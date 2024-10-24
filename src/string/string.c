// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source) {
	size_t i;
	for (i = 0; source[i] != '\0'; i++) {
		destination[i] = source[i];
	}

	destination[i] = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len) {
	size_t i;
	for (i = 0; source[i] != '\0' && i < len; i++) {
		destination[i] = source[i];
	}

	for (; i < len; i++) {
		destination[i] = '\0';
	}

	return destination;
}

char *strcat(char *destination, const char *source) {
	size_t i;
	for (i = 0; destination[i] != '\0'; i++) {}
	size_t j;
	for (j = 0; source[j] != '\0'; j++) {
		destination[i + j] = source[j];
	}
	destination[i + j] = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len) {
	size_t i;
	for (i = 0; destination[i] != '\0'; i++) {}
	size_t j;
	for (j = 0; source[j] != '\0' && j < len; j++) {
		destination[i + j] = source[j];
	}
	destination[i + j] = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2) {
	for (size_t i = 0;; i++) {
		if (str1[i] == str2[i] && str1[i] == '\0') {
			return 0;
		}
		if (str1[i] == '\0') {
			return -1;
		}
		if (str2[i] == '\0') {
			return 1;
		}

		int chars_diff = str1[i] - str2[i];

		if (chars_diff != 0) {
			return chars_diff;
		}
	}
}

int strncmp(const char *str1, const char *str2, size_t len) {
	for (size_t i = 0; i < len; i++) {
		if (str1[i] == str2[i] && str1[i] == '\0') {
			return 0;
		}
		if (str1[i] == '\0') {
			return -1;
		}
		if (str2[i] == '\0') {
			return 1;
		}

		int chars_diff = str1[i] - str2[i];

		if (chars_diff != 0) {
			return chars_diff;
		}
	}
	return 0;
}

size_t strlen(const char *str) {
	size_t i = 0;

	for (; *str != '\0'; str++, i++) {}

	return i;
}

char *strchr(const char *str, int c) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == c) {
			return &str[i];
		}
	}

	return NULL;
}

char *strrchr(const char *str, int c) {
	char *last_occurrence = NULL;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == c) {
			last_occurrence = &str[i];
		}
	}

	return last_occurrence;
}

char *strstr(const char *haystack, const char *needle) {
	for (int i = 0; haystack[i] != '\0'; i++) {
		if (haystack[i] != needle[0]) {
			continue;
		}

		int j;
		for (j = 1; needle[j] != '\0' && haystack[i + j] != '\0' &&
					needle[j] == haystack[i + j]; j++) {}

		if (needle[j] == '\0') {
			return &haystack[i];
		}
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle) {
	char *last_occurrence = NULL;

	for (int i = 0; haystack[i] != '\0'; i++) {
		if (haystack[i] != needle[0]) {
			continue;
		}

		int j;
		for (j = 1; needle[j] != '\0' && haystack[i + j] != '\0' &&
					needle[j] == haystack[i + j]; j++) {}

		if (needle[j] == '\0') {
			last_occurrence = &haystack[i];
		}
	}

	return last_occurrence;
}

void *memcpy(void *destination, const void *source, size_t num) {
	unsigned char *byte_source = (unsigned char *)source;
	unsigned char *byte_destination = (unsigned char *)destination;

	for (size_t i = 0; i < num; i++) {
		byte_destination[i] = byte_source[i];
	}

	return destination;
}

void __memmove_descending(void *destination, const void *source, size_t num) {
	unsigned char *byte_source = (unsigned char *)source;
	unsigned char *byte_destination = (unsigned char *)destination;

	//  Because size_t is an unsigned type, can't make the for
	//	`size_t i = num - 1; i >= 0; ...` as it will underflow at i = 0, and
	//	the condition will never be met
	for (size_t i = num; i > 0; i--) {
		byte_destination[i - 1] = byte_source[i - 1];
	}
}

void *memmove(void *destination, const void *source, size_t num) {
	char ascending_order = 1;

	// This is to check in case that the source overlaps the destination.
	// In that case, we will copy from right to left to avoid
	// changing those bytes early
	if (source + num >= destination) {
		ascending_order = 0;
	}

	if (ascending_order == 1) {
		memcpy(destination, source, num);
	} else {
		__memmove_descending(destination, source, num);
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
	unsigned char *byte_ptr1 = (unsigned char *)ptr1;
	unsigned char *byte_ptr2 = (unsigned char *)ptr2;

	for (size_t i = 0; i < num; i++) {
		int byte_diff = byte_ptr1[i] - byte_ptr2[i];

		if (byte_diff != 0)
			return byte_diff;
	}
	return 0;
}

void *memset(void *source, int value, size_t num) {
	unsigned char *byte_source = (unsigned char *)source;
	unsigned char byte_value = (unsigned char)value;

	for (size_t i = 0; i < num; i++) {
		byte_source[i] = byte_value;
	}

	return source;
}
