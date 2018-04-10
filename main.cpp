#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <iostream>
#include <fstream>

#include "paillier.h"

using namespace std;
using namespace NTL;

ZZ lcm(ZZ x, ZZ y){
  ZZ ans = (x * y) / NTL::GCD(x,y);
  return ans;
}

/*
 *Function stringToNumber converts a string containing all digits into a
 *number of type ZZ

 *Input: String
 *Output: number in ZZ


  *How it works:
  *1)intereate through each char in str,
  *2)convert the ascii value of each char into the integer value (temp)
  *3) add the integer value into var number (number = temp*(10^digit_place)
 */
NTL::ZZ stringToNumber(string str)

{
  long len = str.length();
  ZZ number = ZZ(0); //initialize the return val :number as 0;
  ZZ a = ZZ(10);  //used to calculate digitplace multiplier
  int digit_place = 0;



  for (int i = 0; i < len; i++)
  {
    ZZ temp = conv<ZZ>(str[len-1-i]); //interates from str[len-1] to str[0]

    temp -= 48; //ascii conversion of value temp

    //Calculates (number = temp*(10^digit_place))
    ZZ multiplier;
    NTL::power(multiplier,a,digit_place);
    temp *= multiplier;
    number += temp;
    //========================
    digit_place++;
  }
  //cout << "number is " << number << endl;
  return number;
}




int main()
{
    //===============
    //commented this section in order to test paillier default constructor
     //ZZ p = ZZ(43);
     //ZZ q = ZZ(41);
     //ZZ lambda = lcm(p - 1, q - 1);
    //Paillier paillier(p*q, lambda);

    //initialize paillier object with default constructor

    //Paillier paillier;


    //ZZ m = ZZ(10);

    //===============
    //Paillier paillier();
    ZZ m;

    cout << "Pailller Cryptosystem" << endl;
    cout << "1) Encrypt message.txt" << endl;
    cout << "2) Decrypt cipher.txt" << endl;

    int userInput = 0;
    cin >> userInput;

    if(userInput == 1)
    {
      //encrypt
        cout << endl <<"Encrypting message.txt and writing cipher into cipher.txt" << endl;
        string line;
        ifstream message_file("message.txt");

        if(message_file.is_open())
        {

          getline(message_file,line);
          cout << "Message.txt contains: "<<line << endl;

          //converts string version of message to ZZ value
          ZZ message_ZZ = ZZ(stringToNumber(line));
          Paillier paillier;

          ZZ modulus = paillier.getModulus();
          ZZ generator = paillier.getGenerator();

          ZZ lambda = paillier.getLambda();
          ZZ lambdaInverse = paillier.getLambdaInverse();

          ZZ cipher = paillier.encrypt(message_ZZ);

          ofstream public_key_file("public_key.txt");
          ofstream private_key_file("private_key.txt");

          if(public_key_file.is_open())
          {
            public_key_file << modulus << endl;
            public_key_file << generator << endl;

            cout << "Modulus and Generator stored in public_key.txt"<< endl;
            public_key_file.close();
          }
          else cout << "Unable to open public_key.txt";

          if(private_key_file.is_open())
          {
            private_key_file << lambda << endl;
            private_key_file << lambdaInverse << endl;

            cout << "Lambda and lambda Inverse stored in private_key.txt"<< endl;
            private_key_file.close();
          }
          else cout << "Unable to open private_key.txt";


          ofstream cipher_file ("cipher.txt");
          if(cipher_file.is_open())
          {
            cipher_file << cipher;
            cout << "Encrypted message stores in cipher.txt"<< endl;
            cipher_file.close();
          }

          else cout << "Unable to open cipher.txt";
          message_file.close();
        }
        else cout << "Unable to open message.txt";
    }

    else if (userInput ==2)
    {
        //decrypt
        cout << "Decrypting cipher.txt and writing message into message.txt" << endl;


        ZZ message_ZZ;
        Paillier paillier;

        ZZ modulus;
        ZZ generator;
        ZZ lambda;
        ZZ lambdaInverse;

        ZZ cipher;

        string line;
        ifstream cipher_file ("cipher.txt");
        if(cipher_file.is_open())
        {

          getline(cipher_file,line);

          cipher = ZZ(stringToNumber(line));
          cipher_file.close();
        }

        else{
          cout << "Unable to open cipher.txt" << endl;
        }

        ifstream public_key_file ("public_key.txt");
        if(public_key_file.is_open())
        {

          getline(public_key_file,line);
          modulus = ZZ(stringToNumber(line));
          getline(public_key_file,line);
          generator = ZZ(stringToNumber(line));
          public_key_file.close();
        }
        else{
          cout << "Unable to open public_key.txt" << endl;
        }

        ifstream private_key_file ("private_key.txt");
        if(private_key_file.is_open())
        {

          getline(private_key_file,line);
          lambda = ZZ(stringToNumber(line));
          getline(private_key_file,line);
          lambdaInverse = ZZ(stringToNumber(line));
          private_key_file.close();
        }

        else{
          cout << "Unable to open private_key.txt" << endl;
        }

        paillier.setLambda(lambda);
        paillier.setModulus(modulus);
        paillier.setLambdaInverse(lambdaInverse);
        paillier.setGenerator(generator);


        //cout << "modulus" << modulus << endl;
        //cout << "generator" << generator << endl;
        //cout << "lambda" << lambda << endl;
        //cout << "lambdaInverse" << lambdaInverse << endl;

        message_ZZ = paillier.decrypt(cipher);
        cout << "decrypted message is " << message_ZZ << endl;
        cout << "Message m is stored back into message.txt" << endl;

        ofstream message_file ("message.txt");
        if(message_file.is_open())
        {
          message_file << message_ZZ;
          message_file.close();
        }

        else cout << "Unable to open message.txt";

      }





    // ZZ p = ZZ(paillier.getP());
    // ZZ q = paillier.getQ();
    // ZZ lambda = paillier.getLambda();
    // ZZ n = paillier.getModulus();
    //
    // cout << "p = " << p << endl;
    // cout << "q = " << q << endl;
    // cout << "n = " << n << endl;
    // cout << "lamdba = " << lambda << endl;
    //
    // ZZ c = paillier.encrypt(m, (ZZ)131 );22
    // cout << "c = " << c << endl;
    // ZZ m2 = paillier.decrypt(c);
    // cout << "m2 = " << m2 << endl;
    //
    // if (m == m2){
    //     cout << "m = m2, encryption and decryption successful" << endl;
    // }

    return 0;
}
