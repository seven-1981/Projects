#ifndef _ALSACARDLISTER_H
#define _ALSACARDLISTER_H

#include "ICardLister.hpp"

#include <vector>
#include <string>


//Forward declaration of interface class
class ICardInfoGetter;
//Forward declaration of card info
struct ALSACardInfo_t;
//Using for card info type
using CARD_INFO_TYPE = ALSACardInfo_t;


//Definition of audio card lister class for Linux sound (ALSA)
class ALSACardLister : public ICardLister<CARD_INFO_TYPE>
{
public:
	ALSACardLister();
	~ALSACardLister();
	
	//Init method - starts card detection
	void init(ICardInfoGetter* info_getter) override;
	
	//Override the base class methods
	std::vector<CARD_INFO_TYPE> get_cardInfos() const override;
	
private:
	//Soundcard info getter
	ICardInfoGetter* m_cardInfoGetter;
	//Soundcard infos
	std::vector<CARD_INFO_TYPE> m_cardInfo;
	
	//Start detection process
	void detect_soundcards();
	//Detect how many soundcards are installed
	unsigned int detect_num_soundcards() const;
	//Collect soundcard infos
	void collect_soundcard_infos(unsigned int numCards);
	//Create hw id string - used for open interface
	void build_hw_id_string(unsigned int id, std::string& hw_id, CARD_INFO_TYPE& info) const;
	//Open card control interface and try to extract name
	void open_and_extract(std::string& hw_id, CARD_INFO_TYPE& info);
	//Extract name of soundcard
	void extract_card_name(CARD_INFO_TYPE& info);
};

#endif
