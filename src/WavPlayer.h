//
//  PiPlayer.h
//  approxPi
//
//  Created by Akshay Cadambi on 4/20/16.
//
//

#ifndef WavPlayer_h
#define WavPlayer_h

#include "WavReader.hpp"

class WavPlayer
{
public:
    WavPlayer(string fileName)
    {
        audiofile.open_file(fileName);
        duration(audiofile.getTotalDur());
    }
    
    WavReader audioFile;
    
    bool isPlaying(void)
    {
        return playing;
    }
    
    void play(void)
    {
        if(!isPlaying())
        {
            audiofile.reader_enabled = true;
            playing = true;
        }
    }
    
    void pause(void)
    {
        if(isPlaying())
        {
            playing = false;
            audiofile.reader_enabled = false;
        }
    }
    
    bool togglePlay(void)
    {
        if(isPlaying())
            pause();
        else
            play();

        return isPlaying();
    }
    
    bool mute(void)
    {
        mute = true;
        audiofile.mute();
    }
    
    void stop(void)
    {
        playing = false;
        audiofile.readBuf = 0;
    }
    
    void mute(void)
    {
        audiofile.mute = true;
        mute = true;
    }

private:
    bool playing = false;
    bool mute = false;
    TimeStruct duration;
};


#endif /* WavPlayer_h */
