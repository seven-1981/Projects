#include "AudioRecorder.hpp"

#include "IRecordingService.hpp"
#include "ALSACardConfiguration.hpp"
#include "globals.hpp"


void AudioRecorder::init(GEN_REC_SERVICE* service)
{
    m_service = service;
}

Errors_e AudioRecorder::prepare_recorder(GEN_CARD_CONFIG_TYPE& config)
{
    if (m_service != nullptr)
    {
        set_buffer_size(config);
        return m_service->set_handle(config);
    }
    else
    {
        return Errors_e::AUDIO_RECORDER_NOT_INITIALIZED;
    }
}

void AudioRecorder::set_mode(CaptureMode_e mode)
{
    m_mode = mode;
}

void AudioRecorder::set_buffer_size(GEN_CARD_CONFIG_TYPE& config)
{
    CARD_CONFIG_TYPE& typedConfig = dynamic_cast<CARD_CONFIG_TYPE&>(config);
    m_bufferSize = typedConfig.PCM_BUFFER_SIZE;
}

Errors_e AudioRecorder::convert_errorCode(const int code) const
{
    const int RETURN_EBADFD = -77;  //Values from ALSA library
    const int RETURN_EPIPE = -32;
    const int RETURN_ESTRPIPE = -86;
    const int RETURN_EAGAIN = -11;
    Errors_e retVal = Errors_e::NO_ERROR;
    switch(code)
    {
        case RETURN_EBADFD:
            retVal = Errors_e::AUDIO_RECORDER_CAPTURE_EBADFD;
            break;
        case RETURN_EPIPE:
            retVal = Errors_e::AUDIO_RECORDER_CAPTURE_EPIPE;
            break;
        case RETURN_ESTRPIPE:
            retVal = Errors_e::AUDIO_RECORDER_CAPTURE_ESTRPIPE;
            break;
        case RETURN_EAGAIN:
        default:
            retVal = Errors_e::AUDIO_RECORDER_CAPTURE_EAGAIN;
            break;
    }   
    return retVal;
}