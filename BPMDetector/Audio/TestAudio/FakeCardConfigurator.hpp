#ifndef _FAKECARDCONFIGURATOR_H
#define _FAKECARDCONFIGURATOR_H

#include "../ICardConfigurator.hpp"
#include "../ALSACardConfiguration.hpp"


//Forward declarations
struct ICardConfiguration_t;
//Using for type simplifications
using GEN_CARD_CONFIG_TYPE = ICardConfiguration_t;
using CARD_CONFIG_TYPE = ALSACardConfiguration_t;

//States used in this mock
enum FakeCardConfiguratorStates_e
{
	State_OpenDeviceFailure,		//Open device returns error
	State_AllocationFailure, 		//HW param allocation error
	State_ParamInitFailure,			//HW param initialization error
	State_SetAccessModeFailure, 	//Set access mode returns error
	State_SetAudioFormatFailure,	//Set audio format returns error
	State_SetSampleRateFailure,		//Set sample rate returns error
	State_SetNumChannelsFailure,	//Set number of channels returns error
	State_ApplyParamsFailure,		//Apply params returns error
	State_PrepareInterfaceFailure,	//Prepare interface returns error
	State_ConfigSuccess				//Configuration successful
};


//Mock object for testing
class FakeCardConfigurator : public ICardConfigurator
{
public:
	FakeCardConfigurator() : m_hw_id() { }
	~FakeCardConfigurator() { }
	
	//Set state of mock - defines test case
	void set_state(FakeCardConfiguratorStates_e state);
	
	//Override the base class methods
	void set_hw_id(std::string& hw_id) override;
	Errors_e configure(GEN_CARD_CONFIG_TYPE& config) override;
	
private:
	FakeCardConfiguratorStates_e m_state;
	std::string m_hw_id;
};

#endif
