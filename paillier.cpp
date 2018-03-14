#include "paillier.h"

NTL::ZZ generateCoprimeNumber(NTL::ZZ n) {
    NTL::ZZ ret;
    while (true) {
        ret = RandomBnd(n);
        if (NTL::GCD(ret, n) == 1) { return ret; }
    }
}

Paillier::Paillier() {
    /* Length in bits. */
    long keyLength = 512;
    NTL::ZZ p, q;
    GenPrimePair(p, q, keyLength);
    modulus = p * q;
    generator = modulus + 1;
    NTL::ZZ phi = (p - 1) * (q - 1);
    // LCM(p, q) = p * q / GCD(p, q);
    lambda = phi / NTL::GCD(p - 1, q - 1);
    lambdaInverse = NTL::InvMod(lambda, modulus);
}

Paillier::Paillier(NTL::ZZ modulus, NTL::ZZ lambda) {
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
        NTL::ZZ q = NTL::GenPrime_ZZ(keyLength/2, err);
        while (p != q) {
            q = NTL::GenPrime_ZZ(keyLength/2, err);
        }
        NTL::ZZ n = p * q;
        NTL::ZZ phi = (p - 1) * (q - 1);
        if (NTL::GCD(n, phi) == 1) return;
    }
}

NTL::ZZ Paillier::encrypt(NTL::ZZ message) {
    NTL::ZZ random = generateCoprimeNumber(modulus);
    NTL::ZZ ciphertext = 
        NTL::PowerMod(generator, message, modulus * modulus) *
        NTL::PowerMod(random, modulus, modulus * modulus);
    return ciphertext % (modulus * modulus);
}

NTL::ZZ Paillier::encrypt(NTL::ZZ message, NTL::ZZ random) {
    NTL::ZZ ciphertext = 
        NTL::PowerMod(generator, message, modulus * modulus) *
        NTL::PowerMod(random, modulus, modulus * modulus);
    return ciphertext % (modulus * modulus);
}


NTL::ZZ Paillier::decrypt(NTL::ZZ ciphertext) {
    /* NOTE: NTL::PowerMod will fail if the first input is too large
     * (which I assume means larger than modulus).
     */
    NTL::ZZ deMasked = NTL::PowerMod(ciphertext, lambda, 
                                     modulus * modulus);
    NTL::ZZ power = L_function(deMasked);
    return (power * lambdaInverse) % modulus;
}
