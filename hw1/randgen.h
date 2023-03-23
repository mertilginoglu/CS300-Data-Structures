#ifndef _RANDGEN_H
#define _RANDGEN_H

#include <time.h>                // for time()
#include <stdlib.h>              // for rand/srand
#include <cmath>
#include <iostream>
#include <limits.h>                     // for INT_MAX

using namespace std;

// designed for implementation-independent randomization
// if all system-dependent calls included in this class, then
// other classes can make use of this class in independent manner
// all random numbers are uniformly distributed in given range
//
// RandGen() ---      constructor sets seed of random # generator
//                    once per program, not per class/object
//     
// RandInt(int max)
// RandInt(int low,int max) - return random integer in range [0..max)
//                     when one parameter used, [low..max] when
//                     two parameters used
//
//       examples:    rnd.RandInt(6) is random integer [0..5] or [0..6)
//                    rnd.RandInt(3,10) is random integer [3..10]
//                    rnd.RandInt()  is random integer [0..INT_MAX)
//
// RandReal()       -- returns random double in range [0..1)
// RandReal(double low, double max) -- random double in range [low..max)

class RandGen
{
  public:
    RandGen();                          // set seed for all instances
    int RandInt(int max = INT_MAX);     // returns int in [0..max)
    int RandInt(int low, int max);      // returns int in [low..max]
    double RandReal();                  // returns double in [0..1)
    double RandReal(double low, double max); // range [low..max]

    static void SetSeed(int seed);      // static (per class) seed set
private:
    static int ourInitialized;          // for 'per-class' initialization
};

int RandGen::ourInitialized = 0;

void RandGen::SetSeed(int seed)
// postcondition: system srand() used to initialize seed
//                once per program (this is a static function)    
{
	if (0 == ourInitialized)
	{
		ourInitialized = 1;   // only call srand once
		srand(seed);          // randomize
	}
}


RandGen::RandGen()
// postcondition: system srand() used to initialize seed
//                once per program     
{
	if (0 == ourInitialized)
	{
		ourInitialized = 1;          // only call srand once


		time_t now;
		time(&now); // localtime bir zamandan itibaren geçen saniye formatinda
					// now degiskenine kaydedilir.
		srand(int((sin(double(now)) * 1000000)));//Gokhan
												 // seed'imiz her saniye bir artmasin diye
												 // daha random artsin diye sinusunu aliyorum 
												 //       srand(unsigned(time(0)));    // randomize
	}
}

int RandGen::RandInt(int max)
// precondition: max > 0
// postcondition: returns int in [0..max)     
{
	return int(RandReal() * max);
}

int RandGen::RandInt(int low, int max)
// precondition: low <= max     
// postcondition: returns int in [low..max]     
{
	return low + RandInt(max - low + 1);
}

double RandGen::RandReal()
// postcondition: returns double in [0..1)     
{
	return rand() / (double(RAND_MAX) + 1);
}

double RandGen::RandReal(double low, double high)
{
	double width = fabs(high - low);
	double thelow = low < high ? low : high;
	return RandReal()*width + thelow;
}

#endif
