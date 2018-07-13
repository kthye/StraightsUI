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

class Model : public Subject {
public:
    enum PlayerType { HUMAN, COMPUTER };
    enum GameState { INITIAL, IN_ROUND, ROUND_ENDED, GAME_ENDED };
    enum Error { ILLEGAL_DISCARD, NONE };

private:
    // The current seed used to shuffle the deck
    int seed_;

    // The deck owns all card objects passed around during the game
    std::vector<std::unique_ptr<const Card>> deck_;

    // Holds all players in the game
    std::vector<std::unique_ptr<Player>> players_;

    // Points to the player whose turn it currently is
    std::vector<std::unique_ptr<Player>>::iterator curr_player_;

    // Stores the cards that have been played
    SortedCardList play_area_;

    // Stores the winners of the most recent game
    // If a game is in progress, winners_ is empty
    std::vector<std::vector<const Player *>> winners_;

    // The current state of the game
    Model::GameState state_;

    // The current error, if it exists
    Model::Error error_;

    // Initializes the internal deck representation
    void initDeck();

    // Clears players_ and creates PLAYER_COUNT new players with types
    void resetPlayers(const std::vector<PlayerType> & types);

    // Shuffles the internal deck representation
    void shuffleDeck();

    // Deals the first 13 cards to player 1, second 13 cards to player 2, etc.
    void dealHands();

    // Advances curr_player_ to the next player
    void advancePlayer();

    // Populates winners_ using current player scores
    void populateWinners();

public:
    // The number of cards in the deck
    static const size_t CARD_COUNT;

    // The number of players in a game
    static const size_t PLAYER_COUNT;

    // The number of cards in each player's hand
    static const size_t HAND_SIZE;

    Model();

    const std::vector<std::unique_ptr<Player>> & players() const;
    const Player * currPlayer() const;
    const SortedCardList & playArea() const;
    const std::vector<std::vector<const Player *>> & winners() const;
    Model::GameState state() const;
    Model::Error error() const;

    CardList currLegalPlays() const;

    void newGame(const std::vector<PlayerType> & types, int seed = 0);
    void newRound();
    void endRound();
    void endGame();
    void playCard(const Card * c);
    void discardCard(const Card * c);
    void setError(Error error);
    void clearError();
    void ragequit();

    void playCurrPlayer(const PlayerVisitor * pv);

}; // Model

#endif
