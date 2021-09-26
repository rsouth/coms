

//#include <stdlib.h> // malloc
#include <limits.h>
#include <stdio.h>
#include <string.h> // memset
#include <assert.h>
#include "ordercache/order_cache.h"
#include "securitycache/security_cache.h"

//#include "lib/lwlog.h"

#include "lib/seethe.h"


#undef LOG_LEVEL
#define LOG_LEVEL   DEBUG

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
  info("Starting.");
  init_security_cache();
  init_order_cache();

  Order *order = create_order(LONG_MAX, LONG_MAX, SELL);
  create_order(456, 12345, BUY);
  print_all_orders();

  delete_order(order->id);
  print_all_orders();
//

  // shutdown
  info("Stopping.");
  free_orders();
//  free_securities();
  todo("Assertions for order & security cache having being free'd");
  return 0;
}
