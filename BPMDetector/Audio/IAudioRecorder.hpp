#ifndef _IAUDIORECORDER_H
#define _IAUDIORECORDER_H


//Forward declarations
class ICaptureService;


//Interface class for audio recording
class IAudioRecorder
{
public:
    virtual ~IAudioRecorder() { }

    //Interface functions
    virtual void init(ICaptureService* service) = 0;
};

#endif