#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
  unsigned int options : 4;
  struct {
    unsigned int none    : 1; // no arguments given at all 
    unsigned int chars   : 1; // output the #chars 
    unsigned int words   : 1; // output the #words
    unsigned int lines   : 1; // output the #lines 
  };
} opts_t;

typedef struct {
  int lines;
  int words;
  int chars;
  char fn[1024]; // hopefully a filename isn't over 1kB of chars
  opts_t* opts;
} wc_t;

// free all of the stuff
// opts_t* will be like a "singleton",
// so don't free it with every wc_t
void wc_free(wc_t** wcs, int num_wcs);

// take a filename and opts_t* and create a wc_t
wc_t* wc_create(char* fn, opts_t* opts);

// fill out the wc_t struct from the given file fields should already be at 0
// open the file to read, then close it when done
// report any errors straight to stderr
void wc_read(wc_t* count);

// output in the form:
// <fn> <?lines> <?words> <?chars>
void wc_output(wc_t* wc);

// output the total of all the wcs
// total <?lines> <?words> <?chars>
void wc_output_total(wc_t** wcs, int num_wcs);

// make sure a string is valid file
int validate(char* str);

// generate all of the wc_t's to run through and the opts to do so
wc_t** wc_gen_from_args(int argc, char* argv[], opts_t* opts, int* num_wcs);



int main(int argc, char* argv[])
{
  opts_t opts;
  opts.options = 0;

  opts.chars = 1;
  opts.lines = 1;

  printf("%d\n", opts.options);

  wc_t* wc = wc_create("test", &opts);

  free(wc);

  return 0;
}



// free all of the stuff
// opts_t* will be like a "singleton",
// so don't free it with every wc_t
void wc_free(wc_t** wcs, int num_wcs)
{
  free(wcs[0]->opts);
  for(int i = 0; i < num_wcs; i++)
    free(wcs[i]);
}

// take a filename and opts_t* and create a wc_t
wc_t* wc_create(char* fn, opts_t* opts)
{
  wc_t* wc = malloc(sizeof(*wc));
  wc->lines = 0;
  wc->words = 0;
  wc->chars = 0;
  strcpy(wc->fn, fn);
  wc->opts = opts;

  return wc;
}

// fill out the wc_t struct from the given file fields should already be at 0
// open the file to read, then close it when done
// report any errors straight to stderr
void wc_read(wc_t* count)
{
  FILE* fd;

  if(strcmp(count->fn, "-stdin-"))
    fd = fopen(stdin, "r");
  else
    fd = fopen(count->fn, "r");
  
  char cur;
  int saw_space = 0;
  while((cur = fgetc(fd)) != EOF)
  {
    // check for newline
    if(cur == '\n')
    {
      wc->lines++;
      continue;
    }

    // check for spaces
    if(cur == ' ' && !saw_space) 
    {
      wc->word++;
      saw_space = 1;
    }
    else if(cur != ' ' && saw_space)
    {
      saw_space = 0;
    }

    wc->chars++;
  }

  fclose(fd);
}

// output in the form:
// <fn> <?lines> <?words> <?chars>
void wc_output(wc_t* wc)
{
  printf("%s", wc->fn);

  if(wc->opts->lines)
    printf(" %d", wc->line);

  if(wc->opts->words)
    printf(" %d", wc->word);

  if(wc->opts->chars)
    printf(" %d", wc->chars);

  printf("\n");
}

// output the total of all the wcs
// total <?lines> <?words> <?chars>
void wc_output_total(wc_t** wcs, int num_wcs)
{
  wc_t* total = wc_create("total", wcs[0]->opts);
  
  for(int i = 0; i < num_wcs; i++)
  {
    wc_t* wc = wcs[i];
    total->lines += wc->lines;
    total->words += wc->words;
    total->chars += wc->chars;
  }

  wc_output(total);
  free(total);
}

// make sure a string is valid file
int validate(char* str)
{
  // security-wise, I think this is probably bad
  // try to open it for reading
  FILE* fd = fopen(str, "r");
  
  // could I open it?
  if(fd == NULL)
  { // no
    fprintf(stderr, "ERROR: file \'%s\' cannot be opened\n", str);
    return 0;
  }
  
  // yes; close it
  fclose(fd);
  return 1;
}

// generate all of the wc_t's to run through and the opts to do so
wc_t** wc_gen_from_args(int argc, char* argv[], opts_t* opts, int* num_wcs);


