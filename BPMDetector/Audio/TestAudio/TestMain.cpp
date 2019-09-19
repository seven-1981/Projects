#include <gtest/gtest.h>
#include "TestAudioCardLister.cpp"
#include "TestAudioCardFilter.cpp"
#include "TestAudioCardManager.cpp"
#include "TestBuffer.cpp"
#include "TestAudioRecorder.cpp"
#include "TestWavFile.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
