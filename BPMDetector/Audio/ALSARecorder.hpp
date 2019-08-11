#ifndef _ALSARECORDER_H
#define _ALSARECORDER_H

#include "IAudioRecorder.hpp"

class ALSARecorder : public IAudioRecorder
{
public:
    ALSARecorder() { };
    ~ALSARecorder() { };

private:
};

#endif