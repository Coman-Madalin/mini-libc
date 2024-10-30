#include <unistd.h>
#include <internal/syscall.h>
#include <stddef.h>
#include "time.h"

unsigned int sleep(unsigned int seconds) {
	struct timespec requested = {seconds, 0}, remaining;
	return nanosleep(&requested, &remaining);
}

unsigned int nanosleep(const struct timespec *req, struct timespec *rem) {
	return syscall(__NR_nanosleep, req, rem);
}
