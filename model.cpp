/*
 * Adapted from MVC example by Jo Atlee
 */

#include <random>
#include <algorithm>
#include "model.h"
#include "Card.h"
#include "GameLogic.h"
#include "PlayController.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

#include <iostream>
using namespace std;

const size_t Model::CARD_COUNT = 52;
const size_t Model::PLAYER_COUNT = 4;
const size_t Model::HAND_SIZE = Model::CARD_COUNT / Model::PLAYER_COUNT;
const std::string Model::ERR_HAS_LEGAL_PLAY = "You have a legal play. You may not discard.";

Model::Model()
: seed_{0}, game_in_progress_{false}, round_in_progress_{false} {
    initDeck();
}

const std::vector<std::unique_ptr<Player>> & Model::players() const {
    return players_;
}

const Player * Model::currPlayer() const {
    return (*curr_player_).get();
}

const SortedCardList & Model::playArea() const {
    return play_area_;
}

bool Model::gameInProgress() const {
    return game_in_progress_;
}

bool Model::roundInProgress() const {
    return round_in_progress_;
}

std::string Model::error() const {
    return error_;
}

const std::vector<std::vector<const Player *>> & Model::winners() const {
    return winners_;
}

void Model::newGame(const std::vector<PlayerType> & types, int seed) {
    players_.clear();
    winners_.clear();
    initPlayers(types);
    seed_ = seed;
    game_in_progress_ = true;
    newRound();
}

void Model::endGame() {
    setWinners();
    game_in_progress_ = false;
    notify();
}

void Model::newRound() {
    play_area_.clear();
    for (auto it = players_.begin(); it != players_.end(); ++it) {
        (*it)->clearDiscard();
    }
    shuffleDeck();
    dealHands();
    round_in_progress_ = true;
    notify();
}

void Model::endRound() {
    updateScores();
    round_in_progress_ = false;
    notify();
}

// Require that c points to element in deck
void Model::playCard(const Card * c) {
    CardList legal_plays = GameLogic::getLegalPlays(play_area_, (*curr_player_)->hand());
    if (legal_plays.contains(c)) {
        (*curr_player_)->removeFromHand(c);
        play_area_.addCard(c);
        cout << "Player " << (*curr_player_)->number() << " plays " << *c << endl;
        advancePlayer();
    } else if (!legal_plays.isEmpty()) {
        error_ = ERR_HAS_LEGAL_PLAY;
    } else {
        (*curr_player_)->removeFromHand(c);
        (*curr_player_)->addToDiscard(c);
        cout << "Player " << (*curr_player_)->number() << " discards " << *c << endl;
        advancePlayer();
    }
    notify();
}

void Model::play(const PlayerVisitor * pv) {
    (*curr_player_)->play(pv);
}

void Model::clearError() {
    error_.clear();
    notify();
}

void Model::initDeck() {
    for (int s = CLUB; s != SUIT_COUNT; ++s) {
        for (int r = ACE; r != RANK_COUNT; ++r) {
            // TODO: use make_unique here
            // deck_.push_back(std::make_unique<Card>(static_cast<Suit>(s), static_cast<Rank>(r)));
            deck_.push_back(std::unique_ptr<const Card>(new Card(static_cast<Suit>(s), static_cast<Rank>(r))));
        }
    }
}

void Model::initPlayers(const std::vector<PlayerType> & types) {
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

void Model::updateScores() {
    cout << "updatescores called" << endl;
    for (auto it = players_.begin(); it != players_.end(); ++it) {
        size_t score_gained = GameLogic::calculateScore((*it)->discard());
        (*it)->incrementScore(score_gained);
    }
}

struct winners_ascending
{
    inline bool operator() (const std::vector<const Player *> & v1, const std::vector<const Player *> & v2)
    {
        return (v1.at(0)->score() < v2.at(0)->score());
    }
};

// requires: winners should have been cleared
void Model::setWinners() {
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
    std::sort(winners_.begin(), winners_.end(), winners_ascending());
}

void Model::clearScores() {
    for (auto it = players_.begin(); it != players_.end(); ++it) {
        (*it)->resetScore();
    }
}

void Model::clearWinners() {
    winners_.clear();
}

void Model::ragequit(size_t number) {
    players_.at(number - 1) = std::unique_ptr<Player>(new ComputerPlayer(std::move(*players_.at(number - 1))));
    notify();
}
