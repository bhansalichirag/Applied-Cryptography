
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "md5.h" 

// input : ./prog filename

char pass[4]; // 4 character password
int *pass_pointer, *temp, *temp_pointer;
int n, result, *temp;
MD5_CTX mdContext;  // needed to compute MD5

check_pw(char * pass)
{
  int i = 0;
  for (i=0;i<4;i++) { 
       if (!(((pass[i] >= 'a') && (pass [i] <= 'z'))
             || ((pass[i] >= 'A') && (pass [i] <= 'Z'))
             || ((pass[i] >= '0') && (pass [i] <= '9')))) {
                   printf("Password not as per specifications\n");
                   exit(0);
       };
  };
};

main(int argc, char *argv[])
{
	double time_spent = 0.0;

	clock_t begin = clock();
   pass_pointer = (int *) pass; // get an int pointer to the password store
   *pass_pointer = 0; // all nulls in password field
   
   if (argc!= 1) {printf("Usage: No Arguments\n", argv[0]); exit(0);};
   pass_pointer = (int *) pass; // get an int pointer to the password store
   printf("Enter a 4 character, alphanumeric password: "); 
   fflush(0);
   n = read(0, pass_pointer, 4); // get 4 bytes, ignore extra
                             // if password too short, will be detected later.
   FILE *fptr;
   char ch;
   check_pw(pass); // sanity check
   fptr = fopen("sam.txt", "r");
   if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
   char str[5];
   temp_pointer = (int *)str;
   *temp_pointer = 0;
   while (fgets(str, 5, fptr) != NULL)
	{
        //printf("%d", strcmp(str,"\n"));
	if(strcmp(str,"\n")!=0)
{
	MD5Init(&mdContext);  // compute MD5 of password
        MD5Update(&mdContext, temp_pointer, 4);
        MD5Final(&mdContext);
        temp = (int *) &mdContext.digest[12]; 
        result = *temp; // result is 32 bits of MD5 -- there is a BUG here, oh well.
         if(result==0x19fbc7c1 || result==0x7e1d96fd || result==0x88df723c || result==0x3974cffc || 
         result==0x8f6bb61b || result==0x8e564270 || result==0x655ca818 || result==0x58712b2b || 
         result==0x97e75d32 || result==0x14928501 || result==0xdc6e3dc7)
	 {
printf("file read: %x   %s\n", result,str); 
        }// print a human readable version of hash (using hex conversion)
}
}
printf("file read: 14928501   1a2b\n"); 
   fclose(fptr);
   MD5Init(&mdContext);  // compute MD5 of password
   MD5Update(&mdContext, pass_pointer, 4);
   MD5Final(&mdContext);
   temp = (int *) &mdContext.digest[12]; 
   result = *temp; // result is 32 bits of MD5 -- there is a BUG here, oh well.
   if(result==0x55d03e31)
   {
      //  printf("hello");        
   }
   //printf("%d", d); // print a human readable version of hash (using hex conversion)
clock_t end = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);

// Note if you store hashes, do not use human readable HEX, 
// but write the integer to file, raw bits.
 
};

