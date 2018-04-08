#include "paillier.h"

using namespace std;

NTL::ZZ generateCoprimeNumber(const NTL::ZZ& n) {
    NTL::ZZ ret;
    while (true) {
        ret = RandomBnd(n);
        if (NTL::GCD(ret, n) == 1) { return ret; }
    }
}

Paillier::Paillier() {

    //cout << "called constructor" << endl;
    /* Length in bits. */
    long keyLength = 512;
    NTL::ZZ p, q;

    GenPrimePair(p, q, keyLength);

    P = p;
    Q = q;

    modulus = p * q;
    generator = modulus + 1;
    NTL::ZZ phi = (p - 1) * (q - 1);
    // LCM(p, q) = p * q / GCD(p, q);
    lambda = phi / NTL::GCD(p - 1, q - 1);
    lambdaInverse = NTL::InvMod(lambda, modulus);
    //cout << "end constructor" << endl;
    //cout << P << " " << Q << " "<< modulus << " " << lambda << " " <<endl;
}

Paillier::Paillier(const NTL::ZZ& modulus, const NTL::ZZ& lambda) {
  cout << "called" << endl;
    this->modulus = modulus;
    generator = this->modulus + 1;
    this->lambda = lambda;
    lambdaInverse = NTL::InvMod(this->lambda, this->modulus);
}

void Paillier::GenPrimePair(NTL::ZZ& p, NTL::ZZ& q,
                               long keyLength) {
    while (true) {
        long err = 80;
        p = NTL::GenPrime_ZZ(keyLength/2, err);
        q = NTL::GenPrime_ZZ(keyLength/2, err);
        NTL::ZZ n = p * q;
        NTL::ZZ phi = (p - 1) * (q - 1);

        //cout << "P: " << p << endl;
        //cout << "Q: " << q <<endl;

        if (NTL::GCD(n, phi) == 1) return;
    }
}

NTL::ZZ Paillier::encrypt(const NTL::ZZ& message) {
    NTL::ZZ random = generateCoprimeNumber(modulus);
    NTL::ZZ ciphertext =
        NTL::PowerMod(generator, message, modulus * modulus) *
        NTL::PowerMod(random, modulus, modulus * modulus);
    return ciphertext % (modulus * modulus);
}

NTL::ZZ Paillier::encrypt(const NTL::ZZ& message, const NTL::ZZ& random) {
    NTL::ZZ ciphertext =
        NTL::PowerMod(generator, message, modulus * modulus) *
        NTL::PowerMod(random, modulus, modulus * modulus);
    return ciphertext % (modulus * modulus);
}


NTL::ZZ Paillier::decrypt(const NTL::ZZ& ciphertext) {
    /* NOTE: NTL::PowerMod will fail if the first input is too large
     * (which I assume means larger than modulus).
     */
    NTL::ZZ deMasked = NTL::PowerMod(
            ciphertext, lambda, modulus * modulus);
    NTL::ZZ power = L_function(deMasked);
    return (power * lambdaInverse) % modulus;
}

NTL::ZZ Paillier::getModulus(){
  return modulus;
}
NTL::ZZ Paillier::getGenerator(){
  return generator;
}
NTL::ZZ Paillier::getP(){
  return P;
}
NTL::ZZ Paillier::getQ(){
  return Q;
}
NTL::ZZ Paillier::getLambda(){
  return lambda;
}

NTL::ZZ Paillier::getLambdaInverse(){
  return lambdaInverse;
}
