#include "FakeCardConfigurator.cpp"
#include "../ALSACardManager.cpp"
#include <gtest/gtest.h>
#include <string>


const std::string HW_ID = "hw:2,0";


class TestALSACardManager : public testing::Test
{
public:
    ALSACardManager manager;
    FakeCardConfigurator configurator;
    ALSACardConfiguration_t config;
    ALSACardLister lister;
    FakeCardInfoGetter infoGetter;

    void SetUp() override 
    {
        infoGetter.set_state(State_GetSuccess);
        lister.init(&infoGetter);
        manager.init_lister(&lister);
        manager.init_configurator(&configurator);
    }
};

TEST_F(TestALSACardManager, CreatesInstance)
{
    ALSACardManager manager;
}

/*****************************************
 * LISTER TESTING
 ****************************************/

TEST_F(TestALSACardManager, ReturnsNotInitializedIfListerNotInitialized)
{
    ALSACardManager manager_not_initialized;

    Errors_e retval = manager_not_initialized.select_and_configure();
    
    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NOT_INITIALIZED);
}

TEST_F(TestALSACardManager, ReturnsNoErrorOnSuccess)
{
    CARD_INFO_TYPE usb_card;

    Errors_e retval = manager.get_usb_cardInfo(usb_card);
    
    ASSERT_EQ(retval, Errors_e::NO_ERROR);
}

TEST_F(TestALSACardManager, GetUSBCardInfoReturnsCorrectErrorIfNoUSBCardsFound)
{
    auto lambda = [] (const CARD_INFO_TYPE& card) { return card.name.find(FAILURE_TAG) != std::string::npos; };
    manager.set_filter(lambda);
    CARD_INFO_TYPE usb_card;

    Errors_e retval = manager.get_usb_cardInfo(usb_card);
    
    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND);    
}

TEST_F(TestALSACardManager, CreateHwIdReturnsCorrectErrorIfNoUSBCardsFound)
{
    auto lambda = [] (const CARD_INFO_TYPE& card) { return card.name.find(FAILURE_TAG) != std::string::npos; };
    manager.set_filter(lambda);
    std::string hw_id { };

    Errors_e retval = manager.create_usb_hw_id(hw_id);
    
    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND);
}

TEST_F(TestALSACardManager, BuildsCorrectHWIDStringFromUSBCardID)
{
    std::string hw_id { };

    Errors_e retval = manager.create_usb_hw_id(hw_id);

    ASSERT_EQ(hw_id, HW_ID);     
}

TEST_F(TestALSACardManager, ReturnsNoSoundcardsFoundIfOpenFailure)
{
    infoGetter.set_state(State_OpenFailure);
    lister.init(&infoGetter);
    manager.init_lister(&lister);

    Errors_e retval = manager.select_and_configure();

    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND);
}

TEST_F(TestALSACardManager, ReturnsNoSoundcardsFoundIfGetFailure)
{
    infoGetter.set_state(State_GetFailure);
    lister.init(&infoGetter);
    manager.init_lister(&lister);

    Errors_e retval = manager.select_and_configure();

    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NO_USB_CARDS_FOUND);
}

/*****************************************
 * CONFIGURATOR TESTING
 ****************************************/

TEST_F(TestALSACardManager, ReturnsNotInitializedIfConfiguratorNotInitialized)
{
    ALSACardManager manager_not_initialized;
    manager_not_initialized.init_lister(&lister);

    Errors_e retval = manager_not_initialized.select_and_configure();
    
    ASSERT_EQ(retval, Errors_e::AUDIO_MANAGER_NOT_INITIALIZED);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterOpenDeviceFailure)
{
    configurator.set_state(State_OpenDeviceFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_CANT_OPEN_PCM_DEVICE);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterAllocationFailure)
{
    configurator.set_state(State_AllocationFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_ERROR_ALLOCATING_PARAM_HW);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterParamInitFailure)
{
    configurator.set_state(State_ParamInitFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_ERROR_INITIALIZING_PARAM);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterSettingAccessModeFailure)
{
    configurator.set_state(State_SetAccessModeFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_ERROR_SETTING_ACCESS_MODE);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterSettingAudioFormatFailure)
{
    configurator.set_state(State_SetAudioFormatFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_ERROR_SETTING_AUDIO_FORMAT);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterSettingSampleRateFailure)
{
    configurator.set_state(State_SetSampleRateFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_ERROR_SETTING_SAMPLE_RATE);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterSetNumChannelsFailure)
{
    configurator.set_state(State_SetNumChannelsFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_ERROR_SETTING_NUMBER_OF_CHANNELS);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterAfterApplyingFailure)
{
    configurator.set_state(State_ApplyParamsFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_ERROR_APPLYING_HW_PARAMS);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusAfterPreparationFailure)
{
    configurator.set_state(State_PrepareInterfaceFailure);

    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::AUDIO_CONFIG_ERROR_PREPARING_INTERFACE);
}

TEST_F(TestALSACardManager, ReturnsCorrectStatusUponSuccess)
{
    configurator.set_state(State_ConfigSuccess);
    
    manager.init_configurator(&configurator);
    
    ASSERT_EQ(manager.select_and_configure(), Errors_e::NO_ERROR);
}