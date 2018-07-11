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

using namespace std;

class Tester : public Observer {
    int update_count;
public:
    Tester() : update_count{0} {}

    void update () {
        ++update_count;
    }

    void assertSingleUpdate() {
        assert(update_count == 1);
        update_count = 0;
    }
};

int main( int argc, char * argv[] ) {

	Model model;
    Controller controller( &model );
    Tester t;
    model.subscribe(&t);

    cout << "Hello world!" << endl;

    // Game should not start in progress
    assert(model.gameInProgress() == false);

    // Start a new game
    model.newGame(std::vector<PlayerType> {HUMAN, COMPUTER, COMPUTER, HUMAN});

    t.assertSingleUpdate();

    assert(model.players().at(0)->type() == HUMAN);
    assert(model.players().at(1)->type() == COMPUTER);
    assert(model.players().at(2)->type() == COMPUTER);
    assert(model.players().at(3)->type() == HUMAN);

    // Check the correct opening state of the game
    stringstream hand;
    for (const Card * c : model.currPlayer()->hand()) {
        hand << *c << " ";
    }
    assert(hand.str() == "JH 6C 10S 4S 5D 3H 7S KS 7D JD 8H 4C 4D ");

    // Play the 7S as you would expect
    const Card * seven_spades = *(++++++++++++model.currPlayer()->hand().begin());
    model.playCard(seven_spades);

    t.assertSingleUpdate();

    // Check that the card was played properly
    hand.str("");
    for (const Card * c : model.players().at(3)->hand()) {
        hand << *c << " ";
    }
    assert(hand.str() == "JH 6C 10S 4S 5D 3H KS 7D JD 8H 4C 4D ");

	return 0;
} // main
