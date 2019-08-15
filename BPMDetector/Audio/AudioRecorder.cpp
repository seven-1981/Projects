#include "AudioRecorder.hpp"

void AudioRecorder::prepare_buffer(ICardConfiguration_t& configuration, long size)
{
    m_bufferSize = size;
}

long AudioRecorder::get_buffer_size()
{
    return m_bufferSize;
}