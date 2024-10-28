// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <sys/mman.h>
#include <stdlib.h>

void *malloc(size_t size) {
	if (mem_list_head.prev == NULL) {
		mem_list_init();
	}

	size_t new_desired_start = (size_t)(mem_list_head.prev->start +
										mem_list_head.prev->len);

	mem_list_add((void *)new_desired_start, size);
	void *new_start = mmap((void *)new_desired_start, size,
						   PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
						   -1, 0);

	mem_list_head.prev->start = new_start;

	return new_start;
}

void *calloc(size_t nmemb, size_t size) {
	void *allocated_memory = malloc(nmemb * size);
	char *byte_allocated_memory = (char *)allocated_memory;

	for (size_t i = 0; i < nmemb * size; i++) {
		byte_allocated_memory[i] = 0;
	}

	return allocated_memory;
}

void free(void *ptr) {
	struct mem_list *mem_list_to_ptr = mem_list_find(ptr);

	munmap(mem_list_to_ptr->start, mem_list_to_ptr->len);

	mem_list_to_ptr->next->prev = mem_list_to_ptr->prev;
	mem_list_to_ptr->prev->next = mem_list_to_ptr->next;

	munmap(mem_list_to_ptr, sizeof(struct mem_list));
}

void *realloc(void *ptr, size_t size) {
	struct mem_list *mem_list_to_ptr = mem_list_find(ptr);
	char *byte_old_start = mem_list_to_ptr->start;
	int old_length = mem_list_to_ptr->len;

	void *new_start = mmap(mem_list_to_ptr->start, size,
						   PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
						   -1, 0);

	if (new_start == NULL) {
		return NULL;
	}

	char *byte_new_start = (char *)new_start;

	for (int i = 0; i < old_length; i++) {
		byte_new_start[i] = byte_old_start[i];
	}

	munmap(byte_old_start, old_length);
	mem_list_to_ptr->start = new_start;
	mem_list_to_ptr->len = size;

	return new_start;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
	size_t total_size = nmemb * size;
	if (nmemb != 0 && total_size / nmemb != size) {
		return NULL;
	}

	return realloc(ptr, total_size);
}
