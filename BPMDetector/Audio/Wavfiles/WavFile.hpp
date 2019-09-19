#ifndef _WAVFILE_H
#define _WAVFILE_H

#include <iostream>


const std::string FILE_ID = "RIFF----WAVEfmt ";   //Chunk size '-' to be filled in
const std::string DATA_ID = "data";
const size_t FILE_SIZE_POS = 4;     //Position of file size in .wav file
const size_t HEADER_POS = 16;       //Position of start of header info
const size_t DATA_POS = 44;         //Position of start of data


struct WavHeader_t
{
    unsigned int fmt_length = 16;               //Size of rest of format header in bytes
    unsigned int format_tag = 1;                //Format of wav file - 1 = canonical PCM
    unsigned int num_channels = 1;              //Number of channels - 1 = mono, 2 = stereo
    unsigned int sample_rate = 44100;           //Number of samples for each second and channel in Hz
    unsigned int frame_size = 2;                //Block alignment - frame size in bytes
                                                //Size of one frame = channels * (bits/sample + 7) / 8, without division rest
    unsigned int bytes_second = sample_rate * frame_size;
    unsigned int bits_sample = 16;              //Number of bits per sampple for each channel
};


class WavFile
{
public:
    explicit WavFile(std::iostream& ios) : m_data(ios) { }
    ~WavFile() { }

    template <typename T>
    friend WavFile& operator>>(WavFile& wavFile, T& value);
    template <typename T>
    friend WavFile& operator<<(WavFile& wavFile, T& value);

    std::string get_data() const;
    WavHeader_t get_header() const;
    size_t get_size() const;

    void write_header(WavHeader_t& header);
    void finish();

    friend WavFile& operator<<(WavFile& wavFile, const std::string& str); //Deliberately no template
    //because g++ doesn't allow template specialization in non-namespace scope

    WavFile(const WavFile&) = delete;
    WavFile& operator=(const WavFile&) = delete;
    WavFile(WavFile&&) = delete;
    WavFile& operator=(WavFile&&) = delete;

private:
    std::iostream& m_data;

    unsigned int read_word(unsigned int size) const;

	template <typename WORD>
	void write_word(WORD value, unsigned int size)
    {
        //Function to write "word" into output stream ("binary write"), only works for little endian (RIFF).
        //For big endian (RIFX), the for loop must be reversed.
        for (; size > 0; --size, value >>= 8)
        {
            m_data.put(static_cast<char>(value & 0xFF));
        }
    }
};

template <typename T>
WavFile& operator>>(WavFile& wavFile, T& value)
{
    if (wavFile.m_data.tellg() < DATA_POS)
    {
        wavFile.m_data.seekg(DATA_POS);
    }
    value = wavFile.read_word(sizeof(value));
    return wavFile;    
}

template <typename T>
WavFile& operator<<(WavFile& wavFile, T& value)
{
    wavFile.write_word(value, sizeof(value));
    return wavFile;
}

#endif
