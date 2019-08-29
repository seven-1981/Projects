#ifndef _ALSACARDCONFIGURATION_H
#define _ALSACARDCONFIGURATION_H

#include "ICardConfiguration.hpp"

#include <alsa/asoundlib.h>
#include <memory>


//Struct for ALSA card configuration parameters
struct ALSACardConfiguration_t : public ICardConfiguration_t
{
	snd_pcm_stream_t 	PCM_CAPTURE_MODE 	= SND_PCM_STREAM_CAPTURE;
	int 				PCM_BLOCKING_MODE 	= SND_PCM_NONBLOCK;
	snd_pcm_access_t 	PCM_ACCESS_MODE 	= SND_PCM_ACCESS_RW_INTERLEAVED;
	snd_pcm_format_t 	PCM_AUDIO_FORMAT 	= SND_PCM_FORMAT_S16_LE;
	unsigned int		PCM_SAMPLE_RATE		= 44100;
	unsigned int		PCM_NUM_CHANNELS	= 1;

	snd_pcm_hw_params_t* PCM_HW_PARAMS 		= nullptr;
	snd_pcm_t* PCM_HANDLE					= nullptr;
};

#endif

/*
// |snd_pcm_hw_params_t| is not exposed and requires memory allocation through
  // ALSA API. Therefore, use a smart pointer to pointer to insure freeing
  // memory when the function returns.
  std::unique_ptr<snd_pcm_hw_params_t*,
                  std::function<void(snd_pcm_hw_params_t**)>>
      params_holder(&hw_params, [wrapper](snd_pcm_hw_params_t** params) {
        wrapper->PcmHwParamsFree(*params);
      });
	  */


