//
// Created by rsouth on 26/09/2021.
//

#include <time.h>
#include <malloc.h>
#include <string.h>
#include "../lib/seethe.h"

#define DT_BUF_SZ  11

void dtp_as_str(char** pp_char, struct tm *p_dt) {
  char buf[DT_BUF_SZ] = {0};
  strftime(buf, DT_BUF_SZ, "%F", p_dt);
  buf[DT_BUF_SZ - 1] = '\0';

  *pp_char = malloc(DT_BUF_SZ);
  strncpy(*pp_char, buf, DT_BUF_SZ);
  debug("created %s at %p", *pp_char, *pp_char);
}

struct tm now() {
  time_t t = time(NULL);
  struct tm *pdt = localtime(&t);
  return *pdt;
}
