#include "FakeCardInfoGetter.hpp"

#include <string>

const int RETURN_FAIL = -1;
const int RETURN_SUCCESS = 0;
const int NUM_CARDS = 4;
const std::string FAKE_CARD_NAME[NUM_CARDS] = { "Sound card 0: bcm2835 ALSA",
												"Sound card 1: bcm2835 ALSA",
												"Sound card 2: USB Audio",
												"Sound card 3: bcm2835 ALSA" };


int FakeCardInfoGetter::next(int& num)
{
	//Get number of next sound card
	switch (m_state)
	{
		case State_NextFailure:
			return RETURN_FAIL;
			break;
			
		case State_NextSuccessNoSoundcards:
			num = -1;
			return RETURN_SUCCESS;
			break;
			
		case State_OpenFailure:
		case State_GetFailure:
		case State_GetSuccess:
		case State_PartialSuccess:
			if (m_number >= NUM_CARDS)
				return RETURN_FAIL;
			num = m_number++;
			return RETURN_SUCCESS;
			break;
			
		default:
			return RETURN_FAIL;
			break;
	}

}

int FakeCardInfoGetter::open(std::string hw_id)
{
	//Open sound card and init handle
	switch (m_state)
	{
		case State_NextFailure:
		case State_NextSuccessNoSoundcards:
		case State_OpenFailure:
			return RETURN_FAIL;
			break;
		
		case State_GetFailure:
		case State_GetSuccess:
		case State_PartialSuccess:
			return RETURN_SUCCESS;
			break;
			
		default:
			return RETURN_FAIL;
			break;
	}
		
}

int FakeCardInfoGetter::get_name(std::string& name)
{
	//Retrieve card info string
	switch (m_state)
	{
		case State_NextFailure:
		case State_NextSuccessNoSoundcards:
		case State_OpenFailure:
		case State_GetFailure:
			return RETURN_FAIL;
			break;
			
		case State_GetSuccess:
			name = FAKE_CARD_NAME[m_counter++];
			return RETURN_SUCCESS;
			break;
			
		case State_PartialSuccess:
			//Last card not successful
			if (m_counter == NUM_CARDS - 1)
			{
				name = "";
				m_counter++;
				return RETURN_FAIL;
			}
			else
			{
				name = FAKE_CARD_NAME[m_counter++];
				return RETURN_SUCCESS;
			}
			break;
			
		default:
			return RETURN_FAIL;
			break;
	}
}

void FakeCardInfoGetter::set_state(FakeCardInfoStates_e state)
{
	m_state = state;
}
