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

#include "paillier.h"
#include "ddlog.h"

using namespace std;
using namespace NTL;


int main(){
  //converts string version of message to ZZ value

  ZZ generator = ZZ(2);
  ZZ modulus = ZZ(9);
  ZZ number = ZZ(1);

  int answer = ddlog::getStepsA(number,generator,modulus);
  cout << answer << endl;



}
