#include "ALSACardConfigurator.hpp"

#include "../globals.hpp"


void ALSACardConfigurator::set_hw_id(std::string& hw_id)
{
	m_hw_id = hw_id;
}

Errors_e ALSACardConfigurator::configure(CARD_CONFIG_TYPE& config)
{
	//Start onfiguration process
	if (open_device(config) < 0)
	{
		return Errors_e::AUDIO_CONFIG_CANT_OPEN_PCM_DEVICE;
	}
	
	if (allocate_param_struct() < 0)
	{
		return Errors_e::AUDIO_CONFIG_ERROR_ALLOCATING_PARAM_HW;
	}
	
	if (init_param_struct() < 0)
	{
		return Errors_e::AUDIO_CONFIG_ERROR_INITIALIZING_PARAM;
	}
	
	if (set_access_mode(config) < 0)
	{
		return Errors_e::AUDIO_CONFIG_ERROR_SETTING_ACCESS_MODE;
	}
	
	if (set_audio_format(config) < 0)
	{
		return Errors_e::AUDIO_CONFIG_ERROR_SETTING_AUDIO_FORMAT;
	}
	
	if (set_sample_rate(config) < 0)
	{
		return Errors_e::AUDIO_CONFIG_ERROR_SETTING_SAMPLE_RATE;
	}
	
	if (set_num_channels(config) < 0)
	{
		return Errors_e::AUDIO_CONFIG_ERROR_SETTING_NUMBER_OF_CHANNELS;
	}
	
	if (apply_params() < 0)
	{
		return Errors_e::AUDIO_CONFIG_ERROR_APPLYING_HW_PARAMS;
	}
	
	if (prepare_interface() < 0)
	{
		return Errors_e::AUDIO_CONFIG_ERROR_PREPARING_INTERFACE;
	} 
	
	//Configuration was successful
	return Errors_e::NO_ERROR;
}

int ALSACardConfigurator::open_device(CARD_CONFIG_TYPE& config)
{
	//Open PCM device
	return snd_pcm_open(&m_pcmHandle, m_hw_id.c_str(), config.PCM_CAPTURE_MODE, config.PCM_BLOCKING_MODE);	
}
	
int ALSACardConfigurator::allocate_param_struct()
{
	//Allocate hardware parameter structure
	return snd_pcm_hw_params_malloc(&m_hwParams);
}

int ALSACardConfigurator::init_param_struct()
{
	//Initialize parameter structure
	return snd_pcm_hw_params_any(m_pcmHandle, m_hwParams);
}

int ALSACardConfigurator::set_access_mode(CARD_CONFIG_TYPE& config)
{
	//Set access mode
	return snd_pcm_hw_params_set_access(m_pcmHandle, m_hwParams, config.PCM_ACCESS_MODE);	
}

int ALSACardConfigurator::set_audio_format(CARD_CONFIG_TYPE& config)
{
	//Set audio format
	return snd_pcm_hw_params_set_format(m_pcmHandle, m_hwParams, config.PCM_AUDIO_FORMAT);	
}

int ALSACardConfigurator::set_sample_rate(CARD_CONFIG_TYPE& config)
{
	//Set sampling rate
	return snd_pcm_hw_params_set_rate_near(m_pcmHandle, m_hwParams, &config.PCM_SAMPLE_RATE, 0);
}

int ALSACardConfigurator::set_num_channels(CARD_CONFIG_TYPE& config)
{
	//Set number of channels
	return snd_pcm_hw_params_set_channels(m_pcmHandle, m_hwParams, config.PCM_NUM_CHANNELS);
}

int ALSACardConfigurator::apply_params()
{
	//Apply hardware parameters
	return snd_pcm_hw_params(m_pcmHandle, m_hwParams);	
}

int ALSACardConfigurator::prepare_interface()
{
	//Prepare audio interface for usage
	return snd_pcm_prepare(m_pcmHandle);	
}
