#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
#include "data.h"

using namespace std;
using namespace NTL;

ZZ stringToNumber(string str)
{
    ZZ number = conv<ZZ>(str[0]);
    long len = str.length();
    for(long i = 1; i < len; i++)
    {
        number *= 128;
        number += conv<ZZ>(str[i]);
    }

    return number;
}


int execute_server();
vector<Input> readInputFile(string filename);


int main()
{
  int answer;
  answer = execute_server();

    return 0;
}

int execute_server(){

  //initalize server databse to this following bit array of length 20
  bool server_db[20] = {0,1,0,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1};

  ZZ shareOne;
  ZZ shareLambda;

  vector<bool> server_db_vector;
  vector<Memory> pi_list;

  //Memory server_result = Memory();

  vector<Input> inputsfromClient;
  vector<Input> inputs;

  for (int i = 0 ; i < 20 ; i++)
  {
    server_db_vector.push_back(server_db[i]);
    //cout <<"i is : "<< server_db[i] << endl;
  }
  //get Values of Inputs
  //Inputs is a vector of Inputs of size 11.
  //<share1,sharelambda,input1, 8 Inputs from client>

  inputs = readInputFile("client_inputs.txt");
  //cout << "value is "<<inputs[0].value << endl;
  //cout << "first bit is "<<inputs[0].bits[0] << endl;
  //cout << "modulus is "<<inputs[0].modulus << endl;

  shareOne = ZZ(inputs[0].value);
  shareLambda = ZZ(inputs[1].value);
  Input inputOne = Input(inputs[2].value,inputs[2].bits,inputs[2].modulus);

  //calculate values of bigPi and store into vector pi_list


}

//Read file from Client
vector<Input> readInputFile(string filename){


  vector<Input> inputs;
  ZZ value;
  ZZ modulus;
  vector<NTL::ZZ> bits;


  NTL::ZZ currentBit;

  char c; //holds braces

  ifstream input_file(filename.c_str());

  if(input_file.is_open())
  {
    for(int i = 0; i < 11 ;i++){
      input_file.get(c); // check for {
        //cout << "c is" << c  << endl;
      input_file >> value; // get value
      cout << "value is"<< value << endl;
      for (int j = 0 ; j < 512 ; j++){  //get bits
        input_file >> currentBit;
        //cout << "current bit is "<< currentBit << endl;
        bits.push_back(currentBit);

    }
      //cout << "size of bits " << bits.size() << endl;

      input_file >> modulus; //get modulus
      input_file.get(c);
      //cout << "c is" << c  << endl;

      Input currentInput = Input(value,bits,modulus);
      inputs.push_back(currentInput);
    }
  }
  else cout << "Unable to open " << filename << endl;

  //cout << "first bit is "<<inputs[0].bits[0] << endl;

  return inputs;
}
