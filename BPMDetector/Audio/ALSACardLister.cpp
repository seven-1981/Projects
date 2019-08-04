#include "ALSACardLister.hpp"

#include "../globals.hpp"
#include "ALSACardInfoGetter.hpp"
#include "ALSACardInfo.hpp"


//Used to create hardware identification string 
const std::string HW_IDENTIFIER = "hw:";
const std::string HW_SUBDEV_STR = ",0";


ALSACardLister::ALSACardLister() : m_cardInfoGetter(nullptr), m_cardInfo()
{

}

ALSACardLister::~ALSACardLister()
{
	
}

void ALSACardLister::init(ICardInfoGetter* info_getter)
{
	m_cardInfoGetter = info_getter;
	//Start detection process if initialized
	if (m_cardInfoGetter != nullptr)
	{
		m_cardInfo.clear();
		detect_soundcards();
	}
}

std::vector<CARD_INFO_TYPE> ALSACardLister::get_cardInfos() const
{
	return m_cardInfo;
}

void ALSACardLister::detect_soundcards()
{
	//Get the number of soundcards on the raspberry
	unsigned int numCards = detect_num_soundcards();

	//If no sound cards found, issue error
	if (numCards < 1)
	{
		return;
	}
	
	//Fill internal vector with data
	collect_soundcard_infos(numCards);
	//Free allocated memory
	m_cardInfoGetter->free();
}

unsigned int ALSACardLister::detect_num_soundcards() const
{
	unsigned int foundCards = 0;
	
	//First sound card always starts with 0, so we start with -1
	int cardNum = -1;
	//Return value from ALSA function
	int err = 0;
	
	while (1)
	{
		//Get number of next sound card
		err = m_cardInfoGetter->next(cardNum);
		if (err < 0)
			break;
			
		if (cardNum < 0)
			break;
		
		++foundCards;
	}
	
	m_cardInfoGetter->free();
	
	return foundCards;
}

void ALSACardLister::collect_soundcard_infos(unsigned int numCards)
{
	CARD_INFO_TYPE cardInfo;
	std::string hw_id { };
	//Loop through soundcards and collect infos
	for (unsigned int i = 0; i < numCards; ++i)
	{
		//Fill card info with data
		build_hw_id_string(i, hw_id, cardInfo);
		//Open card interface with built hw ID and try to extract name
		open_and_extract(hw_id, cardInfo);
		//Populate vector
		m_cardInfo.push_back(cardInfo);
		//Close card interface
		m_cardInfoGetter->close();
	}	
}

void ALSACardLister::build_hw_id_string(unsigned int id, std::string& hw_id, CARD_INFO_TYPE& info) const
{
	//Build id string from card id number
	hw_id = HW_IDENTIFIER + std::to_string(id);
	//Fill card info
	info.ID = id;
	info.hw_ID = hw_id;
	info.subdev = HW_SUBDEV_STR;
}	

void ALSACardLister::open_and_extract(std::string& hw_id, CARD_INFO_TYPE& info)
{
	//Open this card's control interface.
	int err = m_cardInfoGetter->open(hw_id);
	if (err >= 0)
	{
		//Open card interface successful, try to get name
		extract_card_name(info);
	}
}

void ALSACardLister::extract_card_name(CARD_INFO_TYPE& info)
{
	std::string card_name { };
	(void)m_cardInfoGetter->get_name(card_name);
	//Upon error, empty string is returned, so discard return value
	info.name = card_name;
}