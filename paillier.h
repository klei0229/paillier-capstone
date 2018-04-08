#include <NTL/ZZ.h>
#include <NTL/ZZ_pXFactoring.h>

class Paillier {
    public:
    /* Completely generate everything, from scratch */
    Paillier();
    Paillier(const NTL::ZZ& modulus, const NTL::ZZ& lambda);
    //Paillier(path to public key, path to private key).

    /* Paillier encryption function. Takes in a message from the
     * integers modulo n (Paillier.modulus) and returns a message in
     * the integers modulo n**2.
     *
     * Parameters
     * ==========
     * NTL::ZZ message : The message to encrypt, as a number.
     *
     * Returns
     * =======
     * NTL:ZZ ciphertext : The encyrpted message.
     */
    NTL::ZZ encrypt(const NTL::ZZ& message);

    /* Paillier encryption function with provided randomness, if user
     * wants to provide their own randomness.
     *
     * Random number should be coprime to modulus.
     *
     * Parameters
     * ==========
     * NTL::ZZ message : The message to encrypt, as a number.
     * NTL::ZZ random : The random mask.
     *
     * Returns
     * =======
     * NTL:ZZ ciphertext : The encyrpted message.
     */
    NTL::ZZ encrypt(const NTL::ZZ& message, const NTL::ZZ& random);

    /* Paillier decryption function. Takes in a cipertext from Z mod
     * n**2 and returns a message in the Z mod n.
     *
     * Parameters
     * ==========
     * NTL::ZZ cipertext : The encrypted message.
     *
     * Returns
     * =======
     * NTL::ZZ message : The original message.
     */
    NTL::ZZ decrypt(const NTL::ZZ& ciphertext);


    /*
    Functions below are used for displaying private variables for debugging
    */
    NTL::ZZ getModulus();
    NTL::ZZ getGenerator();
    NTL::ZZ getP();
    NTL::ZZ getQ();
    NTL::ZZ getLambda();
    NTL:: ZZ getLambdaInverse();

    private:
    /* modulus = pq, where p and q are primes */

    NTL::ZZ P;
    NTL::ZZ Q;

    NTL::ZZ modulus;
    NTL::ZZ generator;
    NTL::ZZ lambda;
    NTL::ZZ lambdaInverse;

    /* The L function in the paillier cryptosystem.  See
     * <https://en.wikipedia.org/wiki/Paillier_cryptosystem> for more
     * details.
     *
     * Parameters
     * ==========
     * NTL::ZZ x : The argument to L.
     * NTL::ZZ n : The paillier modulus.
     *
     * Returns
     * =======
     * NTL::ZZ result : (x - 1) / n
     */
    NTL::ZZ L_function(const NTL::ZZ& n) { return (n - 1) / modulus; }



    /*
     * GenPrimePair Function finds values for p and q(two large prime numbers
     * randomly to be used for computing the the public and private key.
     *
     * Parameters
     * ==========
     * NTL::ZZ& p : pass by reference p to contain value of first prime number.
     * NTL::ZZ& q : pass by reference q to contain value of second prime number.
     * long keyLength: argument that deteremines the length of p and q to be obtained.

    */
    void GenPrimePair(NTL::ZZ& p, NTL::ZZ& q, long keyLength);



};
