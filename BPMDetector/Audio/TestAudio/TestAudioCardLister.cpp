#include "FakeCardInfoGetter.cpp"
#include "AudioCardLister.cpp"
#include <gtest/gtest.h>

class TestAudioCardLister : public testing::Test
{
public:
    FakeCardInfoGetter infoGetter;
    AudioCardLister lister;
    //Vector for soundcard info
    std::vector<CARD_INFO_TYPE> soundcardInfo;
};
 
TEST_F(TestAudioCardLister, CreatesInstance)
{
    AudioCardLister lister;
}

/*****************************************
 * NEXT FAILURE
 ****************************************/

TEST_F(TestAudioCardLister, ReturnsZeroSoundcardsAfterNextFailure)
{
    infoGetter.set_state(State_NextFailure);
    lister.init(&infoGetter);
    
    soundcardInfo = lister.get_cardInfos();
    
    ASSERT_EQ(soundcardInfo.size(), 0);
}

/*****************************************
 * NO SOUNDCARDS
 ****************************************/

TEST_F(TestAudioCardLister, ReturnsZeroSoundcardsAfterNoSoundcardsFromNext)
{
    infoGetter.set_state(State_NextSuccessNoSoundcards);
    lister.init(&infoGetter);

    soundcardInfo = lister.get_cardInfos();
    
    ASSERT_EQ(soundcardInfo.size(), 0);
}

/*****************************************
 * OPEN FAILURE
 ****************************************/

TEST_F(TestAudioCardLister, ReturnsCorrectNumSoundcardsAfterOpenError)
{
    infoGetter.set_state(State_OpenFailure);
    lister.init(&infoGetter);

    soundcardInfo = lister.get_cardInfos();
    
    ASSERT_EQ(soundcardInfo.size(), NUM_CARDS);
}

/*****************************************
 * GET FAILURE 
 ****************************************/

TEST_F(TestAudioCardLister, ReturnsCorrectNumSoundcardsAfterGetFailure)
{
    infoGetter.set_state(State_GetFailure);
    lister.init(&infoGetter);

    soundcardInfo = lister.get_cardInfos();
    
    ASSERT_EQ(soundcardInfo.size(), NUM_CARDS);
}

/*****************************************
 * PARTIAL GET SUCCESS 
 ****************************************/
 
 TEST_F(TestAudioCardLister, ReturnsCorrectSoundcardNamesAfterPartialSuccess)
{
    infoGetter.set_state(State_PartialSuccess);
    lister.init(&infoGetter);

    soundcardInfo = lister.get_cardInfos();
    
    for (unsigned int i = 0; i < soundcardInfo.size() - 1; ++i)
        EXPECT_EQ(soundcardInfo.at(i).name, FAKE_CARD_NAME[i]);
    ASSERT_EQ(soundcardInfo.at(soundcardInfo.size() - 1).name, "");
}

/*****************************************
 * GET SUCCESS 
 ****************************************/

TEST_F(TestAudioCardLister, ReturnsCorrectNumSoundcardsAfterSuccessfulDetection)
{
    infoGetter.set_state(State_GetSuccess);
    lister.init(&infoGetter);

    soundcardInfo = lister.get_cardInfos();
    
    ASSERT_EQ(soundcardInfo.size(), NUM_CARDS);
}

TEST_F(TestAudioCardLister, ReturnsCorrectSoundcardNamesAfterSuccessfulDetection)
{
    infoGetter.set_state(State_GetSuccess);
    lister.init(&infoGetter);
    
    soundcardInfo = lister.get_cardInfos();

    for (unsigned int i = 0; i < soundcardInfo.size(); ++i)
        EXPECT_EQ(soundcardInfo.at(i).name, FAKE_CARD_NAME[i]);
}

TEST_F(TestAudioCardLister, ReturnsCorrectSoundcardIdsAfterSuccessfulDetection)
{
    infoGetter.set_state(State_GetSuccess);
    lister.init(&infoGetter);
    
    soundcardInfo = lister.get_cardInfos();

    for (unsigned int i = 0; i < soundcardInfo.size(); ++i)
        EXPECT_EQ(soundcardInfo.at(i).ID, i);
}

TEST_F(TestAudioCardLister, ReturnsCorrectSoundcardHWIdsAfterSuccessfulDetection)
{
    infoGetter.set_state(State_GetSuccess);
    lister.init(&infoGetter);
    
    soundcardInfo = lister.get_cardInfos();

    for (unsigned int i = 0; i < soundcardInfo.size(); ++i)
    {
        std::string hw_id = HW_IDENTIFIER + std::to_string(i);
        EXPECT_EQ(soundcardInfo.at(i).hw_ID, hw_id);
    }
}
