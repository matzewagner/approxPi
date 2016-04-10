#include "ApproximatePi.h"

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

ApproximatePi::ApproximatePi(void)
{
	currentApprox = 4;
	currentSample = 0;
	currentSign = 1;
}

void ApproximatePi::tick()
{
	currentSign *= -1;
	currentSample++;

	double previousApprox = currentApprox;
	currentApprox = previousApprox + currentSign* 4.0/(2.0*(currentSample+1) - 1);
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
