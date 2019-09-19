#ifndef _IAUDIORECORDER_H
#define _IAUDIORECORDER_H


//Forward declarations
enum class Errors_e;
struct ICardConfiguration_t;
class IRecordingService;
template <typename T>
class Buffer;


//Interface class for audio recording
class IAudioRecorder
{
public:
    virtual ~IAudioRecorder() { }

    //Init functions
    virtual void init(IRecordingService* service) = 0;
    //Interface functions
    virtual Errors_e prepare_recorder(ICardConfiguration_t& config) = 0;

    template <typename T> //Implicit interface - not virtual
    Errors_e capture_samples(ICardConfiguration_t& config, Buffer<T>& buffer);  
};

#endif
