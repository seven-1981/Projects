#ifndef _ALSARECORDINGSERVICE_H
#define _ALSARECORDINGSERVICE_H

#include "IRecordingService.hpp"

#include <alsa/asoundlib.h>


//Forward declaration
enum class Errors_e;
struct ALSACardConfiguration_t;
//Typename simplifications
using CARD_CONFIG_TYPE = ALSACardConfiguration_t;
using GEN_CARD_CONFIG_TYPE = ICardConfiguration_t;


class ALSARecordingService : public IRecordingService
{
public:
    ALSARecordingService() : 
      m_pcmHandle(nullptr), 
      m_isHandleSet(false) { }
    ~ALSARecordingService() { }

    //Interface functions
    Errors_e set_handle(GEN_CARD_CONFIG_TYPE& config) override;
    bool is_handleSet() override;
    int pcm_readi(void* buffer, int size) override;

private:
    snd_pcm_t* m_pcmHandle;
    bool m_isHandleSet;

    int pcm_drop() override;
    int pcm_recover(int err, int silent) override;
};

#endif