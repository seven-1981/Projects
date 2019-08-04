#ifndef _WAVFILE_H
#define _WAVFILE_H

#include <iostream>


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

    std::string get_data() const;
    WavHeader_t get_header() const;
    unsigned int get_size() const;

    template <typename T>
    friend WavFile& operator<<(WavFile& wavFile, T& value);

    void write_header(WavHeader_t& header);
    void finish();

    WavFile(const WavFile&) = delete;
    WavFile& operator=(const WavFile&) = delete;

private:
    std::iostream& m_data;
    bool is_valid;

	template <typename WORD>
	void write_word(WORD value, unsigned int size);

    unsigned int read_word(unsigned int size) const;
};

template <typename T>
WavFile& operator>>(WavFile& wavFile, T& value);

template <typename T>
WavFile& operator<<(WavFile& wavFile, T& value);

#endif