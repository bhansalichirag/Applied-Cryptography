#include "RSA.h"
#include "BigInt.h"
#include <cmath>
#include <iostream>
#define RAND_LIMIT32 0x7FFFFFFF
using namespace RSAUtil;

int main(int argc, char *argv[])
{ /*********************************************************
 * A Simple Driver
 * *******************************************************
 */
  // for (int i = 0; i < 5; i++)
  // {
  //   unsigned long int *a;
  //   unsigned long int arr[4];
  //   a = &arr[0];

  //   unsigned long int *a2;
  //   unsigned long int arr2[4];
  //   a2 = &arr2[0];

  //   RSA myRSA;
  //   RSA myRSA2;
  //   BigInt message, cipher, deciphered;
  //   BigInt message2, cipher2, deciphered2;

  //   message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
  //   message.toULong(a, 4);
  //   cipher = myRSA.encrypt(message);
  //   deciphered = myRSA.decrypt(cipher);
  //   //std::cout << *a << std::endl;

  //   message2 = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
  //   message2.toULong(a, 4);
  //   cipher2 = myRSA2.encrypt(message);
  //   deciphered2 = myRSA2.decrypt(cipher);
  //   //std::cout << *a2 << std::endl;

  //   std::cout << "message: " << 2*i <<"   "<< message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
  //   std::cout << "message2: " << 2*i+1 <<"   "<< message2.toHexString() << "\tcipher: " << cipher2.toHexString() << "\tdeciphered: " << deciphered2.toHexString() << std::endl;
  // }

//   unsigned long int *a;
//   unsigned long int arr[4];
//   a = &arr[0];

//   RSA myRSA(45482,36002);
//   BigInt message, cipher, deciphered;
//   message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
//   message.toULong(a, 4);
//   cipher = myRSA.encrypt(message);
//   deciphered = myRSA.decrypt(cipher);
//   //std::cout << *a << std::endl;
//   std::cout << "\tQ:" << myRSA.getQ() << "\tP:" << myRSA.getP() <<std::endl;
//   //std::cout << "\tPublic: " << myRSA.getPublicKey;
//   std::cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
//  // myRSA.~RSA;
//   RSA myRSA2(47624,32000);
//   message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
//   message.toULong(a, 4);
//   cipher = myRSA2.encrypt(message);
//   deciphered = myRSA2.decrypt(cipher);
//   //std::cout << *a << std::endl;
//   std::cout << "\tQ:" << myRSA2.getQ() << "\tP:" << myRSA2.getP() <<std::endl;
//   //std::cout << "\tPublic:" << myRSA.getPublicKey <<std::endl;
//   std::cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
  //myRSA.~RSA;
}
