#ifndef _FAKERECORDINGSERVICE_H
#define _FAKERECORDINGSERVICE_H

#include "IRecordingService.hpp"


//Forward declarations
enum class Errors_e;
struct ICardConfiguration_t;
struct ALSACardConfiguration_t;
//Type simplifications
using GEN_CARD_CONFIG_TYPE = ICardConfiguration_t;
using CARD_CONFIG_TYPE = ALSACardConfiguration_t;


//States used in this mock
enum FakeRecordingServiceStates_e
{
	State_CaptureSuccess,
    State_CaptureReturns_EBADFD_RecoverNotPossible,
    State_CaptureReturns_EPIPE_RecoverError,
	State_CaptureReturns_EPIPE_RecoverSuccess,
    State_CaptureReturns_ESTRPIPE_RecoverError,
	State_CaptureReturns_ESTRPIPE_RecoverSuccess
};


//Mock object for testing
class FakeRecordingService : public IRecordingService
{
public:
	FakeRecordingService() : 
	  m_state(FakeRecordingServiceStates_e::State_CaptureReturns_EBADFD_RecoverNotPossible), 
      m_isHandleSet(false) { }
	~FakeRecordingService() { }

    //Interface functions
    Errors_e set_handle(ICardConfiguration_t& config) override;
	bool is_handleSet() override;
    int pcm_readi(void* buffer, int size) override;

	//Set state of mock - defines test case
	void set_state(FakeRecordingServiceStates_e state);
	
private:
	FakeRecordingServiceStates_e m_state;
	bool m_isHandleSet;

    int pcm_drop() override;
    int pcm_recover(int err, int silent) override;
};

#endif
