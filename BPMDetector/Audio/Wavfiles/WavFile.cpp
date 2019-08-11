#include "WavFile.hpp"

#include <string>


const std::string FILE_ID = "RIFF----WAVEfmt ";   //Chunk size '-' to be filled in
const std::string DATA_ID = "data";
const size_t FILE_SIZE_POS = 4;     //Position of file size in .wav file
const size_t HEADER_POS = 16;       //Position of start of header info
const size_t DATA_POS = 44;         //Position of start of data


template <typename T>
WavFile& operator<<(WavFile& wavFile, T& value)
{
    wavFile.write_word(value, sizeof(value));
}

template <>
WavFile& operator<<(WavFile& wavFile, const std::string& str)
{
    for (char c : str)
    {
        wavFile.write_word(c, 1);
    }
    return wavFile;
}

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

std::string WavFile::get_data() const
{
    std::stringstream ss;
    ss << m_data.rdbuf();
    return ss.str();
}

WavHeader_t WavFile::get_header() const
{
    WavHeader_t headerToReturn;
    m_data.seekg(HEADER_POS);
    headerToReturn.fmt_length = read_word(4);
    headerToReturn.format_tag = read_word(2);
    headerToReturn.num_channels = read_word(2);
    headerToReturn.sample_rate = read_word(4);
    headerToReturn.bytes_second = read_word(4);
    headerToReturn.frame_size = read_word(2);
    headerToReturn.bits_sample = read_word(2);
    return headerToReturn;
}

size_t WavFile::get_size() const
{
    m_data.seekg(DATA_POS - 4);
    return read_word(4) / get_header().frame_size;
}

void WavFile::write_header(WavHeader_t& header)
{
    m_data.seekp(0);
    m_data << FILE_ID;                  //<< is only possible for ascii data
    write_word(header.fmt_length, 4);   //For binary data, we have to use ostream.put()
    write_word(header.format_tag, 2);
    write_word(header.num_channels, 2);
    write_word(header.sample_rate, 4);
    write_word(header.bytes_second, 4);
    write_word(header.frame_size, 2);
    write_word(header.bits_sample, 2);
    m_data << DATA_ID;
}

void WavFile::finish()
{
    size_t file_size = m_data.tellp();
    m_data.seekp(DATA_POS - 4);
    write_word(file_size - DATA_POS, 4);
    m_data.seekp(FILE_SIZE_POS);
    write_word(file_size - 8, 4);
}

template <typename WORD>
void WavFile::write_word(WORD value, unsigned int size)
{
	//Function to write "word" into output stream ("binary write"), only works for little endian (RIFF).
	//For big endian (RIFX), the for loop must be reversed.
	for (; size > 0; --size, value >>= 8)
    {
		m_data.put(static_cast<char>(value & 0xFF));
    }
}

unsigned int WavFile::read_word(unsigned int size) const
{
    //Function to read a "word" from the input stream ("binary read"), only works for little endian (RIFF).
    char extracted_char = 0x00;
    unsigned int word = 0;
    unsigned int width = size;
    for (; size > 0; --size)
    {
        m_data.get(extracted_char);
        word |= (unsigned int)extracted_char << (8 * (width - size));
    }
    return word;
}
