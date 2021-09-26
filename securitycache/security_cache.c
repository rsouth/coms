//
// Created by rsouth on 26/09/2021.
//

#include <malloc.h>
#include "security_cache.h"
#include "../lib/seethe.h"
#include "../utils/dt_utils.h"
#include "stdio.h"

#undef LOG_LEVEL
#define LOG_LEVEL   DEBUG

Security **securities;

#ifndef PRINT_SECURITY_FORMAT
#define PRINT_SECURITY_FORMAT "Security %s/%s %s (%p)"
#endif

void print_security(Security *sec) {
  char *asd = dt_as_str(&sec->settle_date);
  info(PRINT_SECURITY_FORMAT, sec->traded, sec->against, asd, sec);
  free(asd);
}

void init_security_cache() {

  Security *sec = malloc(sizeof(Security));
  sec->id = 123;
  sec->traded = EUR;
  sec->against = BTC;
  sec->settle_date = now();
  print_security(sec);

  free(sec);

}
