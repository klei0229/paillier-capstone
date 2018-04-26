#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <iostream>
#include <fstream>

#include <iomanip>

#include <cstring>

#include <openssl/sha.h>

using namespace std;
//using namespace NTL;


string decimalToHexical(int decimal_int){

  int quotient = decimal_int;
  int remainder_val;

  string hexString = "";
  string hex_remainder;

  while(quotient != 0){

    remainder_val = quotient%16;

    if(remainder_val == 0) hex_remainder ="0";
    else if (remainder_val == 1) hex_remainder = "1";
    else if (remainder_val == 2) hex_remainder = "2";
    else if (remainder_val == 3) hex_remainder = "3";
    else if (remainder_val == 4) hex_remainder = "4";
    else if (remainder_val == 5) hex_remainder = "5";
    else if (remainder_val == 6) hex_remainder = "6";
    else if (remainder_val == 7) hex_remainder = "7";
    else if (remainder_val == 8) hex_remainder = "8";
    else if (remainder_val == 9) hex_remainder = "9";
    else if (remainder_val == 10) hex_remainder = "a";
    else if (remainder_val == 11) hex_remainder = "b";
    else if (remainder_val == 12) hex_remainder = "c";
    else if (remainder_val == 13) hex_remainder = "d";
    else if (remainder_val == 14) hex_remainder = "e";
    else hex_remainder = "F";

    hexString.insert(0,hex_remainder);

    //cout << hex_remainder << endl;

    quotient = quotient/16;

  }

  //cout << hexString << endl;
  return hexString;

}

bool isSpecialPoint(string binaryString){

  int zeroCounter = 0;
  int oneCounter = 0;

  //cout << binaryString.length() << endl;
  for (int i = 0 ; i < binaryString.length() ; i++)
  {
    //cout << binaryString[i] << endl;
    if (binaryString[i] == '0')
    {
      zeroCounter++;

    }

    else if (binaryString[i] == '1')
    {
      oneCounter++;
    }
    else
     {
       cout << "recieved non binary input" << endl;
     }
  }
    cout << "zeroes: " << zeroCounter << endl;
    cout << "ones: " << oneCounter << endl;

    if (zeroCounter > 10){
      return true;
    }
    else
     return false;
}
string hexConverter(char hexValue)
{
  string returnValue;

  if(hexValue == '0') returnValue = "0000";
  else if (hexValue == '1') returnValue = "0001";
  else if (hexValue == '2') returnValue = "0010";
  else if (hexValue == '3') returnValue = "0011";
  else if (hexValue == '4') returnValue = "0100";
  else if (hexValue == '5') returnValue = "0101";
  else if (hexValue == '6') returnValue = "0110";
  else if (hexValue == '7') returnValue = "0111";
  else if (hexValue == '8') returnValue = "1000";
  else if (hexValue == '9') returnValue = "1001";
  else if (hexValue == 'a') returnValue = "1010";
  else if (hexValue == 'b') returnValue = "1011";
  else if (hexValue == 'c') returnValue = "1100";
  else if (hexValue == 'd') returnValue = "1101";
  else if (hexValue == 'e') returnValue = "1110";
  else if (hexValue == 'f') returnValue = "1111";
  else returnValue = "----";

  return returnValue;


}

string hextoBinaryString(string hexString){

  string binaryString = "";

  for (int i = 0 ; i < hexString.length(); i++){
    binaryString = binaryString + hexConverter(hexString[i]);
  }


  return binaryString;
}

int main(){

  //g++ ddlog.cpp -lcrypto
  //get ZZ a, b

  //sha256(a) sha256(b)

  //take hash and shortern to 100 bits

  //based off 100 bits , determine if is specialpoint
  //cout << sha256('a") << endl;

  //cout << "ddlog test" << endl;

    // unsigned char digest[SHA_DIGEST_LENGTH];
    // const char* text = "4";
    //
    // SHA_CTX ctx;
    // SHA1_Init(&ctx);
    // SHA1_Update(&ctx, text, strlen(text));
    // SHA1_Final(digest, &ctx);
    //
    // char mdString[SHA_DIGEST_LENGTH*2+1];
    // for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
    // {
    //     sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    // }


    //cout << "decimal to hex "<< decimalToHexical(7562) << endl;

    string input;

       // a sha1 hash is 20 bytes
       unsigned char hash[20];

       cout << "enter your string input a: ";
       getline(cin, input);

       // compute the sha1 of the input, and store it our  hash array
       SHA1((unsigned char*)input.c_str(), input.size(), hash);
       // the above is the exact same thing as doing:
       //    SHA_CTX ctx;
       //
       //    SHA1_Init(&ctx);
       //    SHA1_Update(&ctx, input.c_str(), input.size());
       //    SHA1_Final(hash, &ctx);

       // since the hash array just contains a bunch of bytes,
       // print them as hexadecimal values
       string resultHexString =  "";
       //cout << "the hash was: ";


       //returns the hash in decimal
       //convert the hash to string in hexidedicmal
       for(int i = 0; i < 20; ++i) {
           resultHexString = resultHexString + decimalToHexical(int(hash[i]));
       }
      // cout <<"output"<< hexString1<<  endl;



    //printf("SHA1 digest: %s\n", mdString);

    //recieve string result from sha1

    //change to ZZ
    int a = 1;

    //string resultHexString =  "1b6453892473a467d07372d45eb05abc2031647a";

    string resultBinaryString = hextoBinaryString(resultHexString);


    //calculate if is specialNumber

    cout << "hexidecimal result: "<<resultHexString << endl;
    cout << "binary result: "<< resultBinaryString << endl;

    int generator;
    int a_steps = 0;
    //start testing for specialPoint
  //  bool result = isSpecialPoint(resultBinaryString);
    while ( !(isSpecialPoint(resultBinaryString)) ){
      a_steps++;
      a = a*generator;
      //resultHexString= sha1(a);
      //resultBinaryString = hextoBinary(resultHexString);
    }


    cout << a_steps << endl;
    //this block goes into a loop once sha1 works

}
