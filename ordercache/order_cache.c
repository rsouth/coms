//
// Created by rsouth on 18/09/2021.
//

//#include <string.h> // memset
//#include <stdio.h>
//#include <stdlib.h> // malloc
#include <assert.h>
#include "order_cache.h"

#undef LOG_LEVEL
#define LOG_LEVEL   DEBUG
#include "../lib/seethe.h"

//struct OrderCache order_cache;


//typedef struct Order;
//{
//    long id;
//    long qty;
//} Order;

//typedef struct OrderCache
//{
//    // Order order_cache;
//    Order *order_cache;
//    long cache_count;
//    long next_order_index;
//    long cache_size;
//} OrderCache;

const int OC_BUF_COUNT = 10;
const long OC_RESIZE_PCT = 20;

long cache_count = 0;
long next_order_index = 0;
long cache_size = 0;

Order **orders = NULL;
//OrderCache* order_cache;

const char *PRINT_ORDER_FORMAT = "Order %li => %s %li (%p)";

int ensure_size() // remember new_count can be +/-
{
  assert(orders != NULL);
  long cache_expected_size = cache_count + 1 + OC_BUF_COUNT;
  if (cache_size >= cache_expected_size) {
    // cache is big enough :) .. but check if it's too big
    // if the cache size is too large for the count, we can shrink it
    ldiv_t cache_lower_threshold = ldiv(cache_size, (OC_RESIZE_PCT / 100));
    if (cache_count < cache_lower_threshold.quot) {
      // too much space, need to resize - shrink!
    }

    // if the next_order_index is too close to the max, shuffle
    if (cache_size - next_order_index <= 0) {
      // but need to shuffle :)
      // and set next_order_index to cache_count (or plus one?)
    }

    return 0;
  } else {
    // cache is not big enough
    // need to resize


//      size_t new_size = sizeof(Order *) * (OC_BUF_COUNT + cache_size);
//      Order** new_cache = malloc(new_size);
//      if (new_cache == NULL) {
//        return -1;
//      }
//      memset(new_cache, 0, new_size);
//
//      info("Resized from %li to %li", cache_size, OC_BUF_COUNT + cache_size);
//      cache_size = OC_BUF_COUNT + cache_size;

    return 0;
  }

}

long add_to_order_cache(Order **ol, long sz) {
  if (ensure_size() != 0) {
    // fail.
    return -1;
  }

  info("got order at addy %p", *ol);

  orders[next_order_index] = *ol;
  long added_at = next_order_index;
  next_order_index++;
  cache_count++;

//    // add to cache...
//    // order_cache.order_cache[0] = order;
//    // info("added. sizeof %li, count ", sizeof(order_cache.order_cache) / sizeof(Order));
//
  return added_at;
}

char *side_str(enum Side side) {
  return side == SELL ? "SELL" : "BUY";
}

Order *create_order(long id, long qty, enum Side side) {
  Order *order = malloc(sizeof(Order));
  order->id = id;
  order->qty = qty;
  order->side = side;
  info("Order created: %s ID %li, Qty %li at %p", side_str(order->side), order->id, order->qty, order);

//    Order ol[1] = {*order};
//    orders[0] = order;
  add_to_order_cache(&order, 0);
  return order;
}

int delete_order(long order_id) {
  debug("attempting to delete order %li", order_id);

  for (int i = 0; i < cache_size; i++) {
    Order* ord = orders[i];
    if (ord != NULL && orders[i]->id == order_id) {
//            order_cache->order_cache[i] = NULL;
      info("Delete order %li at %p", ord->id, ord);

      free(ord);

      orders[i] = NULL;
      cache_count--;
    }
  }
}

void init_order_cache() {
  cache_count = 0;
  cache_size = OC_BUF_COUNT;
  next_order_index = 0;

  size_t initial_size = sizeof(Order *) * OC_BUF_COUNT;
  orders = malloc(initial_size);
  memset(orders, 0, initial_size);

  info("ordercache at %p", orders);
}

int free_orders() {
  // free each order in the cache
  for (int i = 0; i < cache_size; i++) {
    if (orders != NULL && orders[i] != 0) {
      delete_order(orders[i]->id);
//      info("Freeing order at: %p", orders[i]);
//      free(orders[i]);
//      orders[i] = NULL;
    }
  }

  cache_count = 0;
  cache_size = 0;
  next_order_index = 0;

  // coffee time.
  return 0;
}

void print_order(Order* ord) {
  info(PRINT_ORDER_FORMAT, ord->id, side_str(ord->side), ord->qty, ord);
}

void print_all_orders() {
  if (orders == NULL || cache_count <= 0) {
    info("Order cache is not initted");
    return;
  } else {
    info("Cache has %li orders", cache_count);
    for (long i = 0; i < cache_size; i++) {
      Order *ord = orders[i];
      if (ord != NULL) {
//        info(PRINT_ORDER_FORMAT, ord->id, side_str(ord->side), ord->qty, ord);
        print_order(ord);
      }
    }
  }
}
