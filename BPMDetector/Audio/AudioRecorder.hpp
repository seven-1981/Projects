#ifndef _AUDIORECORDER_H
#define _AUDIORECORDER_H

#include "IAudioRecorder.hpp"

class AudioRecorder : public IAudioRecorder
{
public:
    AudioRecorder() { };
    ~AudioRecorder() { };

    //Override base class functions
    void init(ICaptureService* service) override;

private:
};

#endif