#ifndef _AUDIOCARDMANAGER_H
#define _AUDIOCARDMANAGER_H

#include "ICardManager.hpp"
#include "ICardLister.hpp"
#include "ICardConfigurator.hpp"
#include "ALSACardInfo.hpp"
#include "AudioCardFilter.hpp"

#include <functional>
#include <vector>


//Forward declarations
enum class Errors_e;
struct ICardConfiguration_t;
//Typename simplification
using CONFIGURATOR_TYPE = ICardConfigurator;
using LISTER_TYPE = ICardLister<ALSACardInfo_t>;
using GEN_CARD_CONFIG_TYPE = ICardConfiguration_t;
using CARD_INFO_TYPE = ALSACardInfo_t;
using FILTER_FUNC = std::function<bool(const ALSACardInfo_t&)>;
using CARD_LIST = std::vector<ALSACardInfo_t>;


class AudioCardManager : public ICardManager<LISTER_TYPE>
{
public:
	AudioCardManager();
	~AudioCardManager();
	
	void init_configurator(CONFIGURATOR_TYPE* configurator) override;
	void init_lister(LISTER_TYPE* lister) override;
	//Start card selection and configuration process
	Errors_e select_and_configure(GEN_CARD_CONFIG_TYPE& config) override;
	//Start manual configuration 
	Errors_e configure(GEN_CARD_CONFIG_TYPE& config) override;

	//Set filter for soundcard selection
	void set_filter(FILTER_FUNC func);
	//Get filtered soundcards
	Errors_e get_usb_cardInfo(CARD_INFO_TYPE& info);
	//Build hardware ID string
	Errors_e create_usb_hw_id(std::string& hw_id);
	
private:
	//Soundcard lister
	LISTER_TYPE* m_cardLister;
	//Soundcard configurator
	CONFIGURATOR_TYPE* m_cardConfigurator;
	//Filter to get USB card from card list
	AudioCardFilter<FILTER_FUNC> m_filter;

	//Apply filter to card list
	CARD_LIST filter_cards(CARD_LIST& list);
	//Store HW ID
	Errors_e store_hw_id(std::string& hw_id);
};

#endif
