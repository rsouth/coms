//
// Created by rsouth on 18/09/2021.
//

#ifndef COMS_ORDER_CACHE_H
#define COMS_ORDER_CACHE_H

#include <string.h> // memset
#include <stdio.h>
#include <math.h> // round?
#include <stdlib.h> // malloc
#include "order_cache.h"


typedef struct Order
{
    long id;
    long qty;
} Order;

//typedef struct OrderCache
//{
//    // Order order_cache;
//    long cache_count;
//    long next_order_index;
//    long cache_size;
//    Order *order_cache;
//} OrderCache;

//const int OC_BUF_COUNT = 10;
//const double OC_RESIZE_PCT = 20;

//int ensure_size(const int new_count);

int delete_order(long order_id);

//long add_to_order_cache(Order* order[], long sz);
long add_to_order_cache(Order** ol, long sz);

//Order *create_order(long id, long qty);
//Order *create_order(OrderCache* order_cache, long id, long qty)
Order *create_order(long id, long qty);

void init_order_cache();

//int free_orders(OrderCache* order_cache);
int free_orders();

void print_all_orders();

#endif //COMS_ORDER_CACHE_H
