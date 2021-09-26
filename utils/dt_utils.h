//
// Created by rsouth on 26/09/2021.
//

#ifndef COMS_UTILS_DT_UTILS_H_
#define COMS_UTILS_DT_UTILS_H_

#include <time.h>

void dtp_as_str(char** pp_char, struct tm *p_dt);

struct tm now();

#endif //COMS_UTILS_DT_UTILS_H_
