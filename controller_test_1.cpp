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
    }
};

int main( int argc, char * argv[] ) {

	Model model;
    Controller controller( &model );
    Tester t;
    model.subscribe(&t);

    cout << "Hello world!" << endl;

    // Game should start with stale player types
    assert(model.shouldSetPlayerTypes() == true);

    // We update the player types
    model.setPlayerTypes(std::vector<PlayerType> {HUMAN, COMPUTER, COMPUTER, HUMAN});

    t.assertSingleUpdate();

    assert(model.getPlayers().at(0)->type() == HUMAN);
    assert(model.getPlayers().at(1)->type() == COMPUTER);
    assert(model.getPlayers().at(2)->type() == COMPUTER);
    assert(model.getPlayers().at(3)->type() == HUMAN);

	return 0;
} // main
