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
  unsigned long int *a;
  unsigned long int arr[4];
  a = &arr[0];

  BigInt pubkey, privatekey, modN;
  RSA RSA1;//(44789,48449);
  RSA RSA2;
  pubkey= RSA1.getPublicKey();
  modN = RSA1.getModulus();
  RSA2.setN(modN);
  RSA2.setPublicKey(pubkey);
  
  BigInt message, cipher, deciphered;
  message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
  message.toULong(a, 4);
  cipher = RSA2.encrypt(message);
  deciphered = RSA1.decrypt(cipher);
  std::cout << *a << std::endl;
  //  std::cout<<"message "<<message.toString();
  std::cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() << std::endl;
}
