#include "AudioCardManager.hpp"
#include "globals.hpp"

#include <string>


AudioCardManager::AudioCardManager() 
  : m_cardLister(nullptr), m_cardConfigurator(nullptr), m_filter()
{

}

AudioCardManager::~AudioCardManager()
{
	
}

void AudioCardManager::init_configurator(CONFIGURATOR_TYPE* configurator)
{
	m_cardConfigurator = configurator;
}

void AudioCardManager::init_lister(LISTER_TYPE* lister)
{
	m_cardLister = lister;
}

void AudioCardManager::set_filter(FILTER_FUNC func)
{
    m_filter.set_filter(func);
}

Errors_e AudioCardManager::get_usb_cardInfo(CARD_INFO_TYPE& info)
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

Errors_e AudioCardManager::create_usb_hw_id(std::string& hw_id)
{
    CARD_INFO_TYPE usb_card;
    Errors_e retval = get_usb_cardInfo(usb_card);
    if (retval == Errors_e::NO_ERROR)
    {
        hw_id = usb_card.hw_ID + usb_card.subdev;
    }
    return retval;
}

Errors_e AudioCardManager::select_and_configure(GEN_CARD_CONFIG_TYPE& config)
{
    std::string hw_id { };
    Errors_e retval = create_usb_hw_id(hw_id);
    if (retval != Errors_e::NO_ERROR)
    {
        return retval;
    }

    retval = store_hw_id(hw_id);
    if (retval != Errors_e::NO_ERROR)
    {
        return retval;
    }

    return configure(config);
}

Errors_e AudioCardManager::configure(GEN_CARD_CONFIG_TYPE& config)
{
    if (m_cardConfigurator != nullptr)
    {
        return m_cardConfigurator->configure(config);
    }
    else
    {
        return Errors_e::AUDIO_MANAGER_NOT_INITIALIZED;
    }
}

CARD_LIST AudioCardManager::filter_cards(CARD_LIST& cards)
{
    return m_filter.apply_filter(cards);    
}

Errors_e AudioCardManager::store_hw_id(std::string& hw_id)
{
    if (m_cardConfigurator != nullptr)
    {
        m_cardConfigurator->set_hw_id(hw_id);
        return Errors_e::NO_ERROR;
    }
    else
    {
        return Errors_e::AUDIO_MANAGER_NOT_INITIALIZED;
    }
}
