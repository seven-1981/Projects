#ifndef _BUFFER_H
#define  _BUFFER_H

#include <array>
#include <cassert>


using SIZE_TYPE = unsigned int;


template <typename DATA_TYPE, SIZE_TYPE SIZE>
class Buffer
{
public:
    //Do not declare any c'tors or d'tor here, because compiler will
    //generate them properly (data member std::array has copy assignment).
    //Also move constructors should be generated properly.

    SIZE_TYPE get_size() const
    {
        return SIZE;
    }

    DATA_TYPE operator[](const SIZE_TYPE index) const
    {
        assert(index < SIZE);
        return m_data.at(index);
    }

    DATA_TYPE& operator[](const SIZE_TYPE index)
    {
        assert(index < SIZE);
        return m_data.at(index);
    }

private:
    std::array<DATA_TYPE, SIZE> m_data;
};

#endif