#ifndef APPROX_PI
#define APPROX_PI

#include <atomic>	// to share the approximation value between display and audio threads
#include <sstream>	// for converting float to string
#include <cmath>	// for pow, M_PI
#include <iomanip> 	// for setprecision
#include <vector>	// for n-channels of transposed approximations

//! Number of digits to consider in the approximation of π.
#define APPROXIMATOR_PRECISION 10
const int TRANSPOSITION_FACTOR[] = { 9, 28, 50, 73, 98, 123, 149, 175, 202, 229, 257, 285, 314, 343, 372, 402};

//! \brief Returns digits of a number with precision APPROXIMATOR_PRECISION
/*!
	Return type is an array of length APPROXIMATOR_PRECISION
	TODO: Looks precarious becuase it is returning the address stack of local variable. Check if this is a good way to do this. 
*/
int* getDigits(double number);

//! \brief Returns the string form of a number
std::string numberToString(double number);

//--------------------------------------------------------------

// \brief This class is a pi approximator implemented for use in the sonification of it's digits.
/*!
It approximates based on the infinite series:
π = 4(1 - 1/3 + 1/5 - 1/7 + 1/9 .....)
*/
class ApproximatePi
{
public:
	// TODO
	ApproximatePi(int numChannels=0);

	//! Sign of the latest term added (or subtracted) for the latest approximation
	/* Not intended for use external to this class */
	int currentSign;

	//! \brief TODO
	/*! These are the approximations for each of the successive transpositions. 
		The 0th element is the un-transposed current approximation.

		The elements are atomic to ensure that any other visuals threads 
		can access it in a thread-safe manner 
	*/
	std::atomic<double> currentApproxTransposed;

	float currentPartialAmps[APPROXIMATOR_PRECISION];

	//! \brief Moves forward in time by one sample. 
	void tick();

	void approximate();

	//! Computes the amplitudes for all the partials based on currentApprox and stores it in currentPartialAmps[]
	void computePartialAmplitudes(void);

private:
	//! \brief Each convergence step takes places after 5040 samples of audio have elapsed. This is used internally to keep track of how many samples have passed. 
	int tick_counter = 1;
	long int currentApproxIndex;
	int nChannels;

	//! \brief Current approximation of Pi. This depends on how fast you are approximating.
	double currentApprox;	
};

#endif

