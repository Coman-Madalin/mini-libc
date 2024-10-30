/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __STDDEF_H__
#define __STDDEF_H__    1

#include <internal/types.h>
#include <time.h>

unsigned int nanosleep(const struct timespec *req, struct timespec *rem);

#endif
