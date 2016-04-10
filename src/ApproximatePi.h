#ifndef APPROX_PI
#define APPROX_PI

#include <atomic>	// to share the approximation value between display and audio threads
#include <sstream>	// for converting float to string
#include <cmath>	// for pow, M_PI
#include <iomanip> 	// for setprecision

//! Number of digits to consider in the approximation of π.
#define APPROXIMATOR_PRECISION 10

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
	ApproximatePi(void);

	//! Sign of the latest term added (or subtracted) for the latest approximation
	/* Not intended for use external to this class */
	int currentSign;

	//! Current approximation of Pi
	/*! This is made atomic to ensure that any other visuals threads 
		can access it in a thread-safe manner */
	std::atomic<double> currentApprox;
    
	std::atomic<long int> currentSample;

	float currentPartialAmps[APPROXIMATOR_PRECISION];

	//! Does one more step in the approximation
	void tick();

	//! Computes the amplitudes for all the partials based on currentApprox and stores it in currentPartialAmps[]
	void computePartialAmplitudes(void);
};

#endif

