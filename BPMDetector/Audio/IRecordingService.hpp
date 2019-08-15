#ifndef _IRECORDINGSERVICE_H
#define _IRECORDINGSERVICE_H


//Interface class for audio recording service
class IRecordingService
{
public:
    virtual ~IRecordingService() { }

    //Interface functions
    virtual long pcm_readi(unsigned long size) = 0;
};

#endif
