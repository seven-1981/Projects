#ifndef _AUDIORECORDER_H
#define _AUDIORECORDER_H

#include "IAudioRecorder.hpp"
#include "ALSACardConfiguration.hpp"
#include "IRecordingService.hpp"
#include "Buffer.hpp"
#include "globals.hpp"


//Typename simplifications
using GEN_CARD_CONFIG_TYPE = ICardConfiguration_t;
using CARD_CONFIG_TYPE = ALSACardConfiguration_t;
using GEN_REC_SERVICE = IRecordingService;


enum class CaptureMode_e
{
    CaptureMode_Sync,
    CaptureMode_Async
};


class AudioRecorder : public IAudioRecorder
{
public:
    AudioRecorder() :
      m_bufferSize(0), 
      m_service(nullptr), 
      m_mode(CaptureMode_e::CaptureMode_Sync) { }
    ~AudioRecorder() { }

    //Override interface functions
    void init(GEN_REC_SERVICE* service) override;
    Errors_e prepare_recorder(GEN_CARD_CONFIG_TYPE& config) override;

    //Implicit interface functions
    template <typename T>
    Errors_e capture_samples(GEN_CARD_CONFIG_TYPE& config, Buffer<T>& bufferToFill)
    {
        if ((m_service == nullptr) || (m_service->is_handleSet() == false))
        {
            return Errors_e::AUDIO_RECORDER_NOT_INITIALIZED;
        }
        else
        {
            CARD_CONFIG_TYPE& typedConfig = dynamic_cast<CARD_CONFIG_TYPE&>(config);
            using SAMPLE_TYPE = decltype(typedConfig.PCM_SAMPLE_TYPE);
            SAMPLE_TYPE buffer[m_bufferSize] = { 0 };
            return fill_buffer(buffer, bufferToFill);
        }
    }

    //Capture mode setter
    void set_mode(CaptureMode_e mode);

private:
    int m_bufferSize;
    GEN_REC_SERVICE* m_service;
    CaptureMode_e m_mode;

    void set_buffer_size(GEN_CARD_CONFIG_TYPE& config);
    Errors_e convert_errorCode(const int code) const;

    template <typename T>
    Errors_e fill_buffer(T* sourceBuffer, Buffer<T>& bufferToFill)
    {
        int retVal = m_service->pcm_readi(sourceBuffer, m_bufferSize);
        if (retVal < 0)
        {
            return convert_errorCode(retVal);
        }
        bufferToFill.init(m_bufferSize);
        for (int i = 0; i < m_bufferSize; ++i)
        {
            bufferToFill[i] = sourceBuffer[i];
        }
        return Errors_e::NO_ERROR;
    }
};

#endif
