#include <stdio.h>

int main(int argc, char* argv[])
{
  char** curarg;
  int i = 0;
  int test;

  for(curarg=argv; *curarg; curarg++)
  {
    if(sscanf(*curarg, "%d", &test))
      printf("argv[%d] = %s (is a number!)\n", i++, *curarg);
    else
      printf("argv[%d] = %s (is *NOT* a number!)\n", i++, *curarg);
  } 

  return 0;
}
