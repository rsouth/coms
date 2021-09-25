//
// Created by rsouth on 18/09/2021.
//

#ifndef COMS_ORDER_CACHE_H
#define COMS_ORDER_CACHE_H

#include <string.h> // memset
#include <stdio.h>
#include <math.h> // round
#include <stdlib.h> // malloc
#include "order_cache.h"

typedef enum Side {
  BUY, SELL
} Side;

typedef struct Order {
  long id;
  long qty;
  enum Side side;
} Order;

int delete_order(long order_id);

long add_to_order_cache(Order **ol, long sz);

Order *create_order(long id, long qty, enum Side side);

void init_order_cache();

int free_orders();

void print_all_orders();

#endif //COMS_ORDER_CACHE_H
