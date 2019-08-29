#ifndef _FAKERECORDINGSERVICE_H
#define _FAKERECORDINGSERVICE_H

#include "../IRecordingService.hpp"


//States used in this mock
enum FakeRecordingServiceStates_e
{
	State_CaptureSuccess,
    State_CaptureReturns_EBADFD_DropError,
	State_CaptureReturns_EBADFD_DropSuccess_RecoverError,
	State_CaptureReturns_EBADFD_DropSuccess_RecoverSuccess,
    State_CaptureReturns_EPIPE_RestSuccessful,
	State_CaptureReturns_ESTRPIPE_RestSuccessful
};


//Mock object for testing
class FakeRecordingService : public IRecordingService
{
public:
	FakeRecordingService() { }
	~FakeRecordingService() { }

    //Interface functions
    int pcm_readi(int size) override;

	//Set state of mock - defines test case
	void set_state(FakeRecordingServiceStates_e state);

protected:
    int pcm_drop() override;
    int pcm_recover() override;
	
private:
	FakeRecordingServiceStates_e m_state;

};

#endif
