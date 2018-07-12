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
class PlayController;

enum PlayerType { HUMAN, COMPUTER };

class Model : public Subject {
    // The deck owns all card objects passed around during the game
    std::vector<std::unique_ptr<const Card>> deck_;

    // Holds all players in the game
    std::vector<std::unique_ptr<Player>> players_;

    // Points to the player whose turn it currently is
    std::vector<std::unique_ptr<Player>>::iterator curr_player_;

    // Stores the cards that have been played
    SortedCardList play_area_;

    std::vector<std::vector<const Player *>> winners_;

    // The current seed used to shuffle the deck
    int seed_;

    // Whether a game is currently in progress
    bool game_in_progress_;

    // Whether a round is currently in progress
    bool round_in_progress_;

    // The current error, if it exists
    std::string error_;

    // Initializes the internal deck representation
    void initDeck();

    // Initializes PLAYER_COUNT player objects
    void initPlayers(const std::vector<PlayerType> & types);

    // Shuffles the internal deck representation
    void shuffleDeck();

    // Deals the first 13 cards to player 1, second 13 cards to player 2, etc.
    void dealHands();

    // Advances curr_player_ to the next player
    void advancePlayer();

    // Calculates player scores and updates
    void calculatePlayerScores();

    // Update player scores from their current discards
    void updateScores();

    void setWinners();

    void clearScores();

    void clearWinners();

public:
    // The number of cards in the deck
    static const size_t CARD_COUNT;

    // The number of players in a game
    static const size_t PLAYER_COUNT;

    // The number of cards in each player's hand
    static const size_t HAND_SIZE;

    // The error message shown if the player tries to discard with a legal play
    static const std::string ERR_HAS_LEGAL_PLAY;

    Model();

    const std::vector<std::unique_ptr<Player>> & players() const;
    const Player * currPlayer() const;
    const SortedCardList & playArea() const;
    bool gameInProgress() const;
    bool roundInProgress() const;
    std::string error() const;
    const std::vector<std::vector<const Player *>> & winners() const;

    void newGame(const std::vector<PlayerType> & types, int seed = 0);
    void endGame();
    void newRound();
    void endRound();
    void playCard(const Card * c);
    void clearError();
    void play(const PlayerVisitor * pv);

}; // Model

#endif
