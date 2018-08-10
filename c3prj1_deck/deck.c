#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
  for (size_t i=0; i<hand->n_cards; i++) {
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (int i=0; i<d->n_cards; i++) {
    if (c.value==d->cards[i]->value && c.suit==d->cards[i]->suit) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  for (int i=0; i<d->n_cards; i++) {
    int randomIndex = random() % d->n_cards;
    card_t * tmp = d->cards[i];
    d->cards[i] = d->cards[randomIndex];
    d->cards[randomIndex] = tmp;
  }
}

void assert_full_deck(deck_t * d) {
  assert(d->n_cards==52);
  for (unsigned i=0; i<52; i++) {
    assert(deck_contains(d, card_from_num(i))==1);
  }
}