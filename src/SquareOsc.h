#ifndef SQUAREWAVE_OSCILLATOR
#define SQUAREWAVE_OSCILLATOR

class Phasor
{
public:
    Phasor(){}
    
    void set_freq(float frequency=0, int sampling_rate=44100, float starting_phase=0 )
    {
        phase = starting_phase;
        phase_increment = 2*M_PI*frequency/sampling_rate;
    }
        
    float phase=0;
    
    void increment(void)   // Increments phase
    {
        phase += phase_increment;
        if( phase > 2*M_PI )
            phase = phase - 2*M_PI;
    }
    
private:
    float phase_increment=0;
};

// A memoryless implementation of a Squarewave Oscillator
float SquareOsc(Phasor p)
{
        p.increment();

        if (p.phase < M_PI)
            return 1;
        else
            return -1;
}

#endif