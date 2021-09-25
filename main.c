

//#include <stdlib.h> // malloc
#include <stdio.h>
#include <string.h> // memset
#include <assert.h>
#include "ordercache/order_cache.h"
//#include "lib/lwlog.h"

#include "lib/seethe.h"

#undef LOG_LEVEL
#define LOG_LEVEL   DEBUG

int main(__attribute__((unused)) int argc, char **argv) {

  init_order_cache();

//    info("order_cache contains: %li", cache_count);

//    free(th->order_cache);
//    free(th);

//    return 0;
  info("created ordercache");
//    OrderCache* order_cache = NULL;
//    init_order_cache(order_cache);


  print_all_orders();
//    info("order_cache is %li", order_cache->cache_size);
//
  Order *order = create_order(10, 123, SELL);
  Order *order2 = create_order(456, 12345, BUY);
  print_all_orders();
//    info("OrderId: %li has qty %li", order->id, order->qty);
//
//    // // free(a);
//
  delete_order(order->id);
  print_all_orders();
//
  free_orders();
//
  print_all_orders();

  return 0;
}
