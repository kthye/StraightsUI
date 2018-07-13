/*
 * Adapted from MVC example by Jo Atlee
 */

#include <random>
#include <algorithm>
#include "model.h"
#include "PlayController.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameLogic.h"

const size_t Model::CARD_COUNT = 52;
const size_t Model::PLAYER_COUNT = 4;
const size_t Model::HAND_SIZE = Model::CARD_COUNT / Model::PLAYER_COUNT;

////////////////////////////////////////
// Constructors
////////////////////////////////////////

Model::Model()
: seed_{0}, state_{INITIAL}, error_{NONE} {
    initDeck();
}

////////////////////////////////////////
// Getters
////////////////////////////////////////

const std::vector<std::unique_ptr<Player>> & Model::players() const {
    return players_;
}

const Player * Model::currPlayer() const {
    return (*curr_player_).get();
}

const SortedCardList & Model::playArea() const {
    return play_area_;
}

const std::vector<std::vector<const Player *>> & Model::winners() const {
    return winners_;
}

Model::GameState Model::state() const {
    return state_;
}

Model::Error Model::error() const {
    return error_;
}

////////////////////////////////////////
// Computed properties
////////////////////////////////////////

CardList Model::currLegalPlays() const {
    return GameLogic::getLegalPlays(playArea(), currPlayer()->hand());
}

////////////////////////////////////////
// Public modifiers
////////////////////////////////////////

void Model::newGame(const std::vector<PlayerType> & types, int seed) {
    resetPlayers(types);
    seed_ = seed;
    winners_.clear();
    newRound();
}

void Model::newRound() {
    play_area_.clear();
    for (auto it = players_.begin(); it != players_.end(); ++it) {
        (*it)->clearDiscard();
    }
    shuffleDeck();
    dealHands();
    state_ = IN_ROUND;
    notify();
}

void Model::endRound() {
    state_ = ROUND_ENDED;
    notify();
}

void Model::endGame() {
    populateWinners();
    state_ = GAME_ENDED;
    notify();
}

// Require that c points to element in deck
void Model::playCard(const Card * c) {
    (*curr_player_)->removeFromHand(c);
    play_area_.addCard(c);
    advancePlayer();
    notify();
}

// Require that c points to element in deck
void Model::discardCard(const Card * c) {
    (*curr_player_)->removeFromHand(c);
    (*curr_player_)->addToDiscard(c);
    (*curr_player_)->incrementScore(GameLogic::calculateScore(c));
    advancePlayer();
    notify();
}

void Model::setError(Error error) {
    error_ = error;
    notify();
}

void Model::clearError() {
    error_ = NONE;
    notify();
}

void Model::ragequit() {
    *curr_player_ = std::unique_ptr<Player>(new ComputerPlayer(std::move(**curr_player_)));
    notify();
}

// Note: this one does not notify since it might not change the state
void Model::playCurrPlayer(const PlayerVisitor * pv) {
    (*curr_player_)->play(pv);
}

////////////////////////////////////////
// Private helpers
////////////////////////////////////////

void Model::initDeck() {
    for (int s = CLUB; s != SUIT_COUNT; ++s) {
        for (int r = ACE; r != RANK_COUNT; ++r) {
            // TODO: use make_unique here
            // deck_.push_back(std::make_unique<Card>(static_cast<Suit>(s), static_cast<Rank>(r)));
            deck_.push_back(std::unique_ptr<const Card>(new Card(static_cast<Suit>(s), static_cast<Rank>(r))));
        }
    }
}

void Model::resetPlayers(const std::vector<PlayerType> & types) {
    players_.clear();
    for (size_t i = 0; i < PLAYER_COUNT; ++i) {
        if (types.at(i) == HUMAN) {
            players_.push_back(std::unique_ptr<Player>(new HumanPlayer(i+1)));
        } else {
            players_.push_back(std::unique_ptr<Player>(new ComputerPlayer(i+1)));
        }
    }
}

void Model::shuffleDeck() {
	static std::mt19937 rng(seed_);

	int n = CARD_COUNT;
	while (n > 1) {
		int k = (int)(rng() % n);
		--n;
        std::swap(deck_.at(n), deck_.at(k));
	}
}

void Model::dealHands() {
    auto deck_it = deck_.begin();
    for (auto player_it = players_.begin(); player_it != players_.end(); ++player_it) {
        CardList hand;
        for (size_t i = 0; i < HAND_SIZE; ++i) {
            hand.addCard((*deck_it).get());
              if (**deck_it == GameLogic::STARTING_CARD) {
                curr_player_ = player_it;
            }
            ++deck_it;
        }
        (*player_it)->setHand(std::move(hand));
    }
}

void Model::advancePlayer() {
    ++curr_player_;
    if (curr_player_ == players_.end()) {
        curr_player_ = players_.begin();
    }
}

struct scores_ascending
{
    inline bool operator() (const std::vector<const Player *> & v1, const std::vector<const Player *> & v2)
    {
        return (v1.at(0)->score() < v2.at(0)->score());
    }
};

// requires: winners should have been cleared
void Model::populateWinners() {
    // put players into score buckets
    for (auto pit = players_.begin(); pit != players_.end(); ++pit) {
        std::vector<std::vector<const Player *>>::iterator bit;
        for (bit = winners_.begin(); bit != winners_.end(); ++bit) {
            if ((*bit).at(0)->score() == (*pit)->score()) {
                (*bit).push_back((*pit).get());
                break;
            }
        }
        if (bit == winners_.end()) {
            winners_.push_back(std::vector<const Player *> { (*pit).get() });
        }
    }

    // sort by score
    std::sort(winners_.begin(), winners_.end(), scores_ascending());
}
