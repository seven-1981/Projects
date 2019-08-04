#ifndef _ALSACARDINFOGETTER_H
#define _ALSACARDINFOGETTER_H

#include "ICardInfoGetter.hpp"

#include <alsa/asoundlib.h>
#include <string>


//Card info extraction with ALSA API
class ALSACardInfoGetter : public ICardInfoGetter
{
public:
	ALSACardInfoGetter() { }
	~ALSACardInfoGetter() { }
	
	//Override the base class methods
	int next(int& num) override;			//Get next sound card number
	int open(std::string hw_id) override;		//Open sound card interface
	int get_name(std::string& name) override;	//Get sound card name
	void close() override;						//Close control interface
	void free() const override;					//Release memory
	
private:
	//Handle for sound card interface
	snd_ctl_t* m_cardHandle;
	//Used to hold card information
	snd_ctl_card_info_t* m_cardInfo;
};

#endif
