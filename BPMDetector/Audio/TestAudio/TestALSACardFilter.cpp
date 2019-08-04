#include "../ALSACardFilter.hpp"
#include <gtest/gtest.h>


const std::string FAILURE_TAG = "NOUSB";
const int SELECTED_CARD = 2;

class ALSACardInfo_t;
using CARD_LIST = std::vector<ALSACardInfo_t>;
using FILTER_FUNC = std::function<bool(const CARD_INFO_TYPE&)>;

class TestALSACardFilter : public testing::Test
{
public:
    ALSACardFilter<FILTER_FUNC> filter;
    CARD_LIST list;

    void SetUp() override 
    {
        CARD_INFO_TYPE info { };
        for (unsigned int i = 0; i < NUM_CARDS; ++i)
        {
            info.ID = i;
            info.name = FAKE_CARD_NAME[i];
            list.push_back(info);
        }
    }
};
 
TEST_F(TestALSACardFilter, CreatesInstance)
{
    ALSACardFilter<FILTER_FUNC> filter;
}

TEST_F(TestALSACardFilter, ReturnsEmptyListIfNoUSBCardsFound)
{
    auto lambda = [] (const CARD_INFO_TYPE& card) { return card.name.find(FAILURE_TAG) != std::string::npos; };
    filter.set_filter(lambda);

    CARD_LIST filtered_list = filter.apply_filter(list);

    ASSERT_EQ(filtered_list.size(), 0);
}

TEST_F(TestALSACardFilter, ReturnsCorrectSizeUponSuccess)
{
    CARD_LIST filtered_list = filter.apply_filter(list);

    ASSERT_EQ(filtered_list.size(), 1);
}

TEST_F(TestALSACardFilter, ReturnsCorrectIDUponSuccess)
{
    CARD_LIST filtered_list = filter.apply_filter(list);

    ASSERT_EQ(filtered_list.at(0).ID, SELECTED_CARD);
}

TEST_F(TestALSACardFilter, ReturnsCorrectListUponSuccess)
{
    CARD_LIST filtered_list = filter.apply_filter(list);

    ASSERT_EQ(filtered_list.at(0).name, FAKE_CARD_NAME[SELECTED_CARD]);
}