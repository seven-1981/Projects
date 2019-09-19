#ifndef _IRECORDINGSERVICE_H
#define _IRECORDINGSERVICE_H


//Forward declarations
enum class Errors_e;
struct ICardConfiguration_t;


//Interface class for audio recording service
class IRecordingService
{
public:
    virtual ~IRecordingService() { }

    //Interface functions
    virtual Errors_e set_handle(ICardConfiguration_t& config) = 0;
    virtual bool is_handleSet() = 0;
    virtual int pcm_readi(void* buffer, int size) = 0;
    virtual int pcm_drop() = 0;
    virtual int pcm_recover(int err, int silent) = 0;
};

#endif
