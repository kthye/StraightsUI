/*
 * Adapted from MVC example by Jo Atlee
 */

#include "model.h"
#include "Card.h"

Model::Model() {
    for (int s = CLUB; s != SUIT_COUNT; ++s) {
        for (int r = ACE; r != RANK_COUNT; ++r) {
            // TODO: use make_unique here
            // deck_.push_back(std::make_unique<Card>(static_cast<Suit>(s), static_cast<Rank>(r)));
            deck_.push_back(std::unique_ptr<const Card>(new Card(static_cast<Suit>(s), static_cast<Rank>(r))));
        }
    }
    /// FOR TESTING
    play_area_.addCard(deck_.at(4).get());
    play_area_.addCard(deck_.at(13).get());
    play_area_.addCard(deck_.at(22).get());
    play_area_.addCard(deck_.at(23).get());
    play_area_.addCard(deck_.at(44).get());
    /// END TESTING
}

const std::vector<std::unique_ptr<Player>> & Model::getPlayers() const {
    return players_;
}

const Player * Model::getCurrPlayer() const {
    return (*curr_player_).get();
}

const SortedCardList & Model::getPlayArea() const {
    return play_area_;
}
