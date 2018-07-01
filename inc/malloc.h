#ifndef JOS_INC_MALLOC_H
#define JOS_INC_MALLOC_H 1

#define MAX_MALLOC 32

struct MallocStatus
{
	char buf[MAX_MALLOC][PGSIZE];
	bool used[MAX_MALLOC];
};

void *malloc(size_t size);
void free(void *addr);

#endif
