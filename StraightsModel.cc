/*
 * MVC example of GTKmm program
 *
 * Model class.  Is responsible keeping track of the deck of cards.  
 * It knows nothing about views or controllers.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "StraightsModel.h"


StraightsModel::StraightsModel() : topCard_(-1) {}

Suits StraightsModel::suit() {
  if (topCard_ == -1) return NOSUIT;
  
  return (Suits) (topCard_ % numSuits);
}

Faces StraightsModel::face() {
  if (topCard_ == -1) return NOFACE;

  return (Faces) (topCard_ / numSuits);
}

void StraightsModel::nextCard() {
  if (topCard_ == numCards-1) return;

  topCard_ += 1;
  notify();

}


void StraightsModel::resetCards() {
  topCard_ = -1;
  notify();
}
