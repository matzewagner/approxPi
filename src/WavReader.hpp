//
//  WAVRead.h
//  approxPi
//
//  Created by matze on 4/18/16.
//

#ifndef WAVRead_h
#define WAVRead_h

#include <fstream>

class WavReader
{
public:
    WavReader(void) {}
    
    WavReader(char* file_name) :
    file_name(file_name)
	{
        open_file(file_name);
	}
    
    void open_file(char* file_name)
    {
        FILE *fhandle=fopen(file_name,"rb");
        
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
        int nSamples = Subchunk2Size/(BitsPerSample/8);
        Data = new short[nSamples];
        buf = new float[nSamples];
        fread(Data, BitsPerSample/8, nSamples, fhandle);
        
        fclose(fhandle);
        
        for (int i=0; i<nSamples; ++i)
            buf[i] = Data[i] * ONEOVERSHORTMAX;

    }
    
    float next_sample(void)
    {
        return buf[bufReader++];
    }
    
private:
    char* file_name;
    float *buf;
    short *Data;
    const double ONEOVERSHORTMAX = 1.0/32768;
    
    char ChunkID[4], Format[4], Subchunk1ID[4],Subchunk2ID[4];
    int ChunkSize, Subchunk1Size, SampleRate, ByteRate, Subchunk2Size;
    short AudioFormat, NumChannels, BlockAlign, BitsPerSample;
    int bufReader = 0;


};

#endif /* WAVRead_h */
