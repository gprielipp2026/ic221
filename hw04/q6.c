#include <stdio.h>

int main()
{
  int darray[][4] = {{1, 9, 8, 4},
                     {1, 8, 9, 4},
                     {2, 0, 1, 7},
                     {3, 4, 5, 8}};
  int* p = darray[1];
  printf("%d\n", p[2]);

  return 0;
}
