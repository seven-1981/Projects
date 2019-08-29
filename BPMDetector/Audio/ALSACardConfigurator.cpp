#include "ALSACardConfigurator.hpp"

#include "../globals.hpp"


void ALSACardConfigurator::set_hw_id(std::string& hw_id)
{
	m_hw_id = hw_id;
}

Errors_e ALSACardConfigurator::configure(GEN_CARD_CONFIG_TYPE& config)
{
	CARD_CONFIG_TYPE& typedConfig = dynamic_cast<CARD_CONFIG_TYPE&>(config);

	//Start onfiguration process
	if (open_device(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CANT_OPEN_PCM_DEVICE;
	}
	
	if (allocate_param_struct(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
	}
	
	if (init_param_struct(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
	}
	
	if (set_access_mode(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
	}
	
	if (set_audio_format(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
	}
	
	if (set_sample_rate(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
	}
	
	if (set_num_channels(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
	}
	
	if (apply_params(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
	}

	free_params(typedConfig);
	
	if (prepare_interface(typedConfig) < 0)
	{
		return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
	} 
	
	//Configuration was successful
	return Errors_e::NO_ERROR;
}

int ALSACardConfigurator::open_device(CARD_CONFIG_TYPE& config)
{
	//Open PCM device
	return snd_pcm_open(&config.PCM_HANDLE, m_hw_id.c_str(), config.PCM_CAPTURE_MODE, config.PCM_BLOCKING_MODE);	
}
	
int ALSACardConfigurator::allocate_param_struct(CARD_CONFIG_TYPE& config)
{
	//Allocate hardware parameter structure
	return snd_pcm_hw_params_malloc(&config.PCM_HW_PARAMS);
}

int ALSACardConfigurator::init_param_struct(CARD_CONFIG_TYPE& config)
{
	//Initialize parameter structure
	return snd_pcm_hw_params_any(config.PCM_HANDLE, config.PCM_HW_PARAMS);
}

int ALSACardConfigurator::set_access_mode(CARD_CONFIG_TYPE& config)
{
	//Set access mode
	return snd_pcm_hw_params_set_access(config.PCM_HANDLE, config.PCM_HW_PARAMS, config.PCM_ACCESS_MODE);	
}

int ALSACardConfigurator::set_audio_format(CARD_CONFIG_TYPE& config)
{
	//Set audio format
	return snd_pcm_hw_params_set_format(config.PCM_HANDLE, config.PCM_HW_PARAMS, config.PCM_AUDIO_FORMAT);	
}

int ALSACardConfigurator::set_sample_rate(CARD_CONFIG_TYPE& config)
{
	//Set sampling rate
	return snd_pcm_hw_params_set_rate_near(config.PCM_HANDLE, config.PCM_HW_PARAMS, &config.PCM_SAMPLE_RATE, 0);
}

int ALSACardConfigurator::set_num_channels(CARD_CONFIG_TYPE& config)
{
	//Set number of channels
	return snd_pcm_hw_params_set_channels(config.PCM_HANDLE, config.PCM_HW_PARAMS, config.PCM_NUM_CHANNELS);
}

int ALSACardConfigurator::apply_params(CARD_CONFIG_TYPE& config)
{
	//Apply hardware parameters
	return snd_pcm_hw_params(config.PCM_HANDLE, config.PCM_HW_PARAMS);	
}

int ALSACardConfigurator::prepare_interface(CARD_CONFIG_TYPE& config)
{
	//Prepare audio interface for usage
	return snd_pcm_prepare(config.PCM_HANDLE);	
}

void ALSACardConfigurator::free_params(CARD_CONFIG_TYPE& config)
{
	//Free allocated memory for hw params
	snd_pcm_hw_params_free(config.PCM_HW_PARAMS);
}