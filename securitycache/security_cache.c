//
// Created by rsouth on 26/09/2021.
//

#include <malloc.h>
#include <assert.h>
#include "security_cache.h"
#include "../lib/seethe.h"
#include "../utils/dt_utils.h"
#include "stdio.h"

#undef LOG_LEVEL
#define LOG_LEVEL   DEBUG

#define SC_BUF_COUNT  10;

static long cache_count = 0;
static long cache_size = 0;
static long next_security_index = 0;


Security **securities;

#ifndef PRINT_SECURITY_FORMAT
#define PRINT_SECURITY_FORMAT "Security %s/%s %s (%p)"
#endif

void print_security(Security *sec) {
  char* p_date_str = NULL;
  dtp_as_str(&p_date_str, &sec->settle_date);

  info(PRINT_SECURITY_FORMAT, sec->traded, sec->against, p_date_str, sec);

  debug("freeing %s at %p", p_date_str, p_date_str);
  free(p_date_str);
}

#define ORDER_FORMAT_STR "Security { id: %li, traded: '%s', against: '%s', settle_date: %s } (at %p)"

/**
 * Caller is responsible for freeing the buffer
 * @param buffer
 * @param sec
 */
void security_string(char** buffer, Security* sec) {
  // allocate space for the whole 'security' string
  long max_len = sizeof(char) * 10;
  *buffer = malloc(max_len);

  // allocate space for the settle date string
  char* p_settle_date = NULL;
  dtp_as_str(&p_settle_date, &sec->settle_date);

  // format
  int len = snprintf(*buffer, max_len, ORDER_FORMAT_STR, sec->id, sec->traded, sec->against, p_settle_date, sec);

  // alert if we are truncating the string due to not allocating enough space
  // todo any way to know the size ahead of time?
  if (len > max_len) {
    critical("Truncated security_string, len of %i vs max %li", len, max_len);
  }

  free(p_settle_date);
}

long add_to_security_cache(Security **sec) {
  assert(securities != NULL);
  assert(*sec != NULL);

  todo("ensure_size for security_cache");
//  if (ensure_size() != 0){}

  // get the string of the security
  char* sec_str = NULL;
  security_string(&sec_str, *sec);
  info("got %s to add to cache", sec_str);

  // add to cache and increment counts
  securities[next_security_index] = *sec;
  long added_at = next_security_index;
  next_security_index++;
  cache_count++;

  info("added %s to cache at index %li", sec_str, added_at);
  free(sec_str);
  return added_at;
}

Security * create_security() {
  Security *sec = malloc(sizeof(Security));
  sec->id = 123;
  sec->traded = EUR;
  sec->against = BTC;
  sec->settle_date = now();
  print_security(sec);

  add_to_security_cache(&sec);

  free(sec);

  return NULL;
}



void init_security_cache() {
  cache_count = 0;
  cache_size = SC_BUF_COUNT;
  next_security_index = 0;

  size_t initial_size = sizeof(Security*) * SC_BUF_COUNT; // todo replace the 10
  securities = malloc(initial_size);
  memset(securities, 0, initial_size);

  info("initialised security_cache with size %li at %p", cache_size, securities);
}
