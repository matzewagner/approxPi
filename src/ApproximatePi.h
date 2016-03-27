#ifndef APPROX_PI
#define APPROX_PI

/*
This class approximates pi everytime tick is called. 
*/
#define APPROXIMATOR_PRECISION 10
#include <iostream>
#include <atomic>
using namespace std;


// This class is a pi approximator implemented for use in the sonification of it's digits.
/*!
It approximates based on the infinite series:
π = 4(1 - 1/3 + 1/5 - 1/7 + 1/9 .....)
*/

class ApproximatePi
{
public:
	ApproximatePi(void)
	{
		currentApprox = 4;
		currentSample = 0;
		currentSign = 1;
		std::cout.precision(10);
	}

	//! Sign of the latest term added (or subtracted) for the latest approximation
	/* Not intended for use external to this class */
	int currentSign;

	//! Current approximation of Pi
	/*! This is made atomic to ensure that any other visuals threads 
		can access it in a thread-safe manner */
	std::atomic<double> currentApprox;	

	long int currentSample;

	float currentPartialAmps[APPROXIMATOR_PRECISION];

	//! Does one more step in the approximation
	void tick()
	{
		currentSign *= -1;
		currentSample++;

		double previousApprox = currentApprox;
		currentApprox = previousApprox + currentSign* 4.0/(2.0*(currentSample+1) - 1);
	}

	//! Computes the amplitudes for all the partials based on currentApprox and stores it in currentPartialAmps[]
	void computePartialAmplitudes(void)
	{
		int* digits = getDigits(currentApprox);

		for(int i=0; i<APPROXIMATOR_PRECISION; i++)
		{
			currentPartialAmps[i] = pow(2, digits[i]);
			currentPartialAmps[i] *= 2 * M_PI/(i+1);		//Sawtooth-spectral factor
		}
	}

	//! Returns digits of a number with precision APPROXIMATOR_PRECISION
	/*!
		Return type is an array of length APPROXIMATOR_PRECISION
	*/
	int* getDigits(double number)
	{
		int digit[APPROXIMATOR_PRECISION];
		for(int i=0; i<APPROXIMATOR_PRECISION; i++)
		{
			digit[i] = number;
			number = number - digit[i];
			number = number * 10;
		}
		return digit;
	}
};

#endif