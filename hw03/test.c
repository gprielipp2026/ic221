#include <stdio.h>

int main()
{
  /*printf("%lu\n", sizeof( int ));*/
  /*printf("%lu\n", sizeof( char ));*/
  /*printf("%lu\n", sizeof( int* ));*/
  /*printf("%lu\n", sizeof( float* ));*/
  /*printf("%lu\n", sizeof( char* ));*/
  /*printf("%lu\n", sizeof( short ));*/
  /*printf("%lu\n", sizeof( int** ));*/
  /*printf("%lu\n", sizeof( float ));*/
  /*printf("%lu\n", sizeof( double ));*/

  unsigned int a = 4294967295;
  printf("%d\n", a);
  int i = 3.1519;
  printf("%d\n", i);
  int j = (int) 1.5 + 2.5 + 3.5 + 4.5; 
  printf("%d\n", j);

  return 0;
}
