#include "FakeAudioRecorder.hpp"


const long NUM_SAMPLES = 88200;

long FakeAudioRecorder::pcm_readi(unsigned long size)
{
    return NUM_SAMPLES;
}