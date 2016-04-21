//
//  Time.h
//  approxPi
//
//  Created by Akshay Cadambi on 4/20/16.
//
//

#ifndef TimeStruct_h
#define TimeStruct_h
#include <iostream>

class TimeStruct
{
public:
    TimeStruct(unsigned long num_samples=-1, int sample_rate=-1, int num_channels=-1)
    {
        sampleRate = sample_rate;
        nChannels = num_channels;
        computeMinSecs(num_samples);
    }
    
    TimeStruct(int in_minutes, int in_seconds)
    {
        minutes = in_minutes;
        seconds = in_seconds;
    }

    void computeMinSecs(unsigned long num_samples)
    {
        unsigned long total_seconds = num_samples/(sampleRate*nChannels);
        
        minutes = (int) total_seconds/60.0;
        seconds = ( total_seconds/60.0 - minutes ) * 60;
    }
    
    void debugPrint(void)
    {
        std::cout << "TIME = " << minutes << "min " << seconds << "seconds " << std::endl;
    }
        
    int nChannels;
    int sampleRate;
    int minutes;
    int seconds;
};

#endif /* TimeStruct_h */
