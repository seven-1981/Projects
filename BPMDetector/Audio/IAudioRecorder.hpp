#ifndef _IAUDIORECORDER_H
#define _IAUDIORECORDER_H


//Interface class for audio recording
class IAudioRecorder
{
public:
    virtual ~IAudioRecorder() { }

    //Interface functions
    virtual long pcm_readi(unsigned long size) = 0;
};

#endif
