/*
 * MVC example of GTKmm program
 *
 * Subject class.  Abstract class for Observer Pattern
 *
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include <set>
#include "Subject.h"
#include "Observer.h"

void Subject::subscribe (Observer *newStraightsView) {
    observers_.insert(newStraightsView);
}


void Subject::unsubscribe (Observer *formerStraightsView) {
     observers_.erase(formerStraightsView);
}


void Subject::notify() {
  Observers::iterator i;
  for (i = observers_.begin(); i != observers_.end(); ++i)
    (*i)->update();
}
