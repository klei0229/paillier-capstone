# The following all worked on my machine:
#g++ -g $< -o $@ -lntl -lgmp
#g++ -g $< -o $@ -lntl
#g++ -g $< -o $@
#
# From what I can tell, libm is an implementation of C math functions.
# Why would we need this?

main : main.cpp
	g++ -g $< -o $@ -lntl -lgmp -lm
