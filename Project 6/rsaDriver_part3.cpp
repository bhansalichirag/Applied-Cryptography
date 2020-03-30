#include "RSA.h"
#include "BigInt.h"
#include <cmath>
#include <iostream>
#define RAND_LIMIT32 0x7FFFFFFF
#define RAND_LIMIT16 0x7fff
using namespace RSAUtil;

  BigInt pubkey, modN;
  RSA Bob_rsa;
  RSA Alice_rsa;

void Part1()
{
  //for 10 instances without arguments
  std::cout << "10 instances with no arguments" << std::endl;
  for (int i = 1; i <= 10; i++)
  {
    RSA myRSA;  //Its public-key cryptosystems and is widely used for data transmission
    BigInt message, cipher; // deciphered;

    message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
    cipher = myRSA.encrypt(message);
    //deciphered = myRSA.decrypt(cipher);

    std::cout << "message: " << i << "   " << message.toHexString() << "\tcipher: " << cipher.toHexString() << std::endl;
  }
  //for 5 instances with 1 arguments
  std::cout << "5 instances with 1 prime argument" << std::endl;
  int arr[10] = {35521,35527,35531,35533,35537,35543,35569,35573,35591,35593};
  for (int i = 0; i < 5; i++)
  {
    RSA myRSA(arr[i]);
    BigInt message, cipher, deciphered;

    message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
    cipher = myRSA.encrypt(message);
    deciphered = myRSA.decrypt(cipher);

    std::cout << "message: " << i << "   " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
  }

  std::cout << "5 instances with 2 prime arguments" << std::endl;
  for (int i = 0; i < 5; i++)
  {
    RSA myRSA(35521,35527);
    BigInt message, cipher, deciphered;

    message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
    cipher = myRSA.encrypt(message);
    deciphered = myRSA.decrypt(cipher);

    std::cout << "message: " << i << "   " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
  }

  std::cout << "10 instances with 2 non prime arguments" << std::endl;
  for (int i = 0; i < 10; i++)
  {
    RSA myRSA(30000+i,30000+2*i);
    BigInt message, cipher, deciphered;

    message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
    cipher = myRSA.encrypt(message);
    deciphered = myRSA.decrypt(cipher);

    std::cout << "message: " << i << "   " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
  }
}

void Part2()
{
  BigInt pubkey, privatekey, modN;
  std::cout << "Part2 Challenge Response" << std::endl;
  RSA RSA1;
  RSA RSA2;
  pubkey = RSA1.getPublicKey();
  modN = RSA1.getModulus();
  RSA2.setN(modN);
  RSA2.setPublicKey(pubkey);
  
  BigInt message, cipher, deciphered;
  message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
  cipher = RSA2.encrypt(message);
  deciphered = RSA1.decrypt(cipher);
  std::cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
}

BigInt SendEncryptedToBob(BigInt message_times_encryptedvalue) 
{
  BigInt decrypt_message = Bob_rsa.decrypt(message_times_encryptedvalue);
  return decrypt_message;
}

BigInt SendDecryptedToAlice(BigInt decrypt_message, BigInt random_number_inverse){
  BigInt decrypted_withinverse;
  decrypted_withinverse = decrypt_message * random_number_inverse;
  decrypted_withinverse = decrypted_withinverse % modN;
  return decrypted_withinverse;
}

int main(int argc, char *argv[])
{ 
  //Part1();
  //Part2();
  unsigned long int *a;
  unsigned long int arr[4];
  a = &arr[0];
  
  pubkey = Bob_rsa.getPublicKey();
  modN = Bob_rsa.getModulus();
  Alice_rsa.setN(modN);
  Alice_rsa.setPublicKey(pubkey);

  int random_number = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT16);
  std::cout<< "random number generated:  " << random_number << std::endl;
  BigInt random_number_inverse = modInverse(random_number, modN);

  BigInt message, cipher, message_times_encryptedvalue;
  message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
  message.toULong(a, 4);

  cipher = Alice_rsa.encrypt(random_number);

  message_times_encryptedvalue = cipher * message;

  message_times_encryptedvalue = message_times_encryptedvalue % modN;
  std::cout <<"Messsage generated (BigInteger): " << *a << std::endl;
  std::cout << "message: " << message.toHexString() << std::endl;

  BigInt decrypt_message;
  std::cout<<"Encrypted msg sent to Bob"<<std::endl;
  decrypt_message = SendEncryptedToBob(message_times_encryptedvalue);
  
  //function to Alice()
  std::cout<<"Decrypted msg sent to Alice"<<std::endl;
  BigInt decrypted_withinverse = SendDecryptedToAlice(decrypt_message,random_number_inverse);

  std::cout << "Result (signed message): " << decrypted_withinverse.toHexString() << std::endl;
  std::cout << "\toriginal message: " << Bob_rsa.encrypt(decrypted_withinverse).toHexString() << std::endl;
}

BigInt modInverse(int a, BigInt m)
{
  bool neg = false;
  BigInt b;
  BigInt u1, u2, u3, v1, v2, v3, t1, t2, t3, q;
  u1 = 1;
  u2 = 0;
  u3 = m;

  v1 = 0;
  v2 = 1;
  v3 = a;

  while (!((u3 % v3).isZero()))
  {
    q = (u3 / v3);
    t1 = u1 - (q * v1);
    t2 = u2 - (q * v2);
    t3 = u3 - (q * v3);
    u1 = v1;
    u2 = v2;
    u3 = v3;
    v1 = t1;
    v2 = t2;
    v3 = t3;
  }

  //v2 is neg
  if (v2[BIGINT_SIZE - 1] == 1)
  {
    //take 2's comp
    v2.flip();
    v2 = v2 + 1;
    neg = true;
  }

  b = v2 % m;
  if (neg)
  {
    b = m - b;
  }

  return b;
}

