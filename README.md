# Applied-Cryptography
Fall 2019 Applied Cryptography

Project 1 : Implemented a modified Vignere ciphere, which is a polyalphabetic ciphere, with the help of Substitution and Permuation Boxes for decrypting and encrypting a 32bit block of data.
Also found the weaknesses to the cipher and calculated to time to took to find the key used in the process using brute force.

Project 2 : Given MD5 and encrypt, decrypt function, use cryptanalysis to find flaws in the process and try to exploit the same to find the key used for encryption.
Firstly, for brute force attack, we used the magic number of the file type to find the key, by starting key counting from 0000x and going on until we get the the specific magic number using the encrypted file.
After finding the flaw in the algorithm, the decipher takes way less time when compared to the brute force attack.

