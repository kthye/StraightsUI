#include "SortedCardList.h"
#include <vector>
#include <utility>

struct SortedCardList::SortedCardListImpl {
	std::vector<const Card*> clubs_;
	std::vector<const Card*> diamonds_;
	std::vector<const Card*> hearts_;
	std::vector<const Card*> spades_;
	std::vector<const Card*> allCards_;
};

SortedCardList::SortedCardList()
    : pImpl_{new SortedCardListImpl} {}


SortedCardList::~SortedCardList() {
	delete pImpl_;
}

SortedCardList::SortedCardList(SortedCardList && other) {
	pImpl_ = other.pImpl_;
	other.pImpl_ = nullptr;
}

SortedCardList& SortedCardList::operator=(SortedCardList && other) {
	std::swap(pImpl_, other.pImpl_);
	return *this;
}

void SortedCardList::addCard(const Card* c) {
	switch (c->getSuit()) {
	case CLUB:
        insertInRankOrder(pImpl_->clubs_, c);
		break;
	case DIAMOND:
        insertInRankOrder(pImpl_->diamonds_, c);
		break;
	case HEART:
        insertInRankOrder(pImpl_->hearts_, c);
		break;
	case SPADE:
        insertInRankOrder(pImpl_->spades_, c);
		break;
	default:
		break;
	};

	pImpl_->allCards_.push_back(c);
}

void SortedCardList::clear() {
    pImpl_->allCards_.clear();
    pImpl_->clubs_.clear();
    pImpl_->diamonds_.clear();
    pImpl_->hearts_.clear();
    pImpl_->spades_.clear();
}

void SortedCardList::insertInRankOrder(std::vector<const Card*> & cv, const Card * c) {
    if (cv.empty()) {
        cv.push_back(c);
    } else if (c->getRank() > cv.back()->getRank()) {
        cv.push_back(c);
    } else {
        for (auto it = cv.begin(); it != cv.end(); ++it) {
            if (c->getRank() < (*it)->getRank()) {
                cv.insert(it, c);
                break;
            }
        }
    }
}

SortedCardList::iterator::iterator(std::vector<const Card*>& cards, int cardIndex) : cards_{ cards },
cardIndex_{ cardIndex } {}

SortedCardList::iterator& SortedCardList::iterator::operator++() {
	++cardIndex_;
	return *this;
}

bool SortedCardList::iterator::operator!= (const iterator& other) const {
    return cardIndex_ != other.cardIndex_;
}
bool SortedCardList::iterator::operator== (const iterator& other) const {
    return cardIndex_ == other.cardIndex_;
}

const Card* SortedCardList::iterator::operator*() const {
	return cards_[cardIndex_];
}

SortedCardList::iterator SortedCardList::begin() const {
	return SortedCardList::iterator(pImpl_->allCards_, 0);
}

SortedCardList::iterator SortedCardList::end() const {
	return SortedCardList::iterator(pImpl_->allCards_, pImpl_->allCards_.size());
}

SortedCardList::iterator SortedCardList::clubs_begin() const {
	return SortedCardList::iterator(pImpl_->clubs_, 0);
}

SortedCardList::iterator SortedCardList::clubs_end() const {
	return SortedCardList::iterator(pImpl_->clubs_, pImpl_->clubs_.size());
}

SortedCardList::iterator SortedCardList::diamonds_begin() const {
	return SortedCardList::iterator(pImpl_->diamonds_, 0);
}

SortedCardList::iterator SortedCardList::diamonds_end() const {
	return SortedCardList::iterator(pImpl_->diamonds_, pImpl_->diamonds_.size());
}

SortedCardList::iterator SortedCardList::hearts_begin() const {
    return SortedCardList::iterator(pImpl_->hearts_, 0);
}

SortedCardList::iterator SortedCardList::hearts_end() const {
	return SortedCardList::iterator(pImpl_->hearts_, pImpl_->hearts_.size());
}

SortedCardList::iterator SortedCardList::spades_begin() const {
	return SortedCardList::iterator(pImpl_->spades_, 0);
}

SortedCardList::iterator SortedCardList::spades_end() const {
	return SortedCardList::iterator(pImpl_->spades_, pImpl_->spades_.size());
}
