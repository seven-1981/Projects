#include "ALSACardManager.hpp"

#include <string>


ALSACardManager::ALSACardManager() 
  : m_cardLister(nullptr), m_cardConfigurator(nullptr), m_configuration(), m_filter()
{

}

ALSACardManager::~ALSACardManager()
{
	
}

void ALSACardManager::init_configurator(CONFIGURATOR_TYPE* configurator)
{
	m_cardConfigurator = configurator;
}

void ALSACardManager::init_lister(LISTER_TYPE* lister)
{
	m_cardLister = lister;
}

void ALSACardManager::set_configuration(CARD_CONFIG_TYPE& configuration)
{
    m_configuration = configuration;
}

void ALSACardManager::set_filter(FILTER_FUNC func)
{
    m_filter.set_filter(func);
}

Errors_e ALSACardManager::get_usb_cardInfo(CARD_INFO_TYPE& info)
{
    if (m_cardLister != nullptr)
    {
        CARD_LIST cards = m_cardLister->get_cardInfos();
        CARD_LIST usb_cards = filter_cards(cards);
        if (usb_cards.size() == 0)
        {
            return Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND;
        }
        else
        {
            info = usb_cards.at(0);
            return Errors_e::NO_ERROR;
        }
    }
    else
    {
        return Errors_e::AUDIO_MANAGER_NOT_INITIALIZED;
    }
}

Errors_e ALSACardManager::create_usb_hw_id(std::string& hw_id)
{
    CARD_INFO_TYPE usb_card;
    Errors_e retval = get_usb_cardInfo(usb_card);
    if (retval == Errors_e::NO_ERROR)
    {
        hw_id = usb_card.hw_ID + usb_card.subdev;
    }
    return retval;
}

Errors_e ALSACardManager::select_and_configure()
{
    std::string hw_id { };
    Errors_e retval = create_usb_hw_id(hw_id);
    if (retval != Errors_e::NO_ERROR)
    {
        return retval;
    }

    return start_configuration(hw_id);
}

Errors_e ALSACardManager::start_configuration(std::string& hw_id)
{
    if (m_cardConfigurator != nullptr)
    {
        m_cardConfigurator->set_hw_id(hw_id);
        return m_cardConfigurator->configure(m_configuration);
    }
    else
    {
        return Errors_e::AUDIO_MANAGER_NOT_INITIALIZED;
    }
}

CARD_LIST ALSACardManager::filter_cards(CARD_LIST& cards)
{
    return m_filter.apply_filter(cards);    
}
