//# input : ./prog filename key
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "md5.h"

int key; // symmetric key
int buf, n, infile, outfile;
int size, i, j;
int *temp, result;
int *pass_pointer;
int rollingkey;
MD5_CTX mdContext; // needed to compute MD5

encrypt(char *name)
{
    struct stat st;

    infile = open(name, O_RDONLY);
    if (infile < 0)
    {
        printf("input file %s open error\n", name);
        exit(0);
    }

    outfile = open("output_temp", O_RDWR | O_CREAT | O_TRUNC, 0700);
    if (outfile < 0)
    {
        printf("Cannot access file: output\n");
        exit(0);
    }

    // do the encryption, buf contains plaintext, and rollingkey contains key
    buf = 0;
    rollingkey = key;
    while ((n = read(infile, &buf, 4)) > 0)
    {
        buf = buf ^ rollingkey; //XOR with key, and put ciphertext in buf
        MD5Init(&mdContext);    // compute MD5 of rollingkey
        MD5Update(&mdContext, &rollingkey, 4);
        MD5Final(&mdContext);
        temp = (int *)&mdContext.digest[12];
        result = *temp; // result is 32 bits of MD5 of buf

        rollingkey = rollingkey ^ result; // new key
        write(outfile, &buf, 4);          // write ciphertext
        buf = 0;                          // rinse and repeat
    };
    close(infile);
    close(outfile);
    return (size);
};

//  function for determining the size of file
long int findSize(char file_name[])
{
    // opening the file in read mode
    FILE *fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL)
    {
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

CreateMAC(char buffer[50], int filesize)
{
    FILE *fp;

    char str[filesize]; //for storing the content of the output file
    int final_size = filesize + strlen(buffer);
    char final[final_size];
    pass_pointer = (int *)final; // get an int pointer to the password store
    *pass_pointer = 0;
    fp = fopen("output", "r"); //open and read the file
    if (fp == NULL)
    {
        printf("Could not open file output");
        return 1;
    }
    printf("\nContents\n");
    fgets(str, filesize, fp);
    fclose(fp);
    puts(str);

    strcpy(final, buffer); // copy buffer into the new var final
    strcat(final, str);    // add the file content

    printf("\nFinal Content\n");
    puts(final);
    
    pass_pointer = (int *)final; // get an int pointer to the password store
    MD5Init(&mdContext);         // compute MD5 of password
    MD5Update(&mdContext, pass_pointer, final_size);
    MD5Final(&mdContext);
    temp = (int *)&mdContext.digest[12];
    result = *temp; // result is 32 bits of MD5

    printf("\nResultant MAC: %x\n", result); 
}

main(int argc, char *argv[])
{
    if (argc != 3) ///ensuring that the arguments are there
    {
        //printf("Usage: %s <filename>\n", argv[0]);
        exit(0);
    };
    key = strtol(argv[2], NULL, 16);//atoi(argv[2]); //mykeygen(); // generate encryption key
    
    encrypt(argv[1]); // encrypt input file and place in "output"

    long int res = findSize("output"); //compute the file size
    if (res != -1)
        printf("Size of the file is %ld bytes \n", res);

    char buffer[50]; //for converting the integer to hexa and then string
    itoa(key, buffer, 16);
    
    CreateMAC(buffer, res);
    return 0;
};
