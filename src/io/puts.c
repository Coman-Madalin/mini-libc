#include "stdio.h"
#include "string.h"
#include "internal/io.h"

int puts(const char *s) {
	ssize_t size = strlen(s);

	while (size > 0) {
		ssize_t written_size = write(1, s, size);
		size -= written_size;
		s += written_size;
	}

	write(1, "\n", 1);

	return 0;
}
