
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "md5.h"


//Notes: Rainbow table matrix dimensions: 62 * 62^3
// input : ./prog filename
char word_list[] = {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'C', 'B', 'A', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '9', '2', '3', '4', '5', '6', '7', '8', '1', 'a', 'b', 'c', 'd'};
char ordered_list[] = {'a','b','c','d','e','f','g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A','B','C','D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0','1','2', '3', '4', '5', '6', '7', '8','9'};
char pass[4]; // 4 character password
int *pass_pointer, *temp;
int num, result, *temp;
MD5_CTX mdContext; // needed to compute MD5

void shuffleWords() //for shuffling the word list : reason : to get a new list after each iterations and more chances of getting a different 4 character word 
{
    int size = 62;
    if (size > 1)
    {
        int i;
        for (i = 0; i < size - 1; i++)
        {
        int j = rand() % 62; 
        const char temp = word_list[j];
        word_list[j] = word_list[i];
        word_list[i] = temp;
        }
    }
}

check_pw(char *pass)  //regex for password valid or not
{
  int i = 0;
  for (i = 0; i < 4; i++)
  {
    if (!(((pass[i] >= 'a') && (pass[i] <= 'z')) || ((pass[i] >= 'A') && (pass[i] <= 'Z')) || ((pass[i] >= '0') && (pass[i] <= '9'))))
    {
      printf("Password not as per specifications %c %c %c %c\n", pass[0], pass[1], pass[2], pass[3]);
      exit(0);
    };
  };
};

main(int argc, char *argv[])
{
double time_spent = 0.0;

	clock_t begin = clock();
  pass_pointer = (int *)pass; // get an int pointer to the password store
  *pass_pointer = 0;          // all nulls in password field
  if (argc != 1)
  {
    printf("Usage: No Arguments\n", argv[0]);
    exit(0);
  };
  pass_pointer = (int *)pass; // get an int pointer to the password store
  printf("Enter a 4 character, alphanumeric password: ");
  fflush(0);
  num = read(0, pass_pointer, 4); // get 4 bytes, ignore extra
  int counter = 1;
  while (counter <= 62)
  {
    long long y = 62 * 62 * 62;
    for (int i = 0; i < 4; i++)
    {
      pass[i] = ordered_list[counter];
    }
    while (y > 0)
    {
      // printf("%s\n",pass);
      check_pw(pass);      // sanity check
      MD5Init(&mdContext); // compute MD5 of password
      MD5Update(&mdContext, pass_pointer, 4);
      MD5Final(&mdContext);
      temp = (int *)&mdContext.digest[12];
      result = *temp; // result is 32 bits of MD5 -- there is a BUG here, oh well.
      char buffer[32];
      long long n;
      itoa(result, buffer, 2); //Converts an integer value to a null-terminated string buffer is the resultant binary string
      char temp_val[4];
      shuffleWords();
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          n = n * 10 + ((int)(buffer[8 * i + j])-48);
        }
        temp_val[i] = word_list[abs(convertBinaryToDecimal(n)) % 62];
        n = 0;
      }

      if (result == 0x19fbc7c1 || result == 0x7e1d96fd || result == 0x88df723c || result == 0x3974cffc || result == 0x8f6bb61b || result == 0x8e564270 || result == 0x655ca818 || result == 0x58712b2b || result == 0x97e75d32 || result == 0x14928501)
      {
        printf("%s: %x\n", pass,result);
      }

      //start Reduction function
      pass[0] = temp_val[2];
      pass[1] = temp_val[1];
      pass[3] = temp_val[0];
      pass[2] = temp_val[3];

      //end of reduction function
      
      y--;
    }
    q++;
  }
  // Note if you store hashes, do not use human readable HEX,
  // but write the integer to file, raw bits.
clock_t end = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);
};

int convertBinaryToDecimal(long long n)
{
  int decimalNumber = 0, i = 0, remainder;
  while (n != 0)
  {
    remainder = n % 10;
    n /= 10;
    decimalNumber += remainder * pow(2, i);
    ++i;
  }
  return decimalNumber;
}



// Note if you store hashes, do not use human readable HEX,
// but write the integer to file, raw bits.
