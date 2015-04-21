#ifndef __Random__
#define __Random__

#include <cstdio>
#include <stdio.h>

using namespace std;


class RandomNumber {
	private:
		FILE* file;
	
	public:
		RandomNumber();
		RandomNumber(FILE*);
		int getRandomNumber();
};
#endif