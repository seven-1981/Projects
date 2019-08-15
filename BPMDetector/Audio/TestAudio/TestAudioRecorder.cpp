#include "FakeRecordingService.cpp"
#include "../AudioRecorder.cpp"
#include "../ALSACardConfiguration.hpp"
#include <gtest/gtest.h>

const long TEST_BUFFER_SIZE = 88200;

class TestAudioRecorder : public testing::Test
{
public:
    AudioRecorder recorder;
    ALSACardConfiguration_t config;
};
 
TEST_F(TestAudioRecorder, CreatesInstance)
{
    AudioRecorder recorder;
}

TEST_F(TestAudioRecorder, PreparesBufferForRecording)
{   
    recorder.prepare_buffer(config, TEST_BUFFER_SIZE);

    ASSERT_EQ(recorder.get_buffer_size(), TEST_BUFFER_SIZE);
}

TEST_F(TestAudioRecorder, CapturesSamples)
{
    recorder.prepare_buffer(config, TEST_BUFFER_SIZE);
    
}

/*
TEST_F(TestAudioRecorder, CapturesSamplesInSynchronousMode)
{
    AudioRecorder recorder;
    FakeRecordingService service;
    recorder.init(&service);
    recorder.set_mode(CaptureMode_Sync);
    recorder.configure()
    
    long capturedSamples = recorder.capture_samples
}
*/