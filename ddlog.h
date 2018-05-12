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

namespace ddlog{
    int getStepsA(NTL::ZZ a, NTL::ZZ generator, NTL::ZZ modulus);
    int getStepsB(NTL::ZZ b, NTL::ZZ generator, NTL::ZZ modulus);

    std::string decimalToHexical(int decimal_int);
    std::string zToString(const ZZ &z);
    bool isSpecialPoint(ZZ number);
    string hexConverter(char hexValue);
    string hextoBinaryString(string hexString);
}
