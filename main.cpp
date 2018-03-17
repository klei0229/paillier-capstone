#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "paillier.h"

using namespace std;
using namespace NTL;

ZZ lcm(ZZ x, ZZ y){
  ZZ ans = (x * y) / NTL::GCD(x,y);
  return ans;
}

int main()
{

    ZZ p = ZZ(43);
    ZZ q = ZZ(41);
    ZZ lambda = lcm(p - 1, q - 1);
    Paillier paillier(p*q, lambda);

    ZZ m = ZZ(10);
    ZZ n = p * q;

    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "n = " << n << endl;
    cout << "lamdba = " << lambda << endl;

    ZZ c = paillier.encrypt(m, (ZZ)131 );
    cout << "c = " << c << endl;
    ZZ m2 = paillier.decrypt(c);
    cout << "m2 = " << m2 << endl;

    if (m == m2){
        cout << "m = m2, encryption and decryption successful" << endl;
    }

    return 0;
}
