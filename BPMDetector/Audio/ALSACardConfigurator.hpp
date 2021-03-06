#ifndef _ALSACARDCONFIGURATOR_H
#define _ALSACARDCONFIGURATOR_H

#include "ICardConfigurator.hpp"
#include "ALSACardConfiguration.hpp"

#include <alsa/asoundlib.h>
#include <string>


//Forward declarations
enum class Errors_e;
struct ICardConfiguration_t;
//Using for type simplifications
using GEN_CARD_CONFIG_TYPE = ICardConfiguration_t;
using CARD_CONFIG_TYPE = ALSACardConfiguration_t;


//Card info configuration with ALSA API
class ALSACardConfigurator : public ICardConfigurator
{
public:
	explicit ALSACardConfigurator() : m_hw_id() { }
	~ALSACardConfigurator() { }

	//Override the base class methods
	void set_hw_id(std::string& hw_id) override;
	Errors_e configure(GEN_CARD_CONFIG_TYPE& config) override;
	
private:
	//Hardware identifier used for open PCM device
	std::string m_hw_id;
	
	//Configuration functions are executed in this particular order
	int open_device(CARD_CONFIG_TYPE& config);
	int allocate_param_struct(CARD_CONFIG_TYPE& config);
	int init_param_struct(CARD_CONFIG_TYPE& config);
	int set_access_mode(CARD_CONFIG_TYPE& config);
	int set_audio_format(CARD_CONFIG_TYPE& config);
	int set_sample_rate(CARD_CONFIG_TYPE& config);
	int set_num_channels(CARD_CONFIG_TYPE& config);
	int apply_params(CARD_CONFIG_TYPE& config);
	int prepare_interface(CARD_CONFIG_TYPE& config);
	void free_params(CARD_CONFIG_TYPE& config);
};

#endif
