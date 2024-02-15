#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef union {
  unsigned int options : 4;
  struct {
    unsigned int none  : 1; // no arguments given at all 
    unsigned int chars : 1; // output the #chars 
    unsigned int words : 1; // output the #words
    unsigned int lines : 1; // output the #lines 
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
void wc_read(wc_t* wc);

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
  // get the wc_s to iterate through
  opts_t opts;
  int num_wcs = 0;
  wc_t** wcs = wc_gen_from_args(argc, argv, &opts, &num_wcs);

  // read each wc
  for(int i = 0; i < num_wcs; i++)
  {
    wc_read(wcs[i]);

    // print it out to the screen
    wc_output(wcs[i]);

  }


  // if multiple, put the total
  if(num_wcs > 1)
  {
    wc_output_total(wcs, num_wcs);
  }

  // free memory
  wc_free(wcs, num_wcs);

  return 0;
}



// free all of the stuff
// opts_t* will be like a "singleton",
// so don't free it with every wc_t
void wc_free(wc_t** wcs, int num_wcs)
{
  if(num_wcs > 0)
  {
    free(wcs[0]->opts);
    for(int i = 0; i < num_wcs; i++)
      free(wcs[i]);
  }
  free(wcs);
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
void wc_read(wc_t* wc)
{
  FILE* fd;
  if(strcmp(wc->fn, "-stdin-") == 0)
    fd = stdin;
  else
    fd = fopen(wc->fn, "r");

  char prev=' ', cur;
  int saw_space = 0;
  while((cur = fgetc(fd)) != EOF)
  {
    // check for newline
    if(cur == '\n')
    {
      wc->lines++;
    }

    // check for spaces
    if(!isspace(prev) && isspace(cur)) 
    {
      wc->words++;
    }

    wc->chars++;

    prev = cur;
  }

  // end of file no space but was a word
  if(!isspace(prev))
    wc->words++;

  if(strcmp(wc->fn, "-stdin-") != 0)
    fclose(fd);
}

// output in the form:
// <fn> <?lines> <?words> <?chars>
void wc_output(wc_t* wc)
{
  printf("%s", wc->fn);

  if(wc->opts->lines)
    printf(" %d", wc->lines);

  if(wc->opts->words)
    printf(" %d", wc->words);

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
    return 0;
  }

  // yes; close it
  fclose(fd);
  return 1;
}

// generate all of the wc_t's to run through and the opts to do so
wc_t** wc_gen_from_args(int argc, char* argv[], opts_t* opts, int* num_wcs)
{
  // create the options
  opts = malloc(sizeof(*opts));
  opts->options = 0;

  // just go bold, but only make as many as needed (num_wcs)
  wc_t** wcs = malloc(sizeof(wc_t*)*argc); 
  *num_wcs = 0;  

  // go through the args
  int opt_count = 0;
  for(int i = 1; i < argc; i++)
  {
    if(validate(argv[i]))
    {
      // good file to open
      wcs[(*num_wcs)++] = wc_create(argv[i], opts);
    }
    else if(argv[i][0] == '-')
    {
      int len = strlen(argv[i]);
      for(int j = 1; j < len; j++)
      {

        switch(argv[i][j])
        {
          case 'w':
            opts->words = 1;
            opt_count++;
            break;
          case 'l':
            opts->lines = 1;
            opt_count++;
            break;
          case 'c':
            opts->chars = 1;
            opt_count++;
            break;
          default:
            fprintf(stderr, "ERROR: unkown option \'-%c\'\n", argv[i][j]);
            break;
        }
      }
    }
    else if(strcmp(argv[i], "+") == 0)
    {
      wcs[(*num_wcs)++] = wc_create("-stdin-", opts);
    }
    else
    { // bad file (output that)
      fprintf(stderr, "ERROR: file \'%s\' cannot be opened\n", argv[i]);
    }
  }

  // default usage: "./wc <files>"
  if(opt_count == 0)
  {
    opts->options = 14;
  }

  // "./wc"
  if(argc == 1)
  {
    opts->options = 14;// max out the flags that matter
    wcs[(*num_wcs)++] = wc_create("-stdin-", opts);
  }

  // "./wc <options> " 
  if (opt_count > 0 && *num_wcs == 0)
  {
    wcs[(*num_wcs)++] = wc_create("-stdin-", opts);
  }

  return wcs;
}


