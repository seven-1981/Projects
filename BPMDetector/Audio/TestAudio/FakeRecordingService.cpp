#include "FakeRecordingService.hpp"


const long NUM_SAMPLES = 88200;

long FakeRecordingService::pcm_readi(unsigned long size)
{
    return NUM_SAMPLES;
}