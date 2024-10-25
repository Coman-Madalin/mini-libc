#include <unistd.h>
#include "struct_timespec.h"

unsigned int sleep(unsigned int seconds) {
	struct timespec requested = {seconds, 0}, remaining;
	return nanosleep(&requested, &remaining);
}

