#include <cstddef>
#include <memory>
#include "GameLogic.h"
#include "Card.h"
#include "SortedCardList.h"
#include "CardList.h"
#include "Player.h"

const Card GameLogic::STARTING_CARD = Card(SPADE, SEVEN);
const size_t GameLogic::MAX_SCORE = 80;

CardList GameLogic::getLegalPlays(const SortedCardList& playArea, const CardList& hand) {
	CardList legalPlays;

	for (auto it = hand.begin(); it != hand.end(); ++it) {
        if (**it == STARTING_CARD) {
            legalPlays = CardList();
            legalPlays.addCard(*it);
            break;
        } else if (isPlayLegal(playArea, (*it))) {
			legalPlays.addCard(*it);
		}
	}

	return legalPlays;
}

bool GameLogic::isPlayLegal(const SortedCardList& playArea, const Card* card) {
	for (auto it = playArea.begin(); it != playArea.end(); ++it) {
        if (card->getRank() == SEVEN) {
			return true;
		} else if (card->getSuit() == (*it)->getSuit() &&
			(card->getRank() + 1 == (*it)->getRank() || card->getRank() - 1 == (*it)->getRank())) {
			return true;
		}
	}

	return false;
}

size_t GameLogic::calculateScore(const CardList& discard) {
    size_t score = 0;
	for (auto it = discard.begin(); it != discard.end(); ++it) {
        score += (*it)->getRank() + 1;
	}
	return score;
}

bool GameLogic::isRoundOver(const std::vector<std::unique_ptr<Player>> & players) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (!(*it)->hand().isEmpty()) {
            return false;
        }
    }
    return true;
}

bool GameLogic::isGameOver(const std::vector<std::unique_ptr<Player>> & players) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if ((*it)->score() >= MAX_SCORE) {
            return true;
        }
    }
    return false;
}
