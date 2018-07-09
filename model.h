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
class Player;

class Model : public Subject {
    // The deck owns all card objects passed around during the game
    std::vector<std::unique_ptr<const Card>> deck_;

    // Holds all players in the game
    std::vector<std::unique_ptr<Player>> players_;

    // Points to the player whose turn it currently is
    Player * curr_player_;

    // Stores the cards that have been played
    SortedCardList play_area_;

public:
    Model();

    std::vector<std::unique_ptr<Player>> & getPlayers() const;
    Player * getCurrPlayer() const;
    SortedCardList & getPlayArea() const;
}; // Model


#endif
