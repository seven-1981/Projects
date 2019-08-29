#include "FakeCardConfigurator.cpp"
#include "../AudioCardManager.cpp"
#include <gtest/gtest.h>
#include <string>


const std::string HW_ID = "hw:2,0";


class TestAudioCardManager : public testing::Test
{
public:
    AudioCardManager manager;
    FakeCardConfigurator configurator;
    ALSACardConfiguration_t config;
    AudioCardLister lister;
    FakeCardInfoGetter infoGetter;

    void SetUp() override 
    {
        infoGetter.set_state(State_GetSuccess);
        lister.init(&infoGetter);
        manager.init_lister(&lister);
        manager.init_configurator(&configurator);
    }
};

TEST_F(TestAudioCardManager, CreatesInstance)
{
    AudioCardManager manager;
}

/*****************************************
 * LISTER TESTING
 ****************************************/

TEST_F(TestAudioCardManager, ReturnsNotInitializedIfListerNotInitialized)
{
    AudioCardManager manager_not_initialized;

    Errors_e retval = manager_not_initialized.select_and_configure(config);
    
    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NOT_INITIALIZED);
}

TEST_F(TestAudioCardManager, ReturnsNoErrorOnSuccess)
{
    CARD_INFO_TYPE usb_card;

    Errors_e retval = manager.get_usb_cardInfo(usb_card);
    
    ASSERT_EQ(retval, Errors_e::NO_ERROR);
}

TEST_F(TestAudioCardManager, GetUSBCardInfoReturnsCorrectErrorIfNoUSBCardsFound)
{
    auto lambda = [] (const CARD_INFO_TYPE& card) { return card.name.find(FAILURE_TAG) != std::string::npos; };
    manager.set_filter(lambda);
    CARD_INFO_TYPE usb_card;

    Errors_e retval = manager.get_usb_cardInfo(usb_card);
    
    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND);    
}

TEST_F(TestAudioCardManager, CreateHwIdReturnsCorrectErrorIfNoUSBCardsFound)
{
    auto lambda = [] (const CARD_INFO_TYPE& card) { return card.name.find(FAILURE_TAG) != std::string::npos; };
    manager.set_filter(lambda);
    std::string hw_id { };

    Errors_e retval = manager.create_usb_hw_id(hw_id);
    
    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND);
}

TEST_F(TestAudioCardManager, BuildsCorrectHWIDStringFromUSBCardID)
{
    std::string hw_id { };

    IGNORE manager.create_usb_hw_id(hw_id);

    ASSERT_EQ(hw_id, HW_ID);     
}

TEST_F(TestAudioCardManager, ReturnsNoSoundcardsFoundIfOpenFailure)
{
    infoGetter.set_state(State_OpenFailure);
    lister.init(&infoGetter);
    manager.init_lister(&lister);

    Errors_e retval = manager.select_and_configure(config);

    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND);
}

TEST_F(TestAudioCardManager, ReturnsNoSoundcardsFoundIfGetFailure)
{
    infoGetter.set_state(State_GetFailure);
    lister.init(&infoGetter);
    manager.init_lister(&lister);

    Errors_e retval = manager.select_and_configure(config);

    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND);
}

/*****************************************
 * CONFIGURATOR TESTING
 ****************************************/

TEST_F(TestAudioCardManager, ReturnsNotInitializedIfConfiguratorNotInitialized)
{
    AudioCardManager manager_not_initialized;
    manager_not_initialized.init_lister(&lister);

    Errors_e retval = manager_not_initialized.select_and_configure(config);
    
    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NOT_INITIALIZED);
}

TEST_F(TestAudioCardManager, ReturnsCorrectStatusAfterOpenDeviceFailure)
{
    configurator.set_state(State_OpenDeviceFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(config), Errors_e::AUDIO_MANAGER_CANT_OPEN_PCM_DEVICE);
}

TEST_F(TestAudioCardManager, ReturnsCorrectStatusAfterConfigFailure)
{
    configurator.set_state(State_AllocationFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(config), Errors_e::AUDIO_MANAGER_CARD_CONFIG_FAILURE);
}

TEST_F(TestAudioCardManager, ReturnsCorrectStatusUponSuccess)
{
    configurator.set_state(State_ConfigSuccess);
    
    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(config), Errors_e::NO_ERROR);
}

TEST_F(TestAudioCardManager, PerformsReconfiguration)
{
    configurator.set_state(State_ConfigSuccess);
    manager.init_configurator(&configurator);
    manager.select_and_configure(config);

    ASSERT_EQ(manager.configure(config), Errors_e::NO_ERROR);
}
