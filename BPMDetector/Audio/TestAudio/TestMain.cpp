#include <gtest/gtest.h>
#include "TestALSACardLister.cpp"
#include "TestALSACardFilter.cpp"
#include "TestAudioCardManager.cpp"
#include "TestBuffer.cpp"

#include "../Wavfiles/TestWavFile.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
