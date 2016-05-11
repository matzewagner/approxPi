//
//  WAVReader.h
//  approxPi
//
//  Created by matze on 4/18/16.
//

#ifndef WAVRead_h
#define WAVRead_h

#include <fstream>
#include <string>
#include "TimeStruct.h"

class WavReader
{
public:
    WavReader(void) {}
    
    WavReader(std::string file_name) :
        file_name(file_name)
	{
        open_file(file_name);
	}
    
    bool open_file(std::string file_name)
    {
        FILE *fhandle=fopen(file_name.c_str(),"rb");
        
        if( fhandle != NULL)
        {
            fread(ChunkID,1,4,fhandle);
            fread(&ChunkSize,4,1,fhandle);
            fread(Format,1,4,fhandle);
            fread(Subchunk1ID,1,4,fhandle);
            fread(&Subchunk1Size,4,1,fhandle);
            fread(&AudioFormat,2,1,fhandle);
            fread(&NumChannels,2,1,fhandle);
            fread(&SampleRate,4,1,fhandle);
            fread(&ByteRate,4,1,fhandle);
            fread(&BlockAlign,2,1,fhandle);
            fread(&BitsPerSample,2,1,fhandle);
            fread(&Subchunk2ID,1,4,fhandle);
            fread(&Subchunk2Size,4,1,fhandle);
            nSamples = Subchunk2Size/(BitsPerSample/8);
            Data = new short[nSamples];
            buf = new float[nSamples];
            fread(Data, BitsPerSample/8, nSamples, fhandle);
            
            fclose(fhandle);
            
            for (int i=0; i<nSamples; ++i)
                buf[i] = Data[i] * ONEOVERSHORTMAX;
            
            end_samples = nSamples;
            
            return true;
        }
        else
        {
            return false;
        }
    }
    
    float next_sample(void)
    {
        if (reader_enabled && !mute)
        {
            if(bufReader < end_samples)
                return buf[bufReader++];
            else
            {
                reader_enabled = false;
                return 0;
            }
        }
        else if (mute)
        {
            bufReader++;
            return 0;
        }
        else
        {
            return 0;
        }
    }
    
    int nChannels(void)
    {
        return NumChannels;
    }
    
    int sampleRate(void)
    {
        return SampleRate;
    }
    
    TimeStruct getTotalDur(void)
    {
        return TimeStruct(nSamples, SampleRate, NumChannels);
    }
    
    TimeStruct getCurrentTime(void)
    {
        unsigned long current_len = bufReader;
        return TimeStruct(bufReader, SampleRate, NumChannels);
    }
    
    void set_end_samples(unsigned long samples)
    {
        if (samples <= nSamples)
            end_samples = samples;
        
        //TODO: BUG - Ends "slightly" earlier than it should, but ends correctly.
        
        float delay = 0.1; //(in seconds). Between each channel stopping
        
        for(int chan = 0; chan<NumChannels; chan++)
        {
            int n = (end_samples/NumChannels) - (delay*SampleRate*(NumChannels-chan));
            int m = end_samples;
            m = m*1.0/NumChannels;
            
            for(int i= n*NumChannels; i<m*NumChannels; i+=NumChannels)
            {
                buf[i + chan] = 0;
            }
        }
    }
    
    bool reader_enabled = false;
    bool mute = false;
    std::atomic<unsigned long> bufReader = {0};

private:
    std::string file_name;
    float *buf;
    short *Data;
    const double ONEOVERSHORTMAX = 1.0/32768;
    
    char ChunkID[4], Format[4], Subchunk1ID[4],Subchunk2ID[4];
    int ChunkSize, Subchunk1Size, SampleRate, ByteRate, Subchunk2Size;
    short AudioFormat, NumChannels, BlockAlign, BitsPerSample;
    
    unsigned long nSamples;
    unsigned long end_samples;
};


#endif /* WAVRead_h */
