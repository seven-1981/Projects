#include <gtest/gtest.h>
#include "TestALSACardLister.cpp"
#include "TestALSACardFilter.cpp"
#include "TestALSACardManager.cpp"

#include "TestAudioRecorder.cpp"
#include "TestBuffer.cpp"

#include "../Wavfiles/TestWavFile.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
