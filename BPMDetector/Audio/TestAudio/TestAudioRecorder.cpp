#include "../AudioRecorder.cpp"
#include "FakeCaptureService.cpp"
#include <gtest/gtest.h>


class TestAudioRecorder : public testing::Test
{
public:

};
 
TEST_F(TestAudioRecorder, CreatesInstance)
{
    AudioRecorder recorder;
}

TEST_F(TestAudioRecorder, TakesCapturingClass)
{
    AudioRecorder recorder;
    FakeCaptureService captureService;
    recorder.init(&captureService);
}

TEST_F(TestAudioRecorder, ChecksIfReadyToCapture)
{
    AudioRecorder recorder;
    FakeCaptureService captureService;
    recorder.init(&captureService);
}