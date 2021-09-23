//
// Created by rsouth on 18/09/2021.
//

//#include <string.h> // memset
//#include <stdio.h>
//#include <stdlib.h> // malloc
#include <assert.h>
#include "order_cache.h"

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
long cache_size= 0;

Order** orders= NULL;
//OrderCache* order_cache;

const char* PRINT_ORDER_FORMAT = "Order %li => ID: %li, Qty: %li\n";


int ensure_size(const int new_count) // remember new_count can be +/-
{
//    assert(order_cache != NULL);
//    long cache_expected_size = order_cache->cache_count + new_count + OC_BUF_COUNT;
//    if (order_cache->cache_count >= cache_expected_size)
//    {
//        // cache is big enough :) .. but check if it's too
//        // if the cache size is too large for the count, we can shrink it
//        ldiv_t cache_lower_threshold = ldiv(order_cache->cache_size, (OC_RESIZE_PCT / 100));
//        if (order_cache->cache_count < cache_lower_threshold.quot)
//        {
//            // too much space, need to resize!
//        }
//
//        // if the next_order_index is too close to the max, shuffle
//        if (order_cache->cache_size - order_cache->next_order_index <= 0)
//        {
//            // but need to shuffle :)
//            // and set next_order_index to cache_count (or plus one?)
//        }
//    }
//    else
//    {
//        // cache is not big enough
//        // need to resize
//    }
//
//    return 0;
}

long add_to_order_cache(Order** ol, long sz)
{
//    // if (ensure_size(sizeof(*order) / sizeof(order[0])) != 0)
//    // {
//    //     // fail.
//    //     return -1;
//    // }

    printf("got order at addy %p\n", *ol);

    orders[next_order_index] = *ol;
    long added_at = next_order_index;
    next_order_index++;
    cache_count++;

//    // add to cache...
//    // order_cache.order_cache[0] = order;
//    // printf("added. sizeof %li, count \n", sizeof(order_cache.order_cache) / sizeof(Order));
//
    return added_at;
}


Order *create_order(long id, long qty)
{
    Order *order = malloc(sizeof(Order));
    order->id = id;
    order->qty = qty;
    printf("Order created: ID %li, Qty %li at %p\n", order->id, order->qty, order);

//    Order ol[1] = {*order};
//    orders[0] = order;
    add_to_order_cache(&order, 0);
    return order;
}

int delete_order(long order_id) {
//    for (int i = 0; i < order_cache->cache_count; i++) {
//        if (order_cache->order_cache[i]->id == order_id) {
////            order_cache->order_cache[i] = NULL;
//            Order *to_delete = order_cache->order_cache[i];
//            printf("Delete order %li\n", to_delete->id);
//
////            free(to_delete);
//
//            order_cache->order_cache[i] = NULL;
//            order_cache->cache_count--;
//        }
//    }
}



void init_order_cache() {
    cache_count = 0;
    cache_size = 0;
    next_order_index = 0;

    size_t initial_size = sizeof(Order*) * OC_BUF_COUNT;
    orders = malloc(initial_size);
    memset(orders, 0, initial_size);

    printf("ordercache at %p\n", orders);
}


int free_orders()
{
    // free each order in the cache
    for (int i = 0; i < cache_count; i++) {
        if (orders != NULL && &orders[i] != 0) {
            printf("Freeing order at: %p\n", orders[i]);
            free(orders[i]);
            orders[i] = NULL;
        }
    }

    cache_count = 0;
    cache_size = 0;
    next_order_index = 0;

    // coffee time.
    return 0;
}


void print_all_orders()
{
    if (orders == NULL || cache_count <= 0) {
        printf("Order cache is not initted\n");
        return;
    }
    else
    {
        printf("Cache has %li orders\n", cache_count);
        for (long i = 0; i < cache_count; i++)
        {
            Order* ord = orders[i];
            printf(PRINT_ORDER_FORMAT, i, ord->id, ord->qty);
        }
    }
}
