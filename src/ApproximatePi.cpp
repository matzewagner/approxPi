#include "ApproximatePi.h"

#define N_SAMPS 5040

ApproximatePi::ApproximatePi(int numChannels) :
	nChannels(numChannels)
{
	// if(nchannels > 17 || nchannels < 0)

	currentApprox = 4;
	currentApproxIndex = 0;
	currentSign = 1;
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
	if(tick_counter > N_SAMPS)
	{
		currentApproxTransposed = currentApprox;
		for(int i=0; i<TRANSPOSITION_FACTOR[0]; i++)
		{
			approximate();
		}
		tick_counter = 0;
	}
	else
	{
		tick_counter++;
	}    
}

void ApproximatePi::computePartialAmplitudes(void)
{
	int* digits = getDigits(currentApprox);

	for(int i=0; i<APPROXIMATOR_PRECISION; i++)
	{
		currentPartialAmps[i] = pow(2, digits[i]);
		currentPartialAmps[i] *= 2 * M_PI/(i+1);		//Sawtooth-spectral factor
	}
}

int* getDigits(double number)
{
    static int digit[APPROXIMATOR_PRECISION] {0};
	for(int i=0; i<APPROXIMATOR_PRECISION; i++)
	{
		digit[i] = number;
		number = number - digit[i];
		number = number * 10;
	}
	return digit;
}

std::string numberToString(double number)
{
	std::stringstream s;
	s << std::fixed << std::setprecision(10) << number;
	return s.str();
}