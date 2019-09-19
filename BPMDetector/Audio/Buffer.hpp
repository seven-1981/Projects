#ifndef _BUFFER_H
#define _BUFFER_H

#include <cassert>
#include <memory>
#include <algorithm>


using SIZE_TYPE = unsigned int;


template <typename DATA_TYPE>
class Buffer
{
    using CONT_TYPE = std::unique_ptr<DATA_TYPE[]>;

public:
    Buffer<DATA_TYPE>() : m_size(0), m_is_initialized(false) { }
    Buffer<DATA_TYPE>(SIZE_TYPE size) : m_size(size), m_is_initialized(false) { init(size); }
    
    Buffer<DATA_TYPE>(const Buffer<DATA_TYPE>& rhs)
    {
        assert(rhs.m_is_initialized == true);
        init(rhs.m_size);
        for (SIZE_TYPE i = 0; i < rhs.m_size; ++i)
        {
            m_data[i] = rhs.m_data[i];
        }
    }

    Buffer<DATA_TYPE>(Buffer<DATA_TYPE>&& rhs)
    {
        assert(rhs.m_is_initialized == true);
        init(rhs.m_size);
        rhs.m_is_initialized = false;
        rhs.m_size = 0;
        m_data = std::move(rhs.m_data);
    }

    Buffer<DATA_TYPE>& operator=(Buffer<DATA_TYPE> rhs)
    {
        //Use copy/swap idiom
        //Note that the only operator= has by-value argument
        //Therefore copy constructor is called
        swap(*this, rhs);
        return *this;
    }

    void init(SIZE_TYPE size)
    {
        if (m_is_initialized == false)
        {
            m_data = CONT_TYPE(new DATA_TYPE[size]);
            m_size = size;
            m_is_initialized = true;
        }
    }

    SIZE_TYPE get_size() const
    {
        return m_size;
    }

    DATA_TYPE operator[](const SIZE_TYPE index) const
    {
        assert(m_is_initialized == true);
        assert(index < m_size);
        return m_data[index];
    }

    DATA_TYPE& operator[](const SIZE_TYPE index)
    {
        assert(m_is_initialized == true);
        assert(index < m_size);
        return m_data[index];
    }

    friend void swap(Buffer<DATA_TYPE>& first, Buffer<DATA_TYPE>& second)
    {
        using std::swap; //For argument-dependent name lookup
        swap(first.m_size, second.m_size);
        swap(first.m_is_initialized, second.m_is_initialized);
        first.m_data.swap(second.m_data); //Use of unique_ptr's swap
    }

private:
    SIZE_TYPE m_size;
    CONT_TYPE m_data;
    bool m_is_initialized;
};

#endif