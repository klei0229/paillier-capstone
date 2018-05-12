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

#include <NTL/ZZ.h>
#include <openssl/sha.h>

using namespace std;
using namespace NTL;

string decimalToHexical(int decimal_int);
std::string zToString(const ZZ &z);
string decimalToHexical(int decimal_int);
std::string zToString(const ZZ &z);
string decimalToHexical(int decimal_int);
std::string zToString(const ZZ &z);
bool isSpecialPoint(ZZ number);
int getStepsA(NTL::ZZ a, NTL::ZZ generator, NTL::ZZ modulus);
int getStepsB(NTL::ZZ b, NTL::ZZ generator, NTL::ZZ modulus);
string hexConverter(char hexValue);
string hextoBinaryString(string hexString);
int maxConsecutiveZeroes(string String);
ZZ ddlog(ZZ a, ZZ g);

int maxConsecutiveZeroes(string String){
  int currentMax = 0;
  int answer = 0;
  for (int i = 0 ; i < String.length(); i++){

    if(String[i] == '0')
    {
      currentMax++;
    }
    else{
      if(currentMax > answer){
        answer = currentMax;
      }
      currentMax = 0;
    }
  }
  return answer;

}
string decimalToHexical(int decimal_int){

  string hexString = "";
  stringstream ss;

  // convert to hex and store in hexString
  ss << hex << decimal_int;
  hexString = ss.str();

  return hexString;

}

std::string zToString(const ZZ &z){
  std::stringstream buffer;
  buffer << z;
  return buffer.str();
}


bool isSpecialPoint(NTL::ZZ point)
{
  // ulong to store left most 64bits of point
  // SHA1 = 160 bits, to get 64 we get rid of 96 bits
  //unsigned long LM64 = ((SHA1(point)) << 96);

  string input = zToString(point);
  //convert zz point to string
  //cout << "input string: " << input << endl;
  //string to sha
  unsigned char hash[20];

  //sha1 expects a char input, input is in variable input (string version of ZZ Number)
  SHA1((unsigned char*)input.c_str(), input.size(), hash);

  //for debugging, the hash was displayed in its hex form
  string resultHexString = "";
       //returns the hash in decimal
       //convert the hash to string in hexidedicmal
       for(int i = 0; i < 20; ++i) {
           resultHexString = resultHexString + decimalToHexical(int(hash[i]));
       }

  //resultHexString contains the hash as string in hexidedicmal
        cout << resultHexString << endl;
  //sha to binary
  string resultBinaryString = hextoBinaryString(resultHexString);
  cout <<"binary string is "<< resultBinaryString << endl;

  bool isSpecial = true;
  for(int i = 0; i < 10; ++i)
  {
    if (resultBinaryString[i] == '1')
    {
      isSpecial = false;
    }
  }

  return isSpecial;
  //unsigned long LM64 = ((SHA1(point)) << 96);

  // Special point if LM64 is a number where first 10 leading bits are 0s
  // Biggest possible # is 0b0000000000111111111111111111111111111111111111111111111111111111
  // in decimal = 18014398509481983
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



// isspecialPoint should take the string version of a point ZZ
bool isSpecialPoint1(ZZ number)
{
  bool ret = false;

  string input = zToString(number);
  //convert zz point to string
  //cout << "input string: " << input << endl;
  //string to sha
  unsigned char hash[20];

  //sha1 expects a char input, input is in variable input (string version of ZZ Number)
  SHA1((unsigned char*)input.c_str(), input.size(), hash);

  //for debugging, the hash was displayed in its hex form
  string resultHexString = "";
       //returns the hash in decimal
       //convert the hash to string in hexidedicmal
       for(int i = 0; i < 20; ++i) {
           resultHexString = resultHexString + decimalToHexical(int(hash[i]));
       }

  //resultHexString contains the hash as string in hexidedicmal
        //cout << resultHexString << endl;
  //sha to binary
  string resultBinaryString = hextoBinaryString(resultHexString);
        //cout << resultBinaryString << endl;

  int maxZeroes = maxConsecutiveZeroes(resultBinaryString);
  //cout << maxZeroes << endl;

  if ( maxZeroes < 10){
    ret = false;
  }
  else
  //count consecutive 0's if >10 then return true
    {
      ret = true;
    }
    //cout <<"result " <<ret<<endl;
    return ret;
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



ZZ ddlog(ZZ a, ZZ g){

  ZZ steps = ZZ(0);
  while( isSpecialPoint(a) == false)
  {
    steps++;
    //number = a * g;
  }

  return steps;
}
int main(){
  ZZ answer = ZZ(0);
  ZZ a = ZZ(58439583);
  ZZ g = ZZ(54859348);
  ZZ modulus = ZZ(4942);
  answer = getStepsA(a,g,modulus);

  //cout << answer << endl;


  //new code
}
