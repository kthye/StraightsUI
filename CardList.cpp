#include "CardList.h"

struct CardList::CardListImpl {
    std::vector<const Card*> cards_;
};

CardList::CardList() : pImpl_{ new CardListImpl } {}

CardList::CardList(CardList && other)
    : pImpl_{other.pImpl_} {
    other.pImpl_ = nullptr;
}

CardList::~CardList() { delete pImpl_; }

CardList & CardList::operator=(CardList && other) {
    std::swap(pImpl_, other.pImpl_);
    return *this;
}

void CardList::addCard(const Card *card) {
	pImpl_->cards_.push_back(card);
}

void CardList::clear() {
    pImpl_->cards_.clear();
}

const Card* CardList::removeCard(const Card& card) {
	for (auto it = pImpl_->cards_.begin(); it != pImpl_->cards_.end(); ++it) {
        if ((*it)->getRank() == card.getRank() &&
            (*it)->getSuit() == card.getSuit()) {
            const Card *removed = *it;
			pImpl_->cards_.erase(it);
            return removed;
		}
	}
    return nullptr;
}

const Card* CardList::at(int index) const {
  return pImpl_->cards_.at(index);
}

bool CardList::isEmpty() const {
	return pImpl_->cards_.empty();
}

bool CardList::contains(const Card * card) const {
	for (const Card * c : pImpl_->cards_) {
        if (c == card) return true;
    }
    return false;
}

CardList::iterator::iterator(std::vector<const Card *> &cards, int cardIndex) : cards_{ cards },
	cardIndex_{ cardIndex } {}

CardList::iterator& CardList::iterator::operator++() {
	cardIndex_++;
	return *this;
}
bool CardList::iterator::operator!= (const iterator& other) const {
    return cardIndex_ != other.cardIndex_;
}

bool CardList::iterator::operator== (const iterator& other) const {
    return cardIndex_ == other.cardIndex_;
}
const Card* CardList::iterator::operator*() const {
	return cards_.at(cardIndex_);
}

CardList::iterator CardList::begin() const {
	return iterator(pImpl_->cards_, 0);
}

CardList::iterator CardList::end() const {
	return iterator(pImpl_->cards_, pImpl_->cards_.size());
}
