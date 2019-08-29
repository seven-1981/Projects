#ifndef _AUDIORECORDER_H
#define _AUDIORECORDER_H

#include "IAudioRecorder.hpp"


//Forward declarations
enum class Errors_e;
//Typename simplifications
using GEN_CARD_CONFIG_TYPE = ICardConfiguration_t;


enum class CaptureMode_e
{
    CaptureMode_Sync,
    CaptureMode_Async
};


class AudioRecorder : public IAudioRecorder
{
public:
    AudioRecorder() :
      m_bufferSize(0), m_mode(CaptureMode_e::CaptureMode_Sync) { }
    ~AudioRecorder() { }

    //Override interface functions
    void init(IRecordingService* service) override;
    Errors_e prepare_buffer(GEN_CARD_CONFIG_TYPE& configuration, int size) override;
    int get_buffer_size() override;
    int capture_samples() override;

    //Capture mode setter
    void set_mode(CaptureMode_e mode);

private:
    int m_bufferSize;
    IRecordingService* m_service;
    CaptureMode_e m_mode;
};

#endif

/*
class Type
{
    public:
        virtual ~Type(){}
        virtual void* allocate()const=0;
        virtual void* cast(void* obj)const=0;
};

template<typename T> class TypeImpl : public Type
{
      public:
         virtual void* allocate()const{ return new T; }
         virtual void* cast(void* obj)const{ return static_cast<T*>(obj); }
};

// ...
Type* type = new TypeImpl<int>;
void* myint = type->allocate();
// ...
*/