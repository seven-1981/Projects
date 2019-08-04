#ifndef _ALSACARDCONFIGURATOR_H
#define _ALSACARDCONFIGURATOR_H

#include "ICardConfigurator.hpp"
#include "ALSACardConfiguration.hpp"

#include <alsa/asoundlib.h>
#include <string>


//Forward declaration of error enum class
enum class Errors_e;
//Using for card config type
using CARD_CONFIG_TYPE = ALSACardConfiguration_t;


//Card info configuration with ALSA API
class ALSACardConfigurator : public ICardConfigurator<CARD_CONFIG_TYPE>
{
public:
	explicit ALSACardConfigurator() : m_hw_id() { }
	~ALSACardConfigurator() { }

	//Override the base class methods
	void set_hw_id(std::string& hw_id) override;
	Errors_e configure(CARD_CONFIG_TYPE& config) override;
	
private:
	//Handle for the PCM device
	snd_pcm_t* m_pcmHandle;
	//Hardware parameters
	snd_pcm_hw_params_t* m_hwParams;
	//Hardware identifier used for open PCM device
	std::string m_hw_id;
	
	//Configuration functions are executed in this particular order
	int open_device(CARD_CONFIG_TYPE& config);
	int allocate_param_struct();
	int init_param_struct();
	int set_access_mode(CARD_CONFIG_TYPE& config);
	int set_audio_format(CARD_CONFIG_TYPE& config);
	int set_sample_rate(CARD_CONFIG_TYPE& config);
	int set_num_channels(CARD_CONFIG_TYPE& config);
	int apply_params();
	int prepare_interface();
};

#endif
