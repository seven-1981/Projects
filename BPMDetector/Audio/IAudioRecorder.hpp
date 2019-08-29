#ifndef _IAUDIORECORDER_H
#define _IAUDIORECORDER_H


//Forward declarations
enum class Errors_e;
struct ICardConfiguration_t;
class IRecordingService;


//Interface class for audio recording
class IAudioRecorder
{
public:
    virtual ~IAudioRecorder() { }

    //Init functions
    virtual void init(IRecordingService* service) = 0;
    //Interface functions
    virtual Errors_e prepare_buffer(ICardConfiguration_t& configuration, int size) = 0;
    virtual int get_buffer_size() = 0;
    virtual int capture_samples() = 0;
};

#endif
