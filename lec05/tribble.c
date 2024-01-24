#include <stdio.h>

typedef struct {
	int a;
	int b;
	int c;
} Tribble;

void addTo(Tribble* t1, Tribble* t2)
{
	t1->a += t2->a;
	t1->b += t2->b;
	t1->c += t2->c;
}

int main()
{
	Tribble u, v;
	u.a = 10;
	u.b = 20;
	u.c = 30;

	v.a = 5;
	v.b = 6;
	v.c = 7;

	addTo(&u, &v);
	printf("%d %d %d\n", u.a, u.b, u.c);

	return 0;
}
