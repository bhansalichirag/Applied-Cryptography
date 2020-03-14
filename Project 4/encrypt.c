
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "md5.h" 

// input : ./prog filename

int key; // symmetric key
int buf, n, infile, outfile;
int size,i,j;
  int *temp, result; 	
  int *pass_pointer;  
  int rollingkey; 
MD5_CTX mdContext;  // needed to compute MD5

encrypt(char *name)
{ 
  struct stat st;
     
  // priliminaries, get files ready and sized
  infile = open (name, O_RDONLY);
  if (infile<0) { printf("input file %s open error\n", name); exit(0); }
  
  outfile = open ("output", O_RDWR|O_CREAT|O_TRUNC, 0700);
  if (outfile<0) { printf("Cannot access file: output\n"); exit(0); }
  
  //stat(name, &st); size = 1048576;//st.st_size;
  //if (size <4) {printf("input file too small\n"); exit(0);}; 
  //write(outfile,&size,4); // write input file size to output  //commented on 29th Oct 2019 extra 4 bytes of data in the output file remove it
  
  // do the encryption, buf contains plaintext, and rollingkey contains key
  buf = 0;
  rollingkey = key;  
  while ((n = read(infile, &buf, 4)) > 0 ) {
         buf = buf ^ rollingkey; //XOR with key, and put ciphertext in buf
   MD5Init(&mdContext);  // compute MD5 of rollingkey
   MD5Update(&mdContext, &rollingkey, 4);
   MD5Final(&mdContext);
   temp = (int *) &mdContext.digest[12]; 
   result = *temp; // result is 32 bits of MD5 of buf
   
   rollingkey = rollingkey ^ result; // new key
   write(outfile, &buf, 4);  // write ciphertext
   buf = 0; // rinse and repeat
  };
  close(infile); close(outfile);
  return(size);
};

mykeygen() // generate a key, from system entropy
{ 
  int fd = open("/dev/urandom", O_RDONLY);
  read(fd, &buf, 4);
  return(buf);
}

long int findSize(char file_name[]) 
{ 
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "r"); 
  
    // checking if the file exist or not 
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
  
    fseek(fp, 0L, SEEK_END); 
  
    // calculating the size of the file 
    long int res = ftell(fp); 
  
    // closing the file 
    fclose(fp); 
  
    return res; 
} 

showcontent()
{
FILE *fp;

    char str[1024];
    char str1[8];
    char final[1032];
pass_pointer = (int *) final; // get an int pointer to the password store
*pass_pointer = 0;
fp = fopen("key", "r");
    if (fp == NULL){
        printf("Could not open file output");
        return 1;
    }
printf("\nContents\n");
    while (fgets(str1, 8, fp) != NULL)
    //    printf("%s", str);
    fclose(fp);

fp = fopen("key", "r");
while(fgets(str,1024,fp) != NULL)
fclose(fp);

strcpy(final, str1); /* copy name into the new var */
strcat(final, str); /* add the extension */


pass_pointer = (int *) final; // get an int pointer to the password store
MD5Init(&mdContext);  // compute MD5 of password
   MD5Update(&mdContext, pass_pointer, 1032);
   MD5Final(&mdContext);
   temp = (int *) &mdContext.digest[12]; 
   result = *temp; // result is 32 bits of MD5 -- there is a BUG here, oh well.

   printf("\nResultant hash: %x\n", result); // print a human readable version of hash (using hex conversion)

}

main(int argc, char *argv[])
{
 if (argc!= 3) {printf("Usage: %s <filename>\n", argv[0]); exit(0);};
 key = atoi(argv[2]);//mykeygen(); // generate encryption key
 printf ("key: %x  <needed for decryption>\n", key);

 //encrypt(argv[1]); // encrypt input file and place in "output"

  long int res = findSize("key"); 
    if (res != -1) 
        printf("Size of the file is %ld bytes \n", res); 
   showcontent();
    return 0;
};

