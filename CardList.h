#ifndef CARDLIST_H
#define CARDLIST_H

#include "Card.h"
#include <vector>

// Spec fields: card_list is a fixed-order list of cards

class CardList {
	// Forward declaration of the representation of card_list
	struct CardListImpl;
	CardListImpl* pImpl_;
public:
	// ensures: an empty card_list is initialized
	CardList();

	// ensures: card_list initialized to same cards as args card_list
    CardList(CardList && other);

	// ensures: card_list is deleted and freed from memory
    ~CardList();

	// modifies: card_list
	// ensures: card_list@pre is freed, card_list contains same cards as args card_list
    CardList &operator=(CardList && other);

	// requires: args card is a valid card from deck
	// modifies: card_list
	// ensures: adds args card to end of card_list, all cards in card_list@pre unchanged
    void addCard(const Card* c);

	// modifies: card_list
	// ensures: all cards are removed from card_list
    void clear();

	// requires: args card is a valid card from deck
	// modifies: card_list
	// ensures: Let i be first index such that card_list@pre[i] = args card
	// for all valid k >= i, card_list[k] = card_list@pre[k+1]
	// returns: if i found return card_list@pre[i] else return nullptr
    const Card* removeCard(const Card& c);

		// TODO: spec
		const Card* at(int index) const;

	// returns: if card_list is empty
	bool isEmpty() const;

    // requires: c is a valid card from deck
    // returns: true if the CardList contains c; false otherwise
    bool contains(const Card * c) const;

		// TODO: size spec
		size_t size() const;

	// Spec fields: it_card is an iterator to a card in card_list or the end of card_list
	class iterator {
        std::vector<const Card*> cards_;
		int cardIndex_;
        iterator(std::vector<const Card*>& cards, int cardIndex);
		friend class CardList;
	public:
		// modifies: it_card
		// ensures: it_card = it_card@pre + 1
		// returns: it_card
		iterator& operator++();

		// returns: it_card != it_card in args
        bool operator!= (const iterator&) const;

		// returns: it_card == it_card in args
        bool operator== (const iterator&) const;

		// requires: it_card not the end of card_list
		// returns: card it_card represents
		const Card* operator*() const;
	};

	// returns: if card_list empty then iterator to end of card_list, else iterator to beginning card in card_list
    iterator begin() const;

	// returns: it_card of end of card_list
    iterator end() const;
};

#endif
