#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "future.h"

/*
void malloc_new_decks(future_cards_t * fc, size_t index) {
  fc->decks = realloc(fc->decks, (index+1) * sizeof(*fc->decks));
  for(size_t i=fc->n_decks; i<=index; i++) {
    deck_t * deck = malloc(sizeof(*deck));
    deck->cards = NULL;//malloc(sizeof(*deck->cards));
    deck->n_cards = 0;
    fc->decks[i] = *deck;
  }
  fc->n_decks = index+1;
}
*/

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {

  if (fc->n_decks < index-1) {
    fc->decks = realloc(fc->decks, (index+1) * sizeof(*fc->decks));
  }

  add_card_to(&fc->decks[index], *ptr);
  
  /*
  if (fc->n_decks==0) {
    //fc->decks = malloc(sizeof(*fc->decks));
    malloc_new_decks(fc, index);
  }
  else if (index>fc->n_decks-1) {
    malloc_new_decks(fc, index);
  }
  
  add_card_to(&(fc->decks[index]), *ptr);
  */
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  if (fc->n_decks != deck->n_cards) {
    fprintf(stderr, "There must be the same number of cards in the shuffled deck as there are decks in the future cards\n");
    return;
  }
  for (size_t i=0; i<deck->n_cards; i++) {
    for (size_t j=0; j<fc->decks[i].n_cards; j++) {
      fc->decks[i].cards[j] = deck->cards[i];
      //fc->decks[i].cards[j]->value = deck->cards[i]->value;
    }
  }
}
