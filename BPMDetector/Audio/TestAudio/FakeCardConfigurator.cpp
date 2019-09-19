#include "FakeCardConfigurator.hpp"
#include "globals.hpp"


void FakeCardConfigurator::set_hw_id(std::string& hw_id)
{
	m_hw_id = hw_id;
}

Errors_e FakeCardConfigurator::configure(GEN_CARD_CONFIG_TYPE& config)
{
	CARD_CONFIG_TYPE& typedConfig = dynamic_cast<CARD_CONFIG_TYPE&>(config);
	//Simulate results of configuration process
	switch (m_state)
	{
		case State_OpenDeviceFailure:
			return Errors_e::AUDIO_MANAGER_CANT_OPEN_PCM_DEVICE;
			break;
			
		case State_AllocationFailure:
		case State_ParamInitFailure:
		case State_SetAccessModeFailure:
		case State_SetAudioFormatFailure:
		case State_SetSampleRateFailure:
		case State_SetNumChannelsFailure:
		case State_ApplyParamsFailure:		
		case State_PrepareInterfaceFailure:
			return Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE;
			break;

		case State_ConfigSuccess:
			typedConfig.INITIALIZED = true;
			return Errors_e::NO_ERROR;
			break;
			
		default:
			return Errors_e::AUDIO_MANAGER_CANT_OPEN_PCM_DEVICE;
			break;
	}
}

void FakeCardConfigurator::set_state(FakeCardConfiguratorStates_e state)
{
	m_state = state;
}
