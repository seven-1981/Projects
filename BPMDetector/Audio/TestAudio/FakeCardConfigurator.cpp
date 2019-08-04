#include "FakeCardConfigurator.hpp"
#include "../../globals.hpp"

void FakeCardConfigurator::set_hw_id(std::string& hw_id)
{
	m_hw_id = hw_id;
}

Errors_e FakeCardConfigurator::configure(CARD_CONFIG_TYPE& config)
{
	//Simulate results of configuration process
	switch (m_state)
	{
		case State_OpenDeviceFailure:
			return Errors_e::AUDIO_CONFIG_CANT_OPEN_PCM_DEVICE;
			break;
			
		case State_AllocationFailure:
			return Errors_e::AUDIO_CONFIG_ERROR_ALLOCATING_PARAM_HW;
			break;
			
		case State_ParamInitFailure:
			return Errors_e::AUDIO_CONFIG_ERROR_INITIALIZING_PARAM;
			break;
			
		case State_SetAccessModeFailure:
			return Errors_e::AUDIO_CONFIG_ERROR_SETTING_ACCESS_MODE;
			break;
			
		case State_SetAudioFormatFailure:
			return Errors_e::AUDIO_CONFIG_ERROR_SETTING_AUDIO_FORMAT;
			break;
			
		case State_SetSampleRateFailure:
			return Errors_e::AUDIO_CONFIG_ERROR_SETTING_SAMPLE_RATE;
			break;
			
		case State_SetNumChannelsFailure:
			return Errors_e::AUDIO_CONFIG_ERROR_SETTING_NUMBER_OF_CHANNELS;
			break;
			
		case State_ApplyParamsFailure:
			return Errors_e::AUDIO_CONFIG_ERROR_APPLYING_HW_PARAMS;
			break;
			
		case State_PrepareInterfaceFailure:
			return Errors_e::AUDIO_CONFIG_ERROR_PREPARING_INTERFACE;
			break;
			
		case State_ConfigSuccess:
			return Errors_e::NO_ERROR;
			break;
			
		default:
			return Errors_e::AUDIO_CONFIG_CANT_OPEN_PCM_DEVICE;
			break;
	}
}

void FakeCardConfigurator::set_state(FakeCardConfiguratorStates_e state)
{
	m_state = state;
}
