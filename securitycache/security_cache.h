//
// Created by rsouth on 26/09/2021.
//

#ifndef COMS_SECURITYCACHE_SECURITY_CACHE_H_
#define COMS_SECURITYCACHE_SECURITY_CACHE_H_

#include <time.h>

#define GBP "GBP"
#define BTC "BTC"
#define USD "USD"
#define EUR "EUR"

typedef struct Security {
  long id;
  char *traded;
  char *against;
  struct tm settle_date;
} Security;

void init_security_cache();

#endif //COMS_SECURITYCACHE_SECURITY_CACHE_H_
