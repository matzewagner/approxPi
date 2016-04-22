//
//  PiPlayer.h
//  approxPi
//
//  Created by Akshay Cadambi on 4/20/16.
//
//

#ifndef WavPlayer_h
#define WavPlayer_h

#include "WavReader.h"

class WavPlayer
{
public:
    WavReader audiofile;

    bool open_file(string fileName)
    {
        return audiofile.open_file(fileName);
    }
    
    bool isPlaying(void)
    {
        return audiofile.reader_enabled;
    }
    
    bool isMuted(void)
    {
        return audiofile.mute;
    }
    
    void play(void)
    {
        if(!isPlaying())
        {
            audiofile.reader_enabled = true;
        }
    }
    
    void pause(void)
    {
        if(isPlaying())
        {
            audiofile.reader_enabled = false;
        }
    }
    
    void stop(void)
    {
        pause();
        audiofile.bufReader = 0;
    }
    
    bool togglePlay(void)
    {
        if(isPlaying())
            pause();
        else
            play();

        return isPlaying();
    }
    
    bool toggleMute(void)
    {
        audiofile.mute = !audiofile.mute;
        return audiofile.mute;
    }
    
    TimeStruct getTotalDuration(void)
    {
        return audiofile.getTotalDur();
    }
    
    TimeStruct getCurrentTime(void)
    {
        return audiofile.getCurrentTime();
    }
    
    void setEndTime(TimeStruct endTime)
    {
        unsigned long seconds = endTime.minutes * 60 + endTime.seconds;
        
        audiofile.set_end_samples( seconds * audiofile.sampleRate() * audiofile.nChannels() );
    }
};


#endif /* WavPlayer_h */
