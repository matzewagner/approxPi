#include "ApproximatePi.h"

#define N_SAMPS 5040

////////REMOVE THIS
#include <iostream>

ApproximatePi::ApproximatePi(int transpose_factor)
{
	currentApprox = 4;
	currentApproxIndex = 0;
	currentSign = 1;

	sample_drop = 5040/transpose_factor;
}

void ApproximatePi::Reset(void)
{
    currentApprox = 4;
    currentApproxIndex = 0;
    currentSign = 1;
}

void ApproximatePi::setTransposeFactor(int transpose_factor)
{
	sample_drop = 5040/transpose_factor;
}

void ApproximatePi::approximate(void)
{
	currentApproxIndex++;
	currentSign *= -1;
	double previousApprox = currentApprox;
	currentApprox = previousApprox + currentSign* 4.0/(2.0*(currentApproxIndex+1) - 1);
}

void ApproximatePi::tick()
{
	if(ticker < sample_drop)
	{
		ticker++;
	}
	else
	{
		ticker = 0;
		approximate();
	}

}

void ApproximatePi::computePartialAmps(double number, float output_array[APPROXIMATOR_PRECISION])
{
	int digits[APPROXIMATOR_PRECISION];

	getDigits(number, digits);

	for(int i=0; i<APPROXIMATOR_PRECISION; i++)
	{
		output_array[i] = pow(2, digits[i]);
		output_array[i] *= 2 * M_PI/(i+1);		//Sawtooth-spectral factor
	}
}

void getDigits(double number, int digits[APPROXIMATOR_PRECISION])
{
	for(int i=0; i<APPROXIMATOR_PRECISION; i++)
	{
		digits[i] = number;
		number = number - digits[i];
		number = number * 10;
	}
}

std::string numberToString(double number)
{
	std::stringstream s;
	s << std::fixed << std::setprecision(10) << number;
	return s.str();
}