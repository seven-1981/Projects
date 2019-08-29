#include "AudioRecorder.hpp"

void AudioRecorder::init(IRecordingService* service)
{
    m_service = service;
}

Errors_e AudioRecorder::prepare_buffer(GEN_CARD_CONFIG_TYPE& configuration, int size)
{
    m_bufferSize = size;
    return Errors_e::NO_ERROR;
}

int AudioRecorder::get_buffer_size()
{
    return m_bufferSize;
}

int AudioRecorder::capture_samples()
{
    return m_service->pcm_readi(m_bufferSize);
}

void AudioRecorder::set_mode(CaptureMode_e mode)
{
    m_mode = mode;
}