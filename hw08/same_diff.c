#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  pid_t cpid;
  int status;
  cpid = fork();
  if(cpid==0)
  {
    setpgid(cpid, cpid);
    pid_t p = getppid();
    pid_t pg = getpgid(p);
    pid_t c = getpid();
    pid_t cg = getpgrp();
    if(cg == pg) printf("Same process group\n");
    else printf("Different process group\n");
    exit(0);
  }
  else if(cpid > 0)
  {
    setpgid(cpid, cpid);
    wait(&status);
    exit(0);
  }
  else
  {
    perror("FORK");
    _exit(1);
  }
  return 0;
}
