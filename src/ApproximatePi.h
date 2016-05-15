#ifndef APPROX_PI
#define APPROX_PI

#include <atomic>	// to share the approximation value between display and audio threads
#include <sstream>	// for converting float to string
#include <cmath>	// for pow, M_PI
#include <iomanip> 	// for setprecision
#include <vector>	// for n-channels of transposed approximations
#include "SquareOsc.h" // for audio synthesis

//! Number of digits to consider in the approximation of π.
#define APPROXIMATOR_PRECISION 10
const int TRANSPOSITION_FACTOR[] = { 9, 28, 50, 73, 98, 123, 149, 175, 202, 229, 257, 285, 314, 343, 372, 402};

//! \brief Gets the digits of a number with precision APPROXIMATOR_PRECISION. Stores in digits
/*!
	Return type is an array of length APPROXIMATOR_PRECISION. 
*/
void getDigits(double number, int digits[]);

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
	ApproximatePi(int transpose_factor = 1);

    // Transposes the approximator using sample dropping, use this to obtain an approximator for different channels.
    void setTransposeFactor(int transpose_factor);

	//! \brief Gets the current approximation of Pi.
	/*! This is made into an atomic type so that you can access it in a thread-safe way.
	*/
	std::atomic<double> currentApprox;

    //! \brief Moves forward in time by one sample.
    /*! Makes an approximation at appropriate times based on the transposition factor given.
     */
    float tick();
    
    //! \brief Resets the approximator to it's initial state.
    void Reset(void);

	//! Performs one step in the approximation. Do not use unless you want to time the approximations yourself. 
	void approximate();
    
    //! \brief Disables the all audio computation during tick(). Audio is on by default.
    //! Use this if you want to use a custom audio file.
    void disableAudio(void);

private:
	int sample_drop;
	int ticker = 0;
	long int currentApproxIndex;
    bool audioDisabled = false;
    SquareOsc partials[APPROXIMATOR_PRECISION];
    
    //! \brief Computes the amplitudes for all the partials based on currentApprox and stores it in output_array
    void computePartialAmps(double number, float output_array[APPROXIMATOR_PRECISION]);

    //! \brief Gets the next audio sample
    float getAudioSample(void);

	//! Sign of the latest term added (or subtracted) for the latest approximation
	int currentSign;
};

#endif
