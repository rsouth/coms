//
// Created by rsouth on 18/09/2021.
//

#include <assert.h>
#include "order_cache.h"
#include "../lib/seethe.h"

#undef LOG_LEVEL
#define LOG_LEVEL   DEBUG

/**
 * order_cache default size and increase amount
 */
const int OC_BUF_COUNT = 10;

static long cache_count = 0;      // current count of orders in the cache
static long next_order_index = 0; // next order can be added at this index
static long cache_size = 0;       // current size of the cache

Order **orders = NULL;     // the cache.

char *side_str(enum Side side) {
  return side == SELL ? "SELL" : "BUY";
}

char* order_str(char** buffer, Order* ord) {
  assert(*buffer == NULL);
  assert(ord != NULL);

  long max_len = sizeof(char) * 100;
  *buffer = malloc(max_len);
  int len = snprintf(*buffer, max_len, "Order { id: %li, side: %s, qty: %li } (at %p)",
                     ord->id,
                     side_str(ord->side),
                     ord->qty,
                     ord);

  critical("have: %i, %li", len, max_len);
  if (len > max_len) {
    critical("Truncated order_string for order %li", ord->id);
  }
}


int ensure_size() // remember new_count can be +/-
{
  assert(orders != NULL);
  long cache_expected_size = cache_count + 1 + OC_BUF_COUNT;
  if (cache_size >= cache_expected_size) {
    // cache is big enough :) .. but check if it's too big
    // if the cache size is too large for the count, we can shrink it
    long upper_cache_threshold = cache_size + OC_BUF_COUNT;
    if (cache_count < upper_cache_threshold) {
      // too much space, need to resize - shrink!
      todo("cache too big; downsize it. Size %li vs count %li vs ideal %li",
           cache_size,
           cache_count,
           upper_cache_threshold);
    }

    // if the next_order_index is too close to the max, shuffle
    if (cache_size - next_order_index <= 0) {
      // but need to shuffle :)
      // and set next_order_index to cache_count (or plus one?)
      todo("cache OK size, but need to shuffle");
    }

    return 0;
  } else {
    // cache is not big enough
    // need to resize


    size_t new_size = sizeof(Order *) * (OC_BUF_COUNT + cache_size);
    Order **new_cache = malloc(new_size);
    if (new_cache == NULL) {
      return -1;
    }
    memset(new_cache, 0, new_size);


    // copy from old to new
    int new_cnt = 0;
    for (int i = 0; i < cache_size; i++) {
      if (orders[i] != NULL) {
        new_cache[new_cnt] = orders[i];
        new_cnt++;
      }
    }

    info("Resized from %li to %li", cache_size, OC_BUF_COUNT + cache_size);
    cache_size = OC_BUF_COUNT + cache_size;


    // replace
//      orders = new_cache;
    free(orders);
    orders = new_cache;

    return 0;
  }

}

long add_to_order_cache(Order **ol) {
  assert(orders != NULL);

  if (ensure_size() != 0) {
    // fail.
    return -1;
  }

  char* order_string = NULL;
  order_str(&order_string, *ol);
  info("got %s add to cache", order_string);

  orders[next_order_index] = *ol;
  long added_at = next_order_index;
  next_order_index++;
  cache_count++;

  info("added %s to cache at index %li", order_string, added_at);

  free(order_string);
  return added_at;
}



Order *create_order(long id, long qty, enum Side side) {
  Order *order = malloc(sizeof(Order));
  order->id = id;
  order->qty = qty;
  order->side = side;
  info("Order created: %s ID %li, Qty %li at %p", side_str(order->side), order->id, order->qty, order);

//    Order ol[1] = {*order};
//    orders[0] = order;
  add_to_order_cache(&order);
  return order;
}

int delete_order(long order_id) {
  debug("attempting to delete order %li", order_id);

  for (int i = 0; i < cache_size; i++) {
    Order *ord = orders[i];
    if (ord != NULL && orders[i]->id == order_id) {
//            order_cache->order_cache[i] = NULL;
      char* order_string = NULL;
      order_str(&order_string, ord);
      info("Found %s, deleting", order_string);
      free(order_string);

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

  info("initialised order_cache with size %li at %p", cache_size, orders);
  print_all_orders();
}

int free_orders() {
  info("Finding and freeing all %li orders", cache_count);
  for (int i = 0; i < cache_size; i++) {
    if (orders != NULL && orders[i] != 0) {
      debug("Found and deleting order at index %i", i);
      delete_order(orders[i]->id);
    }
  }

  cache_count = 0;
  cache_size = 0;
  next_order_index = 0;

  // coffee time.
  return 0;
}

void print_order(Order *ord) {
  info(PRINT_ORDER_FORMAT, ord->id, side_str(ord->side), ord->qty, ord);
}


void print_all_orders() {
  if (orders == NULL) {
    info("Order cache is not initted");
    return;

  } else if (cache_count <= 0) {
    info("Order cache contains no entries");
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
