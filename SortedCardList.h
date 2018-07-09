#ifndef SORTEDCARDLIST_H
#define SORTEDCARDLIST_H

#include "Card.h"
#include <vector>

// SortedCardList is a container for cards that maintains a rank order
// numerically from least to greatest for each suit 

// Spec fields: sorted_card_list is the list of all cards 
// clubs_card_list is subset of card_list that has all club cards in order of rank
// diamonds_card_list is subset of card_list that has all diamonds cards in order of rank
// hearts_card_list is subset of card_list that has all hearts cards in order of rank
// spades_card_list is subset of card_list that has all spades cards in order of rank


class SortedCardList {
	// Forward declaration of the implementation of sorted card list
	struct SortedCardListImpl;
	SortedCardListImpl* pImpl_;
    void insertInRankOrder(std::vector<const Card*> & cv, const Card * c);
public:
	// ensures: empty sorted_card_list initialized
	SortedCardList();

	// ensures: sorted_card_list deleted, resources freed 
	virtual ~SortedCardList();

	// ensures: sorted_card_list initialized to same cards as sorted_card_list in args
	SortedCardList(SortedCardList && other);

	// modifies: sorted_card_list
	// ensures: sorted_card_list@pre is freed, sorted_card_list contains same cards as sorted_card_list in args
	SortedCardList &operator=(SortedCardList && other);

	// requires: args card is a valid card from the deck
	// modifies: sorted_card_list
	// ensures: adds args card to sorted_card_list to appropriate suit, may change order to cards in sorted_card_list@pre
	void addCard(const Card* c);

	// modifies: sorted_card_list
	// ensures: all cards removed from sorted_card_list
    void clear();

	// Spec fields: it_card it a iterator to a card in sorted_card_list or to the end of sorted_card_list
	class iterator {
		std::vector<const Card*> cards_;
		int cardIndex_;
		iterator(std::vector<const Card*>& cards, int cardIndex);
		friend class SortedCardList;
	public:
		// modifies: it_card
		// ensures: it_card = it_card@pre + 1
		// returns: it_card
		iterator & operator++();

		// returns: it_card != it_card in args
		bool operator!= (const iterator&) const;

		// returns: it_card == it_card in args
		bool operator== (const iterator&) const;

		// requires: it_card is not the iterator to the end of sorted_card_list
		// returns: card it_card represents 
		const Card* operator* () const;
	};

	// returns: if sorted_card_list empty return iterator to end of sorted_card_list, else return iterator to
	// beginning of sorted_card_list
	iterator begin() const;

	// returns: iterator to end of sorted_card_list
	iterator end() const;

	// returns: if sorted_card_list has no clubs return iterator to end of clubs_card_list, else return iterator to
	// beginning of clubs_card_list
	iterator clubs_begin() const;

	// returns: iterator to end of clubs_card_list
	iterator clubs_end() const;

	// returns: if sorted_card_list has no clubs return iterator to end of diamonds_card_list, else return iterator to
	// beginning of diamonds_card_list
	iterator diamonds_begin() const;

	// returns: iterator to end of diamonds_card_list
	iterator diamonds_end() const;

	// returns: if sorted_card_list has no clubs return iterator to end of hearts_card_list, else return iterator to
	// beginning of hearts_card_list
	iterator hearts_begin() const;

	// returns: iterator to end of hearts_card_list
	iterator hearts_end() const;

	// returns: if sorted_card_list has no clubs return iterator to end of spades_card_list, else return iterator to
	// beginning of spades_card_list
	iterator spades_begin() const;

	// returns: iterator to end of spades_card_list
	iterator spades_end() const;
};

#endif
