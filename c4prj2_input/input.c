#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void remove_newline(char * str) {
  char * pos;
  pos = strchr(str, '\n');
  *pos = '\0';
}

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = malloc(sizeof(*deck->cards));
  deck->n_cards = 0;
  
  char * newstr = remove_newline(str);
  //sep the string on spaces
  while(strsep(&newstr, ' ') != NULL) {
    deck->n_cards++;
    deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
    if (strcomp(*newstr, '?') == 0) {
      size_t index;
      int n = atoi(*(newstr+1));
      index = (size_t)n;
      card_t * ptr = add_empty_card(deck);
      add_future_card(fc, index, ptr);
    }
    else {
      card_t * c = card_from_letters(*newstr, *(newstr+1));
      add_card_to(deck, *c);
    }
  }
  free(newstr);

  return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** deck_ts = malloc(sizeof(**deck_ts));

  char * line = NULL;
  size_t sz = 0;
  int i = 0;
  while(getline(&line, &sz, f) > 0) {
    *n_hands++;
    deck_ts = realloc(deck_ts, *n_hands * sizeof(**deck_ts));
    deck_t * deck = hand_from_string(line, fc);
    deck_ts[i] = deck;
    free(line);
    line = NULL;
    i++;
  }
  free(line);

  return deck_p;
}
