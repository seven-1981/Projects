#ifndef _FAKEAUDIORECORDER_H
#define _FAKEAUDIORECORDER_H

#include "../IAudioRecorder.hpp"


//States used in this mock
enum FakeAudioRecorderStates_e
{
	State_blablabla
};


//Mock object for testing
class FakeAudioRecorder : public IAudioRecorder
{
public:
	FakeAudioRecorder() { }
	~FakeAudioRecorder() { }

    //Interface functions
    long pcm_readi(unsigned long size) override;
	
private:

};

#endif
