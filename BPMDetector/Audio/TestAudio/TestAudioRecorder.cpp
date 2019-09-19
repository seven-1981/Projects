#include "FakeRecordingService.cpp"
#include "AudioRecorder.cpp"
#include "ALSACardConfiguration.hpp"
#include "Buffer.hpp"
#include <gtest/gtest.h>


class TestAudioRecorder : public testing::Test
{
public:
    using SAMPLE_TYPE = short unsigned int;

    AudioRecorder recorder;
    AudioCardLister lister;
    FakeCardInfoGetter infoGetter;
    FakeCardConfigurator configurator;
    AudioCardManager manager;
    ALSACardConfiguration_t config;
    FakeRecordingService service;
    Buffer<SAMPLE_TYPE> buffer;

    void SetUp() override
    {
        infoGetter.set_state(State_GetSuccess);
	    lister.init(&infoGetter);
	    manager.init_lister(&lister);
        configurator.set_state(State_ConfigSuccess);
	    manager.init_configurator(&configurator);
        manager.select_and_configure(config);
        recorder.init(&service);
        buffer.init(config.PCM_BUFFER_SIZE);
    }
};
 
TEST_F(TestAudioRecorder, CreatesInstance)
{
    AudioRecorder recorder;
}

TEST_F(TestAudioRecorder, ChecksForInitializationOfRecordingService)
{
    AudioRecorder recorderNotInitialized;
    Errors_e returnValue = recorderNotInitialized.prepare_recorder(config);

    ASSERT_EQ(returnValue, Errors_e::AUDIO_RECORDER_NOT_INITIALIZED);    
}

TEST_F(TestAudioRecorder, ChecksForInitializationOfPcmHandle)
{
    ALSACardConfiguration_t empty_config;

    Errors_e returnValue = recorder.prepare_recorder(empty_config);

    ASSERT_EQ(returnValue, Errors_e::AUDIO_RECORDER_NOT_INITIALIZED); 
}

TEST_F(TestAudioRecorder, PreparesBuffer)
{
    Errors_e returnValue = recorder.prepare_recorder(config);

    ASSERT_EQ(returnValue, Errors_e::NO_ERROR);
}

TEST_F(TestAudioRecorder, ReturnsErrorCodeIfCaptureCalledWithoutPreparation)
{
    Errors_e returnValue = recorder.capture_samples(config, buffer);

    ASSERT_EQ(returnValue, Errors_e::AUDIO_RECORDER_NOT_INITIALIZED);
}

TEST_F(TestAudioRecorder, CapturesSamplesInSynchronousMode)
{
    service.set_state(State_CaptureSuccess);
    IGNORE recorder.prepare_recorder(config);

    ASSERT_EQ(recorder.capture_samples(config, buffer), Errors_e::NO_ERROR);
}

TEST_F(TestAudioRecorder, ReturnsErrorCodeIfCaptureFailsWithEBADFD)
{
    service.set_state(State_CaptureReturns_EBADFD_RecoverNotPossible);
    IGNORE recorder.prepare_recorder(config);

    ASSERT_EQ(recorder.capture_samples(config, buffer), Errors_e::AUDIO_RECORDER_CAPTURE_EBADFD);
}

TEST_F(TestAudioRecorder, ReturnsErrorCodeIfCaptureFailsWithEPIPERecoverError)
{
    service.set_state(State_CaptureReturns_EPIPE_RecoverError);
    IGNORE recorder.prepare_recorder(config);

    ASSERT_EQ(recorder.capture_samples(config, buffer), Errors_e::AUDIO_RECORDER_CAPTURE_EPIPE);
}

TEST_F(TestAudioRecorder, ReturnsErrorCodeIfCaptureFailsWithEPIPERecoverSuccess)
{
    service.set_state(State_CaptureReturns_EPIPE_RecoverSuccess);
    IGNORE recorder.prepare_recorder(config);

    ASSERT_EQ(recorder.capture_samples(config, buffer), Errors_e::NO_ERROR);
}

TEST_F(TestAudioRecorder, ReturnsErrorCodeIfCaptureFailsWithESTRPIPERecoverError)
{
    service.set_state(State_CaptureReturns_ESTRPIPE_RecoverError);
    IGNORE recorder.prepare_recorder(config);

    ASSERT_EQ(recorder.capture_samples(config, buffer), Errors_e::AUDIO_RECORDER_CAPTURE_ESTRPIPE);
}

TEST_F(TestAudioRecorder, ReturnsErrorCodeIfCaptureFailsWithESTRPIPERecoverSuccess)
{
    service.set_state(State_CaptureReturns_ESTRPIPE_RecoverSuccess);
    IGNORE recorder.prepare_recorder(config);

    ASSERT_EQ(recorder.capture_samples(config, buffer), Errors_e::NO_ERROR);
}

