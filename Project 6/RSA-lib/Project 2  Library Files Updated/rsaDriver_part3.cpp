#include "RSA.h"
#include "BigInt.h"
#include <cmath>
#include <iostream>
#define RAND_LIMIT32 0x7FFFFFFF
#define RAND_LIMIT16 0x7fff
using namespace RSAUtil;

int main(int argc, char *argv[])
{ /*********************************************************
 * A Simple Driver
 * *******************************************************
 */
  unsigned long int *a;
  unsigned long int arr[4];
  a = &arr[0];
  //part A
  BigInt pubkey, privatekey, modN;
  RSA Bob_rsa(44789,48449);
  RSA Alice_rsa;
  pubkey= Bob_rsa.getPublicKey();
  modN = Bob_rsa.getModulus();
  Alice_rsa.setN(modN);
  Alice_rsa.setPublicKey(pubkey);

  //part B
  int random_number = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT16);
  BigInt random_number_inverse = modInverse(random_number,modN);

  //part C
  BigInt message, cipher, message_times_encryptedvalue;
  message = int(((double)std::rand() / RAND_MAX) * RAND_LIMIT32);
  message.toULong(a, 4);

  //part D
  cipher = Alice_rsa.encrypt(random_number);

  //part E
  message_times_encryptedvalue = cipher * message;

  //part F
  message_times_encryptedvalue = message_times_encryptedvalue % modN;
  std::cout << *a << std::endl;
  //  std::cout<<"message "<<message.toString();
  std::cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << message_times_encryptedvalue.toHexString() << std::endl;

  //part G
  //function to Bob()

  //part H
  BigInt decrypt_message;
  decrypt_message = Bob_rsa.decrypt(message_times_encryptedvalue);

  //part I
  //function to Alice()

  //part J
  BigInt decrypted_withinverse;
  decrypted_withinverse = decrypt_message * random_number_inverse;
  decrypted_withinverse = decrypted_withinverse % modN;

  std::cout << "Result: " << decrypted_withinverse.toHexString() << "\toriginal message: " << Bob_rsa.encrypt(decrypted_withinverse).toHexString() << std::endl;

}


BigInt modInverse(int a, BigInt m){
	bool neg = false;
	BigInt b;
	BigInt u1,u2,u3,v1,v2,v3,t1,t2,t3,q;
	u1 = 1;
	u2 = 0;
	u3 = m;
	
	v1 = 0;
	v2 = 1;
	v3 = a;
	
	
	while(!((u3%v3).isZero())){
		q = (u3/v3);
		t1 = u1 - (q*v1);
		t2 = u2 - (q*v2);
		t3 = u3 - (q*v3);
		u1 = v1;
		u2 = v2;
		u3 = v3;
		v1 = t1;
		v2 = t2;
		v3 = t3;
		
	}
	
	//v2 is neg
	if (v2[BIGINT_SIZE-1]==1){
		//take 2's comp
		v2.flip();
		v2 = v2+1;
		neg = true;
	}
	
	b = v2%m;
	if(neg){
		b = m-b;
	}
	
return b;
}