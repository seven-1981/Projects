#ifndef _FAKECARDINFOGETTER_H
#define _FAKECARDINFOGETTER_H

#include "ICardInfoGetter.hpp"

#include <string>


//States used in this mock
enum FakeCardInfoStates_e
{
	State_NextFailure,				//next returns -1
	State_NextSuccessNoSoundcards, 	//next returns 0, num = -1
	State_OpenFailure,				//num = next, open returns -1
	State_GetFailure, 				//open returns 0, get returns -1
	State_GetSuccess,				//get returns 0, sets name
	State_PartialSuccess			//Only some cards set name
};


//Mock object for testing
class FakeCardInfoGetter : public ICardInfoGetter
{
public:
	FakeCardInfoGetter() : m_state(State_NextFailure), m_number(0), m_counter(0) { }
	~FakeCardInfoGetter() { }
	
	int next(int& num) override;
	int open(std::string hw_id) override;
	int get_name(std::string& name) override;
	
	//Set state of mock - defines test case
	void set_state(FakeCardInfoStates_e state);
	
private:
	FakeCardInfoStates_e m_state;
	int m_number;
	int m_counter;
};

#endif
