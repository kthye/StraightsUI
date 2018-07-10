/*
 * Adapted from MVC example by Jo Atlee
 */

#ifndef STRAIGHTS_MODEL_H
#define STRAIGHTS_MODEL_H

#include <vector>
#include <memory>
#include "subject.h"
#include "SortedCardList.h"
#include "Player.h"

class Card;

class Model : public Subject {
    // The deck owns all card objects passed around during the game
    std::vector<std::unique_ptr<const Card>> deck_;

    // Holds all players in the game
    std::vector<std::unique_ptr<Player>> players_;

    // Points to the player whose turn it currently is
    std::vector<std::unique_ptr<Player>>::iterator curr_player_;

    // Stores the cards that have been played
    SortedCardList play_area_;

    // The current seed used to shuffle the deck
    int seed_;

    // Whether the types of the player objects are stale
    bool should_set_player_types_;

    // Initializes the internal deck representation
    void initDeck();

    // Initializes PLAYER_COUNT player objects
    void initPlayers();

    // Shuffles the internal deck representation
    void shuffleDeck();

    // Deals the first 13 cards to player 1, second 13 cards to player 2, etc.
    void dealHands();

public:
    // The number of cards in the deck
    static const size_t CARD_COUNT;

    // The number of players in a game
    static const size_t PLAYER_COUNT;

    // The number of cards in each player's hand
    static const size_t HAND_SIZE;

    // The card which determines the player who should play first
    static const Card STARTING_CARD;

    Model();

    const std::vector<std::unique_ptr<Player>> & getPlayers() const;
    const Player * getCurrPlayer() const;
    const SortedCardList & getPlayArea() const;
    bool shouldSetPlayerTypes() const;

    void setPlayerTypes(const std::vector<PlayerType> & types);

    void reset();

}; // Model

#endif
