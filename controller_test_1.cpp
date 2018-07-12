/*
 * MVC example of GTKmm program
 *
 * Displays top card of sorted deck of cards. When "next" button is clicked,
 * the next card is displayed on top of deck.  When the "reset" button is
 * clicked, the top card of a full sorted deck is displayed
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include <iostream>
#include <sstream>
#include <assert.h>
#include "model.h"
#include "controller.h"
#include "observer.h"
#include "Player.h"
#include "Card.h"

using namespace std;

class Tester : public Observer {
    size_t update_count;
public:
    Tester() : update_count{0} {}

    void update () {
        ++update_count;
    }

    void assertSingleUpdate() {
        assertUpdates(1);
    }

    void assertUpdates(size_t n) {
        assert(update_count == n);
        update_count = 0;
    }
};

int main( int argc, char * argv[] ) {
/*
	Model model;
    Controller controller( &model );
    Tester t;
    model.subscribe(&t);

    cout << "Hello world!" << endl;

    // Game should not start in progress
    assert(model.gameInProgress() == false);

    // Start a new game
    controller.newGame(std::vector<PlayerType> {HUMAN, COMPUTER, COMPUTER, HUMAN});

    t.assertSingleUpdate();

    // Check the correct opening state of the game
    stringstream hand;
    for (const Card * c : model.currPlayer()->hand()) {
        hand << *c << " ";
    }
    assert(hand.str() == "JH 6C 10S 4S 5D 3H 7S KS 7D JD 8H 4C 4D ");

    // Play the 7S as you would expect
    const Card * seven_spades = *(++++++++++++model.currPlayer()->hand().begin());
    controller.playCard(seven_spades);

    t.assertUpdates(2);

    // Check that the card was played properly
    hand.str("");
    for (const Card * c : model.players().at(3)->hand()) {
        hand << *c << " ";
    }
    assert(hand.str() == "JH 6C 10S 4S 5D 3H KS 7D JD 8H 4C 4D ");

    // Discard the 9C
    const Card * nine_clubs = *model.currPlayer()->hand().begin();
    controller.playCard(nine_clubs);

    // Check that the card was played properly
    hand.str("");
    for (const Card * c : model.players().at(0)->hand()) {
        hand << *c << " ";
    }
    assert(hand.str() == "5H 2S 9H 8D AD JS QD 8C 6H JC 10D KC ");

    // We now expect 2 computer turns
    t.assertUpdates(4);
    assert(**model.playArea().clubs_begin() == Card(CLUB, SEVEN));
    assert(**model.playArea().spades_begin() == Card(SPADE, SIX));
    assert(**(++model.playArea().spades_begin()) == Card(SPADE, SEVEN));

    // Try an illegal play
    const Card * jack_hearts = *model.currPlayer()->hand().begin();
    controller.playCard(jack_hearts);
    t.assertUpdates(2);
    assert(model.error() == "You have a legal play. You may not discard.");

    // Now play a legal card
    const Card * six_clubs = *(++model.currPlayer()->hand().begin());
    controller.playCard(six_clubs);
    t.assertUpdates(2);
    assert(model.error().empty());*/

    /**
     * TEST 2
     */

    Model model2;
    Controller controller2( &model2 );
    Tester t2;
    model2.subscribe(&t2);

    controller2.newGame(std::vector<PlayerType> {COMPUTER, COMPUTER, COMPUTER, COMPUTER}, 99);

    assert(!model2.roundInProgress());
    for (auto it = model2.players().begin(); it != model2.players().end(); ++it) {
        for (auto cit = (*it)->discard().begin(); cit != (*it)->discard().end(); ++cit) {
            cout << (**cit) << " ";
        }
        cout << (*it)->score() << endl;
    }

    controller2.newRound();

    assert(!model2.roundInProgress());
    for (auto it = model2.players().begin(); it != model2.players().end(); ++it) {
        for (auto cit = (*it)->discard().begin(); cit != (*it)->discard().end(); ++cit) {
            cout << (**cit) << " ";
        }
        cout << (*it)->score() << endl;
    }

    const std::vector<std::vector<const Player *>> & winners = model2.winners();
    size_t place = 1;
    for (auto bucket : winners) {
        cout << "Place " << place << " (" << bucket.at(0)->score() << " points), players:";
        for (auto p : bucket) {
            cout << " " << p->number();
        }
        cout << endl;
        ++place;
    }

    assert(!model2.gameInProgress());

    controller2.newGame(std::vector<PlayerType> {COMPUTER, COMPUTER, COMPUTER, COMPUTER}, 12);

    assert(!model2.roundInProgress());
    for (auto it = model2.players().begin(); it != model2.players().end(); ++it) {
        for (auto cit = (*it)->discard().begin(); cit != (*it)->discard().end(); ++cit) {
            cout << (**cit) << " ";
        }
        cout << (*it)->score() << endl;
    }

    controller2.newRound();

    assert(!model2.roundInProgress());
    for (auto it = model2.players().begin(); it != model2.players().end(); ++it) {
        for (auto cit = (*it)->discard().begin(); cit != (*it)->discard().end(); ++cit) {
            cout << (**cit) << " ";
        }
        cout << (*it)->score() << endl;
    }

    const std::vector<std::vector<const Player *>> & winners2 = model2.winners();
    place = 1;
    for (auto bucket : winners2) {
        cout << "Place " << place << " (" << bucket.at(0)->score() << " points), players:";
        for (auto p : bucket) {
            cout << " " << p->number();
        }
        cout << endl;
        ++place;
    }

    /**
     * Test 3
     */

    // Model model;
    // Controller controller( &model );
    // Tester t;
    // model.subscribe(&t);
    //
    // controller.newGame(std::vector<PlayerType> {HUMAN, COMPUTER, COMPUTER, COMPUTER});
    //
    // controller.playCard(*model.currPlayer()->hand().begin());
    // controller.playCard(*(++++++++++++++model.currPlayer()->hand().begin()));
    // cout << "ragequitting" << model.currPlayer()->number() << endl;
    // controller.ragequit(model.currPlayer()->number());
    // cout << "ragequit done" << endl;


	return 0;
} // main
