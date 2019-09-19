#include "WavFile.cpp"

#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <fstream>


const std::string SOME_DATA = "some data";
const std::string STANDARD_HEADER = { 
    0x52, 0x49, 0x46, 0x46, 0x2D, 0x2D, 0x2D, 0x2D, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
    0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x44, 0xAC, 0x00, 0x00, 0x88, 0x58, 0x01, 0x00,
    0x02, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61 };
const std::string SOME_PCM_DATA = {
    0x2D, 0x2D, 0x2D, 0x2D, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F };
const std::string FINISHED_HEADER = {
    0x52, 0x49, 0x46, 0x46, 0x40, 0x00, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
    0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x44, 0xAC, 0x00, 0x00, 0x88, 0x58, 0x01, 0x00,
    0x02, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61 };
const std::string FINISHED_DATA = {
    0x1C, 0x00, 0x00, 0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F };
const short int SOME_SHORT_DATA[] = { 
    0x001C,     0x0000,     0x0504,     0x0706,     0x0908,     0x0B0A,     0x0D0C,     0x0F0E,
    0x1110,     0x1312,     0x1514,     0x1716,     0x1918,     0x1B1A,     0x1D1C,     0x1F1E };
const unsigned int SHORT_DATA_SIZE = 16;
const unsigned int FILE_SIZE = 7;


bool operator==(const WavHeader_t& lhs, const WavHeader_t& rhs)
{
    return (lhs.fmt_length == rhs.fmt_length) 
        && (lhs.format_tag == rhs.format_tag)
        && (lhs.num_channels == rhs.num_channels)
        && (lhs.sample_rate == rhs.sample_rate)
        && (lhs.frame_size == rhs.frame_size)
        && (lhs.bytes_second == rhs.bytes_second)
        && (lhs.bits_sample == rhs.bits_sample);
}

    unsigned int fmt_length = 16;               //Size of rest of format header in bytes
    unsigned int format_tag = 1;                //Format of wav file - 1 = canonical PCM
    unsigned int num_channels = 1;              //Number of channels - 1 = mono, 2 = stereo
    unsigned int sample_rate = 44100;           //Number of samples for each second and channel in Hz
    unsigned int frame_size = 2;                //Block alignment - frame size in bytes
                                                //Size of one frame = channels * (bits/sample + 7) / 8, without division rest
    unsigned int bytes_second = sample_rate * frame_size;
    unsigned int bits_sample = 16;              //Number of bits per sampple for each channel

class TestWavFile : public testing::Test
{
public:
    std::stringstream outputFakeFile;
    std::stringstream inputFakeFile;
    WavHeader_t standardHeader;
    WavHeader_t modifiedHeader;
    WavFile* outputWavfile;
    WavFile* inputWavfile;

    void SetUp() override
    {
        outputWavfile = new WavFile(outputFakeFile);

        modifiedHeader.fmt_length = 32;
        modifiedHeader.format_tag = 2;
        modifiedHeader.num_channels = 2;
        modifiedHeader.sample_rate = 11025;
        modifiedHeader.frame_size = 4;
        modifiedHeader.bytes_second = 44100;
        modifiedHeader.bits_sample = 32;

        inputWavfile = new WavFile(inputFakeFile);
        inputWavfile->write_header(modifiedHeader);
        *inputWavfile << SOME_PCM_DATA;
        inputWavfile->finish();
    }

    void TearDown() override
    {
        delete outputWavfile;
        delete inputWavfile;
    }
};
 
TEST_F(TestWavFile, CreatesWavfile)
{
    WavFile file(outputFakeFile);
}

TEST_F(TestWavFile, WritesSomeDataIntoFile)
{   
    *outputWavfile << SOME_DATA;

    ASSERT_EQ(outputWavfile->get_data(), SOME_DATA);
}

TEST_F(TestWavFile, WritesHeaderIntoFile)
{
    outputWavfile->write_header(standardHeader);

    ASSERT_EQ(outputWavfile->get_data(), STANDARD_HEADER);
}

TEST_F(TestWavFile, WritesSamplesIntoFile)
{
    outputWavfile->write_header(standardHeader);

    *outputWavfile << SOME_PCM_DATA;
    
    ASSERT_EQ(outputWavfile->get_data(), STANDARD_HEADER + SOME_PCM_DATA);
}

TEST_F(TestWavFile, CreatesCorrectWavfileUponFinish)
{
    outputWavfile->write_header(standardHeader);
    *outputWavfile << SOME_PCM_DATA;
    
    outputWavfile->finish();

    ASSERT_EQ(outputWavfile->get_data(), FINISHED_HEADER + FINISHED_DATA);
}

TEST_F(TestWavFile, WritesShortDataCorrectly)
{
    outputWavfile->write_header(standardHeader);
    for (unsigned int i = 0; i < SHORT_DATA_SIZE; ++i)
        *outputWavfile << SOME_SHORT_DATA[i];

    outputWavfile->finish();

    ASSERT_EQ(outputWavfile->get_data(), FINISHED_HEADER + FINISHED_DATA);
}

TEST_F(TestWavFile, ReadsHeaderInformationFromExistingFile)
{
    WavHeader_t extractedHeader = inputWavfile->get_header();

    ASSERT_EQ(extractedHeader, modifiedHeader);
}

TEST_F(TestWavFile, ReadsSamplesFromFileCorrectly)
{
    unsigned char sample = 0x00;
    
    for (unsigned int i = 4; i < FINISHED_DATA.size(); ++i)
    {
        *inputWavfile >> sample;
        EXPECT_EQ(sample, FINISHED_DATA[i]);
    }
}

TEST_F(TestWavFile, ReadsSamplesFromFileCorrectlyAfterHeaderExtraction)
{
    IGNORE inputWavfile->get_header();
    unsigned char sample = 0x00;
    
    for (unsigned int i = 4; i < FINISHED_DATA.size(); ++i)
    {
        *inputWavfile >> sample;
        EXPECT_EQ(sample, FINISHED_DATA[i]);
    }
}

TEST_F(TestWavFile, ReadsFileSizeCorrectly)
{
    unsigned int file_size = inputWavfile->get_size();

    ASSERT_EQ(file_size, FILE_SIZE);
}

TEST_F(TestWavFile, SLOW_ReadsHeaderInformationFromFstreamFile)
{
    std::fstream fs("/home/pi/CPP/BPMDetector/Audio/Wavfiles/fast160.wav", std::ios_base::in | std::ios_base::binary);
    ASSERT_EQ(fs.is_open(), true);
    WavFile wavFile(fs);
    WavHeader_t extractedHeader = wavFile.get_header();

    ASSERT_EQ(extractedHeader, standardHeader);
}
