#include "ALSARecordingService.hpp"

#include "ALSACardConfiguration.hpp"
#include "globals.hpp"


//From ALSA interface, 0 = message, 1 = silent
const int RECOVER_SILENT = 1;


Errors_e ALSARecordingService::set_handle(GEN_CARD_CONFIG_TYPE& config)
{
    CARD_CONFIG_TYPE& typedConfig = dynamic_cast<CARD_CONFIG_TYPE&>(config);
    if (typedConfig.INITIALIZED == true)
    {
        m_isHandleSet = true;
        m_pcmHandle = typedConfig.PCM_HANDLE;
        return Errors_e::NO_ERROR;
    }
    else
    {
        return Errors_e::AUDIO_RECORDER_NOT_INITIALIZED;
    }
}

bool ALSARecordingService::is_handleSet()
{
    return m_isHandleSet;
}

int ALSARecordingService::pcm_readi(void* buffer, int size)
{
    int retVal = snd_pcm_readi(m_pcmHandle, buffer, size);
    if (retVal < 0)
    {
        IGNORE pcm_drop();
        return pcm_recover(retVal, RECOVER_SILENT);
    }
    else
    {
        return retVal;
    }
}

int ALSARecordingService::pcm_drop()
{
    return snd_pcm_drop(m_pcmHandle);
}

int ALSARecordingService::pcm_recover(int err, int silent)
{
    return snd_pcm_recover(m_pcmHandle, err, silent);

}