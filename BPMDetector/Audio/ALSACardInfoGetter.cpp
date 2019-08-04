#include "ALSACardInfoGetter.hpp"


int ALSACardInfoGetter::next(int& num)
{
	//Get number of next sound card
	return snd_card_next(&num);	
}

int ALSACardInfoGetter::open(std::string hw_id)
{
	//Open sound card and init handle
	return snd_ctl_open(&m_cardHandle, hw_id.c_str(), 0);	
}

int ALSACardInfoGetter::get_name(std::string& name)
{
	//We need to get a snd_ctl_card_info_t
	snd_ctl_card_info_alloca(&m_cardInfo);
	//Tell ALSA to fill in our snd_ctl_card_info_t with info about this card
	int err = snd_ctl_card_info(m_cardHandle, m_cardInfo);
	if (err >= 0)
	{
		name = snd_ctl_card_info_get_name(m_cardInfo);
	}
	return err;
}

void ALSACardInfoGetter::close()
{
	// Close the card's control interface after we're done with it
	snd_ctl_close(m_cardHandle);
}

void ALSACardInfoGetter::free() const
{
	//ALSA allocates some mem to load its config file when we call some of the
	//above functions. Now that we're done getting the info, let's tell ALSA
	//to unload the info and free up that mem
	snd_config_update_free_global();	
}
