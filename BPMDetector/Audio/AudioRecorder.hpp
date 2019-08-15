#ifndef _AUDIORECORDER_H
#define _AUDIORECORDER_H

#include "IAudioRecorder.hpp"


class AudioRecorder : public IAudioRecorder
{
public:
    AudioRecorder() :
      m_bufferSize(0) { }
    ~AudioRecorder() { }

    //Override interface functions
    void prepare_buffer(ICardConfiguration_t& configuration, long size) override;
    long get_buffer_size() override;

private:
    long m_bufferSize;
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