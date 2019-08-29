#ifndef _IRECORDINGSERVICE_H
#define _IRECORDINGSERVICE_H


//Interface class for audio recording service
class IRecordingService
{
public:
    virtual ~IRecordingService() { }

    //Interface functions
    virtual int pcm_readi(int size) = 0;
    virtual int pcm_drop() = 0;
    virtual int pcm_recover() = 0;
};

#endif
