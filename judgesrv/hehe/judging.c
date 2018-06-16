#include "sort.lib"
void sort(unsigned *a, int n) {
////// Author: 不存在的
	void *memset(void *, int, size_t);
	void *memcpy(void *, const void *, size_t);
	void qsort(unsigned *, int, int);
	qsort(a, 0, n - 1);
}

void
qsort(unsigned *a, int l, int r)
{
	int i = l, j = r;
	unsigned x = a[(l + r) / 2];
	do
	{
		while(a[i] < x) ++i;
		while(x < a[j]) --j;
		if(i <= j)
		{
			unsigned y = a[i]; a[i] = a[j]; a[j] = y;
			++i; --j;
		}
	}
	while(i <= j);
	if(l < j) qsort(a, l, j);
	if(i < r) qsort(a, i, r);

}
