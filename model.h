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
    // Spec fields
    // seed - the integer used to seed the RNG for shuffling
    // deck - the collection of cards used for a game
    // players - the collection of players in a game
    // curr_player - the player whose turn it is
    // play_area - the collection of cards on the table
    // winners - a collection of players ordered by their place in a game
    // state - the phase of the game the model currently represents
    // error - an error message

public:
    // Used to differentiate between player types
    enum PlayerType { HUMAN, COMPUTER };

    // Used to record the state
    enum GameState {
        INITIAL,        // No game has started
        IN_ROUND,       // A round is in progress
        ROUND_ENDED,    // A round has finished, but the game is still in progress
        GAME_ENDED      // A full game has finished
    };

    // Used to convey different kinds of errors
    enum Error {
        ILLEGAL_DISCARD,    // Player has a legal play, but tried to discard
        NONE                // No error
    };

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

    // modifies: seed, deck, players, curr_player, play_area, winners, state, error
    // ensures: seed is set to 0, state is set to INITIAL, and error is set to NONE
    // ensures: deck is initialized
    // ensures: all other members are default initialized
    Model();

    // returns: players of the current game
    const std::vector<std::unique_ptr<Player>> & players() const;

    // requires: round in progress
    // returns: the player whose turn it is
    const Player * currPlayer() const;

    // returns: the current play_area
    // even if a game or round is not in progress, returns the last state of the
    // play_area
    const SortedCardList & playArea() const;

    // requires: game is over
    // returns: winners of the most recent game
    const std::vector<std::vector<const Player *>> & winners() const;

    // returns: the current state of the game
    // the progression of states is as follows:
    // INITIAL -> IN_ROUND -> ROUND_ENDED -> IN_ROUND -> ROUND_ENDED -> ...
    // IN_ROUND -> ROUND_ENDED -> IN_ROUND -> GAME_ENDED -> IN_ROUND -> ...
    Model::GameState state() const;

    // returns: the current error message
    // the error is not updated by any modifiers except setError and clearError
    Model::Error error() const;

    // requires: round in progress
    // returns: the set of legal plays curr_player has
    // this is not a simple getter; it re-computes the legal plays on each call
    CardList currLegalPlays() const;

    // requires: game is over or hasn't started
    // requires: types has at least 4 elements
    // modifies: players, seed, winners, play_area, deck, state
    // ensures: a new round in a new game is started
    // notifies observers
    void newGame(const std::vector<PlayerType> & types, int seed = 0);

    // requires: round is over or hasn't started
    // modifies: players, play_area, deck, state
    // ensures: a new round in the same game is started
    // notifies observers
    void newRound();

    // requires: round in progress
    // modifies: state
    // ensures: round is over
    // notifies observers
    void endRound();

    // requires: round in progress
    // modifies: winners, state
    // ensures: round is over and winners are set
    // notifies observers
    void endGame();

    // requires: round in progress
    // requires: c is a valid pointer to a card in the deck that is in curr_player's hand
    // modifies: curr_player, play_area
    // ensures: c is played
    // notifies observers
    void playCard(const Card * c);

    // requires: round in progress
    // requires: c is a valid pointer to a card in the deck that is in curr_player's hand
    // modifies: curr_player
    // ensures: c is discarded
    // notifies observers
    void discardCard(const Card * c);

    // modifies: error
    // ensures: error is set to the passed value
    // notifies observers
    void setError(Error error);

    // modifies: error
    // ensures: error is set to NONE
    // notifies observers
    void clearError();

    // requires: round in progress
    // requires: curr_player is a human player
    // modifies: curr_player
    // ensures: curr_player is replaced by an equivalent computer player
    // notifies observers
    void ragequit();

    // requires: round in progress
    // modifies: players
    // ensures: player scores are updated with the current state of their discard
    // a notifying method should always be called immediately after updateScores()
    void updateScores();

    // requires: round in progress
    // modifies: curr_player
    // visits curr_player with the passed player visitor
    void playCurrPlayer(const PlayerVisitor * pv);

}; // Model

#endif
