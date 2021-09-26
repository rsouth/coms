//
// Created by rsouth on 26/09/2021.
//

#include <time.h>
#include <malloc.h>
#include <string.h>
#include "../lib/seethe.h"

#define DT_BUF_SZ  11

char *dt_as_str(struct tm *dt) {
  char buf[DT_BUF_SZ] = {0};
  strftime(buf, DT_BUF_SZ, "%F", dt);
  buf[DT_BUF_SZ - 1] = '\0';

  char *thing = malloc(DT_BUF_SZ);
  strncpy(thing, buf, DT_BUF_SZ);
  debug("malloced date at %p", thing);
  return thing;
}

struct tm now() {
  time_t t = time(NULL);
  struct tm *pdt = localtime(&t);
  return *pdt;
}
