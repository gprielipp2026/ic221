#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(int* cardNumberDigits);
int read(char* str, int* num);

int main(int argc, char * argv[]){
  //TODO: Complete the program 

  //ERROR string for you to use to pass automated tests (print stderrr!)
  //  -- "ERROR: require credit card number\n"
  //  -- "ERROR: Invalid credit card number: Bad Length\n"
  //  -- "ERROR: Invalid credit card number: Bad number '%c'\n"
  if(argc != 2)
  {
    fprintf(stderr, "ERROR: require credit card number\n");
    exit(1);
  }
 
  int* cardNumberDigits;
  if(read(argv[1], cardNumberDigits) == 0)
  {
    fprintf(stderr, "ERROR: Invalid credit card number: Bad number '%s'\n", argv[1]);
    exit(1);
  } 
  
  if(strlen(argv[1]) != 16)
  {
    fprintf(stderr, "ERROR: Invalid credit card number: Bad Length\n");
    exit(1);
  }

  // OUTPUT strinsg for you to use to pass automated tests
  //  --  printf("VALID\n");
  //  -- printf("INVALID\n");

  if(check(cardNumberDigits))
  {
    printf("VALID\n");
  }
  else
  {
    printf("INVALID\n");
    return 2;
  }
 
  free(cardNumberDigits); 

  // RETURN values to use
  //  -- return 0 : valid credit card number
  //  -- return 1 : error occured
  //  -- return 2 : invalid credit card number

  return 0;
}

int check(int* cardNumberDigits)
{
  int* digits = malloc(sizeof(int)*16);
  memcpy(digits, cardNumberDigits, 16);
  /*for(int i = 0; i < 16; i++)*/
  /*{*/
  /*digits[i] = cardNumberDigits[i];*/
  /*}*/

  // double every other digit
  for(int i = 0; i < 16; i+=2)
  {
    digits[i] *= 2;
  }

  // if a digit is > 9, replace as the sum of its digits
  for(int i = 0; i < 16; i++)
  {
    if(digits[i] > 9)
    {
      int r = digits[i] % 10;
      int l = (digits[i]/10) % 10;
      digits[i] = l + r;
    }
  }

  // sum the remaining numbers
  int sum = 0;
  for(int i = 0; i < 16; i++)
  {
    sum += digits[i];
  }

  free(digits);

  return (sum % 10) == 0;
}

int read(char* str, int* num)
{
  // return 0 if I fail to parse the number
  int len = strlen(str);
  num = malloc(sizeof(int)*len);
  for(int i = 0; i < len; i++)
  {
    if(!(str[i] >= '0' && str[i] <= '9'))
    {
      free(num);
      return 0;
    }
    num[len-i-1] = str[i] - '0';
  }    
  // return 1 if I succeed
  
  return 1;
}

