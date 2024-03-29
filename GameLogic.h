#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <cstddef>
#include <vector>
#include <memory>

class SortedCardList;
class Card;
class CardList;
class Player;

class GameLogic final {
    // Checks if a given card can be played given the current state of the playArea
    static bool isPlayLegal(const SortedCardList& playArea, const Card* card);

public:
    // The card which determines the player who should play first
    static const Card STARTING_CARD;

    // The score past which the game should be ended
    static const size_t MAX_SCORE;

    // requires: playArea and hand to be valid references to the table and hand respectively in the same game
    // returns: all legal plays in the given hand
    static CardList getLegalPlays(const SortedCardList& playArea, const CardList& hand);

    // returns: the score of the given discard
    static size_t calculateScore(const CardList& discard);

    // returns: whether the round is over based on the players' hands
    static bool isRoundOver(const std::vector<std::unique_ptr<Player>> & players);

    // returns: whether the game is over based on the players' scores
    static bool isGameOver(const std::vector<std::unique_ptr<Player>> & players);
};

#endif
