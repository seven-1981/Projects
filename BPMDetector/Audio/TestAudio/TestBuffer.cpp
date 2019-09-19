#include "Buffer.hpp"
#include "SampleData.hpp"
#include <gtest/gtest.h>


const unsigned int SIZE = 88200;
const unsigned int ARBITRARY_NUM_SAMPLES = 20;
const unsigned int INDEX_BEYOND_SIZE = 88201;
const int ARBITRARY_INDEX = 77;


template <typename DT>
bool operator==(const Buffer<DT>& lhs, const Buffer<DT>& rhs)
{
    if (lhs.get_size() != rhs.get_size())
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
    Buffer<short unsigned int> buffer;
};
 
TEST_F(TestBuffer, CreatesEmptyInstance)
{
    ASSERT_EQ(buffer.get_size(), 0);
}

TEST_F(TestBuffer, CreatesInstanceWithSize)
{
    buffer.init(SIZE);

    ASSERT_EQ(buffer.get_size(), SIZE);
}

TEST_F(TestBuffer, AccessOnEmptyBufferNotPossible)
{
    ASSERT_DEATH(buffer[0], "");
}

TEST_F(TestBuffer, AssertionIfAccessBeyondSize)
{
    buffer.init(SIZE);

    ASSERT_DEATH(buffer[INDEX_BEYOND_SIZE], "");
}


TEST_F(TestBuffer, WriteAndReadAccessWorksProperly)
{
    buffer.init(SIZE);
    for (unsigned int i = 0; i < ARBITRARY_NUM_SAMPLES; ++i)
        buffer[i] = SAMPLE_DATA[i];

    for (unsigned int i = 0; i < ARBITRARY_NUM_SAMPLES; ++i)
        EXPECT_EQ(buffer[i], SAMPLE_DATA[i]);
}

TEST_F(TestBuffer, SLOW_CopyConstructorWorksProperly)
{
    buffer.init(SIZE);
    for (unsigned int i = 0; i < SIZE; ++i)
        buffer[i] = SAMPLE_DATA[i];

    Buffer<short unsigned int> copiedBuffer(buffer);

    ASSERT_EQ(copiedBuffer, buffer);
}

TEST_F(TestBuffer, MoveConstructorWorksProperly)
{
    buffer.init(SIZE);
    for (unsigned int i = 0; i < SIZE; ++i)
        buffer[i] = SAMPLE_DATA[i];

    Buffer<short unsigned int> movedBuffer(std::move(buffer));

    ASSERT_EQ(movedBuffer[ARBITRARY_INDEX], SAMPLE_DATA[ARBITRARY_INDEX]);
    ASSERT_DEATH(buffer[0], "");
}

TEST_F(TestBuffer, SLOW_AssignmentWorksProperly)
{
    Buffer<short unsigned int> assignedBuffer;
    buffer.init(SIZE);
    for (unsigned int i = 0; i < SIZE; ++i)
        buffer[i] = SAMPLE_DATA[i];

    assignedBuffer = buffer;

    ASSERT_EQ(assignedBuffer, buffer);
}

TEST_F(TestBuffer, MoveAssignmentWorksProperly)
{
    Buffer<short unsigned int> moveAssignedBuffer;
    buffer.init(SIZE);
    for (unsigned int i = 0; i < SIZE; ++i)
        buffer[i] = SAMPLE_DATA[i];

    moveAssignedBuffer = std::move(buffer);

    ASSERT_EQ(moveAssignedBuffer[ARBITRARY_INDEX], SAMPLE_DATA[ARBITRARY_INDEX]);
    ASSERT_DEATH(buffer[0], "");
}