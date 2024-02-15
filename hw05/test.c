#include <stdio.h>
#include <stdlib.h>

int main()
{
  unsigned int a = 0xdeadbeef;
  unsigned char *p = (unsigned char*)&a;
  for(int i = 0; i < 4; i++)
  {
    printf("%d: 0x%02x\n", i, p[i]);
  }
}
