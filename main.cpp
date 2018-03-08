#include <NTL/ZZ_pXFactoring.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std;
using namespace NTL;

/*
	To compile:
	g++ -g -O2 main2.cpp -o main -lntl -lgmp -lm

	compile on my vm:
	g++ -g -O2 -I/home/kevin/usr/local/include main2.cpp -o main -L/home/kevin/usr/local/lib/ -lntl -lgmp -lm

	To run:
	./main
*/

/*
	To do list:

	[x] moddiv - removed
	[x] inverseMod - NTL might have , INVMOD function provided by NTL
	[x] lcm -
	[ ] getRandom_G - use NTL for random
	[x] L_function
	[x] encrypt
	[x] decrypt
*/


/*
//DDLOG Procedure Functions
ZZ ddlog(ZZ a,ZZ delta,ZZ M,ZZ phi){
    ZZ i = ZZ(0);
    ZZ h = a;
    // natural log in NTL?

    ZZ T = 2*M*log(2/delta)/delta;

    while(delta(h) != 0 && i < T)
    {
        h = g*h;
        i = i + 1;
    }

    return i;
}
*/

//delta is the random function that returns a random integer from 0 to k-1
ZZ delta(ZZ k){
	ZZ r;
	r = RandomBnd(k);
	return r;
}
//


ZZ L_function(ZZ x,ZZ n){
	ZZ ans;	// Return Value

	ans = (x-1)/n;

	return ans;
}

ZZ encrypt(ZZ m, ZZ n, ZZ g)
{
	assert(0 <= m && m < n);
  	ZZ c;	// Return Value
  	ZZ r;	// Random Value


  	// Convert ZZ to long for power to work (might be a problem)
	long l_m; conv(l_m, m);
	long l_n; conv(l_n, n);

	// Create random # from 0 to n-1
	r = RandomBnd(n);
	//hardcoded r to 131 for testing
	r = ZZ(131);
	cout << "r = " << r << endl;

	// Computes power of stuff
	ZZ pow_g_m; power(pow_g_m, g, l_m);	// g^m
	ZZ pow_r_n; power(pow_r_n, r, l_n);	// r^n
	ZZ pow_n_2; power(pow_n_2, n, 2);	// n^2

	// Does the encryption
	c = MulMod(pow_g_m, pow_r_n, pow_n_2);	// c = ( (g^m)*(r^n) ) / n^2

	return c;
}

ZZ decrypt(ZZ c, ZZ lambda, ZZ mu, ZZ n){
	ZZ m;	// Return Value

	// Convert ZZ to long for power to work (might be a problem)
	long l_lambda; conv(l_lambda, lambda);

	// Computes power of stuff
	ZZ pow_c_lambda; power(pow_c_lambda, c, l_lambda);	// c^lambda
	ZZ pow_n_2; power(pow_n_2, n, 2);	// n^2

	// Just to do c^lambda % n^2
	//AddMod(pow_c_lambda, pow_c_lambda, 0, pow_n_2);

	//a2,a3 are temp varibales to process formula m = (L(c^lambda mod n^2)*mu) mod n
	ZZ a2 =  ZZ(MulMod(pow_c_lambda, 1, pow_n_2));	// a1 = ( (g^lambda) / n^2)
	ZZ a3 = L_function(a2,n);

	m = ZZ(MulMod(a3, mu, n));	// a1 = ( (g^lambda) / n^2)
	return m;
}

ZZ lcm(ZZ x, ZZ y){

  ZZ ans = (x * y) / (__gcd(x,y));

  return ans;

}

int main()
{

	ZZ p = ZZ(43);
	ZZ q = ZZ(41);

	assert(__gcd(p*q,(p-1)*(q-1)) == 1);

	ZZ m = ZZ(10);
	//ZZ n = ZZ(1763);
	ZZ n = ZZ(p*q);
	ZZ g = ZZ(107);
	ZZ lambda = lcm(p-1,q-1);

	// Computes power of stuff
	long l_lambda; conv(l_lambda, lambda);

	ZZ pow_g_lambda; power(pow_g_lambda, g, l_lambda);	// g^lambda
	ZZ pow_n_2; power(pow_n_2, n, 2);	// n^2

	//==============
	//calculations for mu
	//step 1, mul mod g inside L Function
	ZZ a1 =  ZZ(MulMod(pow_g_lambda, 1, pow_n_2));	// a1 = ( (g^lambda) / n^2)
	//compute L function on a1
	ZZ a2 = ZZ(L_function(a1,n));
	ZZ mu = ZZ(0);

	//InvMod changes the value of input parameter mu
	InvMod(mu,a2,n);
	//==============


	cout << "p = " << p << endl;
  cout << "q = " << q << endl;
  cout << "n = " << n << endl;
	cout << "mu = " << mu << endl;
  cout << "lamdba = " << lambda << endl;
  cout << "g = " << g << endl;
  cout << "mu = " << mu << endl << endl;

	ZZ c = encrypt(m, n, g);
	cout << "c = " << c << endl;
	ZZ m2 = decrypt(c,lambda,mu,n);
	cout << "m2 = " << m2 << endl;

	if (m == m2){
		cout << "m = m2, encryption and decryption successful" << endl;

	}
	return 0;
}
