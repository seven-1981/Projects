#ifndef _ALSACARDMANAGER_H
#define _ALSACARDMANAGER_H

#include "ICardManager.hpp"
#include "ICardLister.hpp"
#include "ICardConfigurator.hpp"
#include "ALSACardInfo.hpp"
#include "ALSACardConfiguration.hpp"
#include "ALSACardFilter.hpp"

#include <functional>
#include <vector>


//Forward declaration of error enum class
enum class Errors_e;
//Typename simplification
using CARD_INFO_TYPE = ALSACardInfo_t;
using LISTER_TYPE = ICardLister<ALSACardInfo_t>;
using CARD_CONFIG_TYPE = ALSACardConfiguration_t;
using CONFIGURATOR_TYPE = ICardConfigurator<ALSACardConfiguration_t>;
using CARD_LIST = std::vector<ALSACardInfo_t>;
using FILTER_FUNC = std::function<bool(const CARD_INFO_TYPE&)>;


class ALSACardManager : public ICardManager<CONFIGURATOR_TYPE, LISTER_TYPE, CARD_CONFIG_TYPE>
{
public:
	ALSACardManager();
	~ALSACardManager();
	
	void init_configurator(CONFIGURATOR_TYPE* configurator) override;
	void init_lister(LISTER_TYPE* lister) override;
	void set_configuration(CARD_CONFIG_TYPE& configuration) override;
	//Start card selection and configuration process
	Errors_e select_and_configure() override;

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
	//Soundcard configuration
	CARD_CONFIG_TYPE m_configuration;
	//Filter to get USB card from card list
	ALSACardFilter<FILTER_FUNC> m_filter;

	//Start configuration 
	Errors_e start_configuration(std::string& hw_id);
	//Apply filter to card list
	CARD_LIST filter_cards(CARD_LIST& list);
};

#endif
