// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st) {
	if (fd <= 0) {
		errno = EBADF;
		return -1;
	}

	long err = syscall(__NR_fstat, fd, st);
	if (err != 0) {
		errno = -err;
		return -1;
	}

	return 0;
}
