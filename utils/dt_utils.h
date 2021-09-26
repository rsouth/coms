//
// Created by rsouth on 26/09/2021.
//

#ifndef COMS_UTILS_DT_UTILS_H_
#define COMS_UTILS_DT_UTILS_H_

#include <time.h>

char *dt_as_str(struct tm *dt);

struct tm now();

#endif //COMS_UTILS_DT_UTILS_H_
