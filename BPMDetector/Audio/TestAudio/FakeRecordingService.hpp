#ifndef _FAKERECORDINGSERVICE_H
#define _FAKERECORDINGSERVICE_H

#include "../IRecordingService.hpp"


//States used in this mock
enum FakeRecordingServiceStates_e
{
	State_blablabla
};


//Mock object for testing
class FakeRecordingService : public IRecordingService
{
public:
	FakeRecordingService() { }
	~FakeRecordingService() { }

    //Interface functions
    long pcm_readi(unsigned long size) override;
	
private:

};

#endif
