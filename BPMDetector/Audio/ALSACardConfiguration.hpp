#ifndef _ALSACARDCONFIGURATION_H
#define _ALSACARDCONFIGURATION_H

#include <alsa/asoundlib.h>


//Struct for ALSA card configuration parameters
struct ALSACardConfiguration_t
{
	snd_pcm_stream_t 	PCM_CAPTURE_MODE 	= SND_PCM_STREAM_CAPTURE;
	int 				PCM_BLOCKING_MODE 	= SND_PCM_NONBLOCK;
	snd_pcm_access_t 	PCM_ACCESS_MODE 	= SND_PCM_ACCESS_RW_INTERLEAVED;
	snd_pcm_format_t 	PCM_AUDIO_FORMAT 	= SND_PCM_FORMAT_S16_LE;
	unsigned int		PCM_SAMPLE_RATE		= 44100;
	unsigned int		PCM_NUM_CHANNELS	= 1;
};

#endif
