# The following all worked on my machine:
#g++ -g $< -o $@ -lntl -lgmp
#g++ -g $< -o $@ -lntl
#g++ -g $< -o $@
#

# - ntl: Number theory library
# - gmp: Arbitrary precision arithmetic.
# - ssl + crytpo: For openssl. Installed on most linux machines, and
#   has hashing algorithms.
# - m: From what I can tell, libm is an implementation of C math
#   functions. Why would we need this?
LIBS:=ntl gmp m ssl crypto
LIBFLAGS:=$(addprefix -l, $(LIBS));

main : main.cpp paillier.cpp
	g++ -g -Wall -Wpedantic $^ -o $@ $(LIBFLAGS)
