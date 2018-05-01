#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

#include <cstring>

#include <openssl/sha.h>

using namespace std;
//using namespace NTL;


string decimalToHexical(int decimal_int){

  string hexString = "";
  stringstream ss;

  // convert to hex and store in hexString
  ss << hex << decimal_int;
  hexString = ss.str();

  return hexString;

}

bool isSpecialPoint(NTL::ZZ point)
{
  // ulong to store left most 64bits of point
  // SHA1 = 160 bits, to get 64 we get rid of 96 bits
  unsigned long LM64 = ((SHA1(point)) << 96);

  // Special point if LM64 is a number where first 10 leading bits are 0s
  // Biggest possible # is 0b0000000000111111111111111111111111111111111111111111111111111111
  // in decimal = 18014398509481983
  if( LM64 <= 18014398509481983 )
  {
	  return true;
  }
  else
  {
	  return false;
  }
}

int getStepsA(NTL::ZZ a, NTL::ZZ generator, NTL::ZZ modulus)
{
  // This func is to get # of steps for a to get to a special point

  int steps = 0;
  bool foundSpecial = false;
  NTL::ZZ pointToCheck = a;

  while(!(foundSpecial))
  {
    foundSpecial = isSpecialPoint(pointToCheck);
    if( isSpecialPoint(pointToCheck) )
    {
	    // pointToCheck is a special point
	    foundSpecial = true;
    }
    else
    {
	    // pointToCheck isn't a special point
	    // increment step
	    steps++;
	    // a = a * generator % modulus
	    NTL::MulMod(pointToCheck, pointToCheck, generator, modulus);
    }
  }

  return steps;
}

int getStepsB(NTL::ZZ b, NTL::ZZ generator, NTL::ZZ modulus)
{
  // Similar to getStepsA except we have to inverse b first
  NTL::ZZ pointToCheck = NTL::InvMod(b, modulus);

  return getStepsA(b, generator, modulus);
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
