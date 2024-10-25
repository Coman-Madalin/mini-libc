#include <stddef.h>
#include <internal/syscall.h>
#include "struct_timespec.h"

unsigned int nanosleep(const struct timespec *req, struct timespec *rem) {
	return syscall(__NR_nanosleep, req, rem);
}