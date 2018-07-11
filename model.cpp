/*
 * Adapted from MVC example by Jo Atlee
 */

#include <random>
#include "model.h"
#include "Card.h"
#include "GameLogic.h"
#include "PlayController.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

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

std::string Model::error() const {
    return error_;
}

void Model::newGame(const std::vector<PlayerType> & types, int seed) {
    initPlayers(types);
    seed_ = seed;
    shuffleDeck();
    dealHands();
    game_in_progress_ = true;
    round_in_progress_ = true;
    notify();
}

void Model::newRound() {
    shuffleDeck();
    dealHands();
    round_in_progress_ = true;
    notify();
}

// Require that c points to element in deck
void Model::playCard(const Card * c) {
    CardList legal_plays = GameLogic::getLegalPlays(play_area_, (*curr_player_)->hand());
    if (legal_plays.contains(c)) {
        (*curr_player_)->removeFromHand(c);
        play_area_.addCard(c);
        advancePlayer();
    } else if (!legal_plays.isEmpty()) {
        error_ = ERR_HAS_LEGAL_PLAY;
    } else {
        (*curr_player_)->removeFromHand(c);
        (*curr_player_)->addToDiscard(c);
        advancePlayer();
    }
    notify();
}

void Model::play(const PlayController & pc) {
    (*curr_player_)->play(pc);
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

void Model::resetPlayerScores() {
    for (auto it = players_.begin(); it != players_.end(); ++it) {
        (*it)->resetScore();
    }
}

void Model::advancePlayer() {
    ++curr_player_;
    if (curr_player_ == players_.end()) {
        curr_player_ = players_.begin();
    }
    // curr_player_.play()
}
