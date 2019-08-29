#include "FakeRecordingService.cpp"
#include "../AudioRecorder.cpp"
#include "../ALSACardConfiguration.hpp"
#include <gtest/gtest.h>

const int TEST_BUFFER_SIZE = 88200;


class TestAudioRecorder : public testing::Test
{
public:
    AudioRecorder recorder;
    AudioCardLister lister;
    FakeCardInfoGetter infoGetter;
    FakeCardConfigurator configurator;
    AudioCardManager manager;
    ALSACardConfiguration_t config;
    FakeRecordingService service;

    void SetUp() override
    {
        infoGetter.set_state(State_GetSuccess);
	    lister.init(&infoGetter);
	    manager.init_lister(&lister);
        configurator.set_state(State_ConfigSuccess);
	    manager.init_configurator(&configurator);
        manager.select_and_configure(config);

        recorder.prepare_buffer(config, TEST_BUFFER_SIZE);
    }
};
 
TEST_F(TestAudioRecorder, CreatesInstance)
{
    AudioRecorder recorder;
}

TEST_F(TestAudioRecorder, PreparesBufferForRecording)
{
    AudioRecorder recorder;
    recorder.prepare_buffer(config, TEST_BUFFER_SIZE);

    ASSERT_EQ(recorder.get_buffer_size(), TEST_BUFFER_SIZE);
}

TEST_F(TestAudioRecorder, CapturesSamplesInSynchronousMode)
{
    service.set_state(State_CaptureSuccess);
    recorder.init(&service);
    recorder.set_mode(CaptureMode_e::CaptureMode_Sync);

    ASSERT_EQ(recorder.capture_samples(), TEST_BUFFER_SIZE);
}

TEST_F(TestAudioRecorder, ReturnsErrorCodeIfCaptureFailsWithEBADFD)
{
    service.set_state(State_CaptureReturns_EBADFD_DropError);
    recorder.init(&service);
    recorder.set_mode(CaptureMode_e::CaptureMode_Sync);

    ASSERT_EQ(recorder.capture_samples(), RETURN_EBADFD);
}

/*

this->buffer = (short*)malloc(PCM_BUF_SIZE * snd_pcm_format_width(PCM_AUDIO_FORMAT) / 8 * PCM_CHANNELS);

*/

