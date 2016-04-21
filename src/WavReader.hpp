//
//  WAVRead.h
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
    
    void open_file(std::string file_name)
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
        }
        else
        {
            cout << "Couldn't find the file: " << file_name << endl;
            std::exit(1);
        }
    }
    
    float next_sample(void)
    {
        if (reader_enable && !mute)
        {
            return buf[bufReader++];
        }
        else if (mute)
        {
            bufReader ++;
            return 0;
        }
        else
        {
            return 0;
        }
    }
    
    int getNumChannels(void)
    {
        return NumChannels;
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
    
    bool reader_enable = true;
    bool mute = false;
    
private:
    std::string file_name;
    float *buf;
    short *Data;
    const double ONEOVERSHORTMAX = 1.0/32768;
    
    char ChunkID[4], Format[4], Subchunk1ID[4],Subchunk2ID[4];
    int ChunkSize, Subchunk1Size, SampleRate, ByteRate, Subchunk2Size;
    short AudioFormat, NumChannels, BlockAlign, BitsPerSample;
    std::atomic<unsigned long> bufReader = {0};
    
    unsigned long nSamples;
};


#endif /* WAVRead_h */
