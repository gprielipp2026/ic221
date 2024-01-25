#include <stdio.h>
#include <stdlib.h>

//TODO PART 2: complete the print_array function to have the right output
//prints out the array in the desired format, for exmaple:
// { 0 1 2 3 4 }
void print_array(int len, int* array){
  printf("{ ");
  for(int i = 0; i < len; i++)
  {
    printf("%d ", array[i]);
  }
  printf("}\n");
}

//TODO PART 3: compete the reverse_array function
// hint: you'll need a tmp variable for swaps
void reverse_array(int len, int* array){
  for(int i = 0; i < len/2; i++)
  {
    int temp = array[i];
    array[i] = array[len-1-i];
    array[len-1-i] = temp;
  }
}

//TODO PART 4: complete the randomize array function
// hint: random() returns a random number, but you want it to be in
//       the range of the length of the array. Try using modulo
// hint: try randomnly swapping all index with some other index
void randomize_array(int len, int* array){
  for(int i = 0; i < len; i++)
  {
    int randind = random() % len;
    int temp = array[randind];
    array[randind] = array[i];
    array[i] = temp;
  }
}

//TODO PART 5: complete the sort_arry function (smallest to biggest)
// hint: you'll probably need two for loops 
// hint: Check out insertion sort on wikipedia (it's ok to use that source)
void sort_array(int len, int* array){
  // bubble sort
  for(int j = 0; j < len; j++)
  {
    for(int i = 0; i < len-j-1; i++)
    {
      if(array[i] > array[i+1])
      {// swap the elements
        array[i  ] ^= array[i+1];
        array[i+1] ^= array[i  ];
        array[i  ] ^= array[i+1];
      }
    }
  }
}

int main(int argc, char *argv[]){

  int len=0;    //store the length of the array, initially 0 but will change
  int res;      //store the result of scanf() operations
  int choice;   //store the user choice for operations
  int i;        //an interator for loops

  srandom(1992);//seed random number generator

  printf("Enter the length:\n");

  //TODO PART 1: Requst how many numbers
  // hint: don't forget to return 1 on error
  if( !scanf("%d", &len) )
  {
    fprintf(stderr, "ERROR: Invalid input\n");
    exit(1);
  }

  int array[len]; //declare array now that we know its size


  printf("Enter %d numbers (space separated):\n",len);

  //TODO PART 1: Read in desired numbers
  // hint: don't forget to return 1 on error
  for(i = 0; i < len; i++)
  {
    if ( scanf("%d", &res) )
    { // if it reads something
      array[i] = res;
    }
    else
    {
      fprintf(stderr, "ERROR: Invalid input\n");
      exit(1);
    }
  }
  




  //while loop for operations, run until exit or EOF
  while(1){
    printf("Choose an operation:\n");
    printf("(0) : exit\n");
    printf("(1) : print array\n");
    printf("(2) : reverse array\n");
    printf("(3) : randomize array\n");
    printf("(4) : sort array\n");
    res = scanf("%d",&choice);

    //error check
    if(res == 0){
      char c;
      printf("ERROR: Invalid input. Choose again.\n");

      scanf("%c",&c);//clear stdin and continue
      continue;
    }else if(res == EOF){
      break;
    }

    //TODO: Complete funcation calls based on user choice
    //      - Properly use an if/else if/else block (or a case switch)
    //  
    //      - Each choice should call the appropriate function: 
    //      - print_array(), reverse_array(), randomize_array(), sort_array()
    //
    //      - Remember arrays and pointers in ways are the same, so you can
    //        pass a pointer to the array, as an argument.
    //
    //      - Because you don't know length ahead of time, you'll also need
    //        to pass the length of the array as an argument
    //
    //      - Refresh your memory on loop control, e.g., break and continue

    if (choice == 0){
      break;
    } //add more else if blocks for other choices, e.g., 1, 2, 3, and 4
    else if (choice == 1)
    {
      print_array(len, array);
    }
    else if (choice == 2)
    {
      reverse_array(len, array);
    }
    else if (choice == 3)
    {
      randomize_array(len, array);
    }
    else if (choice == 4)
    {
      sort_array(len, array);
    }
    else{
      printf("ERROR: Invalid number. Choose again.\n\n");
      continue;
    }
    
  }
  return 0; //return 0 on success

}
