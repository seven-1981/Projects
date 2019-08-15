#ifndef _IAUDIORECORDER_H
#define _IAUDIORECORDER_H


//Forward declarations
struct ICardConfiguration_t;


//Interface class for audio recording
class IAudioRecorder
{
public:
    virtual ~IAudioRecorder() { }

    //Interface functions
    virtual void prepare_buffer(ICardConfiguration_t& configuration, long size) = 0;
    virtual long get_buffer_size() = 0;
};

#endif
