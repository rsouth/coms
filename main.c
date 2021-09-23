#include <stdlib.h> // malloc
#include <stdio.h>
#include <string.h> // memset
#include "ordercache/order_cache.h"


int main(int argc, char **argv)
{
    init_order_cache();

//    printf("order_cache contains: %li\n", cache_count);

//    free(th->order_cache);
//    free(th);

//    return 0;
    printf("created ordercache\n");
//    OrderCache* order_cache = NULL;
//    init_order_cache(order_cache);


    print_all_orders();
//    printf("order_cache is %li\n", order_cache->cache_size);
//
    Order *order = create_order(10, 123);
    Order *order2 = create_order(456, 12345);
    print_all_orders();
//    printf("OrderId: %li has qty %li\n", order->id, order->qty);
//
//    // // free(a);
//
//    delete_order(10);
//
    free_orders();
//
    print_all_orders();
    return 0;
}
