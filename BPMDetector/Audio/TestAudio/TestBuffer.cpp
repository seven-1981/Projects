#include "../Buffer.hpp"
#include "SampleData.hpp"
#include <gtest/gtest.h>


const unsigned int SIZE = 88200;
const unsigned int ARBITRARY_NUM_SAMPLES = 20;
const unsigned int INDEX_BEYOND_SIZE = 88201;


template <typename DT, unsigned int SZ>
bool operator==(const Buffer<DT, SZ>& lhs, const Buffer<DT, SZ>& rhs)
{
    if (lhs.get_size() < rhs.get_size())
        return false;
    for (unsigned int i = 0; i < lhs.get_size(); ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}


class TestBuffer : public testing::Test
{
public:
    Buffer<short unsigned int, SIZE> buffer;
};
 
TEST_F(TestBuffer, CreatesInstance)
{
    Buffer<short unsigned int, SIZE> buffer;
}

TEST_F(TestBuffer, ReturnsCorrectSize)
{
    ASSERT_EQ(buffer.get_size(), SIZE);
}

TEST_F(TestBuffer, WriteAndReadAccessWorksProperly)
{
    for (unsigned int i = 0; i < ARBITRARY_NUM_SAMPLES; ++i)
        buffer[i] = SAMPLE_DATA[i];

    for (unsigned int i = 0; i < ARBITRARY_NUM_SAMPLES; ++i)
        EXPECT_EQ(buffer[i], SAMPLE_DATA[i]);
}

TEST_F(TestBuffer, AssertionIfAccessBeyondSize)
{
    unsigned short int sample = 0;
    ASSERT_DEATH(sample = buffer[INDEX_BEYOND_SIZE], "");
}

//Disabled due to execution time comsumption
TEST_F(TestBuffer, SLOW_CopyConstructorWorksProperly)
{
    Buffer<short unsigned int, SIZE> copiedBuffer(buffer);
    ASSERT_EQ(copiedBuffer, buffer);
}

//Disabled due to execution time comsumption
TEST_F(TestBuffer, SLOW_AssignmentWorksProperly)
{
    Buffer<short unsigned int, SIZE> assignedBuffer = buffer;
    ASSERT_EQ(assignedBuffer, buffer);
}