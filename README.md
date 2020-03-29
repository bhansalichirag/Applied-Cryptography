# Applied-Cryptography
# Fall 2019 Applied Cryptography

# Objective and Implementation

Project 1 : 

Objective: Develop a reversible 32bit block encryption algo
           Utilize substitution and permutation in encryption
           Brute force a block encryption algorithm

Implemented a modified Vignere ciphere, which is a polyalphabetic ciphere, with the help of Substitution and Permutation Boxes for decrypting and encrypting a 32bit block of data.
Also found the weaknesses to the cipher and calculated the time it took to find the key used in the process using brute force attack.

Project 2 : 

Objective: Apply brute force techniques to an encrypted pdf, png image, and text file
           Perform a cryptanalysis on an encrypted pdf, png image, and text file

Given MD5 and encrypt, decrypt functions.
Firstly, for brute force attack, we used the magic number of the file type to find the key, by starting key counting from 0000x and going on until we get the specific magic number using the encrypted output file and decrypting it.

After analysing the code for all the given functions, found flaws in the algorithm, used it to find the required key for image, pdf and text and concluded that deciphering using cryptanalysis takes way less time when compared to the brute force attack for this project.

Project 3 :

Objective: Using the hash function used, find the passwords (unsalted) for the respective hashes using dictionary and rainbow table attack.

Using the hash function, firstly for the dictionary attack, generated all the 4 character long alphanumeric passwords (A-Z,a-z,0-9) and find the ones which have the hashes matching with the given required hashes.

For the rainbow table, we have a reduction function and a table of dimensions 62 * (62^3), and thus using the reduction function and the given hash function, computed the hashes and the intermediate passwords and found out the required passwords.

Project 4 : 

Objective: Write a program that encrypts data using symmetric encryption and MAC

For this project, we were asked to use the code given in the previous 2 projects, to create a MAC (message authentication code), which is used for authentication and integrity of the message, as any changes in the message will change the hash and the receiver would it easily able to detect the same, when the hashes wouldnt match.

Project 5 : 

Objective: Extract information about the digital certificate and use the private and public keys present in the certificate to encrypt and decrypt messages.

Used Python3 library X.509 and OpenSSL to extract and use the information from the certificate.

Project 6 : 

Objective: Understand and Implement Blind Signature.

Blind Signature is a concept where the sender signs a disguised/blinded message, used mainly in privacy related protocols and whee anonymity is required.

