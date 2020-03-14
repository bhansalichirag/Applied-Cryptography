
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "md5.h"

// input : ./prog filename
char word_list[] = {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'C', 'B', 'A', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '9', '2', '3', '4', '5', '6', '7', '8', '1', 'a', 'b', 'c', 'd'};
char pass[4]; // 4 character password
int *pass_pointer, *temp;
int n, result, *temp;
MD5_CTX mdContext; // needed to compute MD5

void shuffleWords()
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

check_pw(char *pass)
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
  n = read(0, pass_pointer, 4); // get 4 bytes, ignore extra
  int q = 1;
  while (q <= 62)
  {
    long long y = 62 * 62 * 62;
    //printf("inside %d\n", q);
    char qqq; // if password too short, will be detected later.
    switch (q)
    {
    case 1:
      qqq = 'a';
      break;
    case 2:
      qqq = 'b';
      break;
    case 3:
      qqq = 'c';
      break;
    case 4:
      qqq = 'd';
      break;
    case 5:
      qqq = 'e';
      break;
    case 6:
      qqq = 'f';
      break;
    case 7:
      qqq = 'g';
      break;
    case 8:
      qqq = 'h';
      break;
    case 9:
      qqq = 'i';
      break;
    case 10:
      qqq = 'j';
      break;
    case 11:
      qqq = 'k';
      break;
    case 12:
      qqq = 'l';
      break;
    case 13:
      qqq = 'm';
      break;
    case 14:
      qqq = 'n';
      break;
    case 15:
      qqq = 'o';
      break;
    case 16:
      qqq = 'p';
      break;
    case 17:
      qqq = 'q';
      break;
    case 18:
      qqq = 'r';
      break;
    case 19:
      qqq = 's';
      break;
    case 20:
      qqq = 't';
      break;
    case 21:
      qqq = 'u';
      break;
    case 22:
      qqq = 'v';
      break;
    case 23:
      qqq = 'w';
      break;
    case 24:
      qqq = 'x';
      break;
    case 25:
      qqq = 'y';
      break;
    case 26:
      qqq = 'z';
      break;
    case 27:
      qqq = 'A';
      break;
    case 28:
      qqq = 'B';
      break;
    case 29:
      qqq = 'C';
      break;
    case 30:
      qqq = 'D';
      break;
    case 31:
      qqq = 'E';
      break;
    case 32:
      qqq = 'F';
      break;
    case 33:
      qqq = 'G';
      break;
    case 34:
      qqq = 'H';
      break;
    case 35:
      qqq = 'I';
      break;
    case 36:
      qqq = 'J';
      break;
    case 37:
      qqq = 'K';
      break;
    case 38:
      qqq = 'L';
      break;
    case 39:
      qqq = 'M';
      break;
    case 40:
      qqq = 'N';
      break;
    case 41:
      qqq = 'O';
      break;
    case 42:
      qqq = 'P';
      break;
    case 43:
      qqq = 'Q';
      break;
    case 44:
      qqq = 'R';
      break;
    case 45:
      qqq = 'S';
      break;
    case 46:
      qqq = 'T';
      break;
    case 47:
      qqq = 'U';
      break;
    case 48:
      qqq = 'V';
      break;
    case 49:
      qqq = 'W';
      break;
    case 50:
      qqq = 'X';
      break;
    case 51:
      qqq = 'Y';
      break;
    case 52:
      qqq = 'Z';
      break;
    case 53:
      qqq = '0';
      break;
    case 54:
      qqq = '1';
      break;
    case 55:
      qqq = '2';
      break;
    case 56:
      qqq = '3';
      break;
    case 57:
      qqq = '4';
      break;
    case 58:
      qqq = '5';
      break;
    case 59:
      qqq = '6';
      break;
    case 60:
      qqq = '7';
      break;
    case 61:
      qqq = '8';
      break;
    case 62:
      qqq = '9';
      break;
    }
    for (int i = 0; i < 4; i++)
    {
      pass[i] = qqq;
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
      itoa(result, buffer, 2); // here 16 means Hexadecimal
      char temp_val[4];
      shuffleWords();
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          n = n * 10 + buffer[8 * i + j];
        }
        //printf("%c %lld %d\n",word_list[abs(convertBinaryToDecimal(n)) % 62],n,convertBinaryToDecimal(n) % 62);
        temp_val[i] = word_list[abs(convertBinaryToDecimal(n)) % 62];
        n = 0;
      }

if (result == 0x19fbc7c1 || result == 0x7e1d96fd || result == 0x88df723c || result == 0x3974cffc || result == 0x8f6bb61b || result == 0x8e564270 || result == 0x655ca818 || result == 0x58712b2b || result == 0x97e75d32 || result == 0x14928501)
      {
        printf("%s: %x\n", pass,result);
      }
      pass[0] = temp_val[2];
      pass[1] = temp_val[1];
      pass[3] = temp_val[0];
      pass[2] = temp_val[3];

      
      // printf("%s: %x\n", pass,result);
      y--;
    }
    //printf("%s\n", pass);
    // // print a human readable version of hash (using hex conversion)
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
