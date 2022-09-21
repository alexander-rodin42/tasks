#include "SimpleString.h"

using namespace rav;

SimpleString::SimpleString()
{
    m_shortData[0] = '\0';
}

SimpleString::SimpleString(const char* data) : m_size(stringLength(data))
{
    if (data == nullptr)
    {
        m_shortData[0] = '\0';
    }

    if (m_size <= kShortStringSize)
    {
        copyData(data, m_shortData, m_size);
    }
    else
    {
        m_capacity = m_size + kExtraBuffer;
        try
        {
            m_longData = new char[m_capacity + 1];
        }
        catch (...)  // (const std::bad_alloc& e) "1. Written in C++11 without any third party libraries."
        {
            throw;  // std::runtime_error("Memory was not allocated for allocator.");
        }

        copyData(data, m_longData, m_size);
        m_shortData[0] = '\0';
    }
}

SimpleString::SimpleString(const SimpleString& other) : m_size(other.m_size), m_capacity(other.m_capacity)
{
    if (other.isShortString())
    {
        copyData(other.m_shortData, m_shortData, m_size);
    }
    else
    {
        try
        {
            m_longData = new char[m_capacity + 1];
        }
        catch (...)
        {
            throw;
        }

        copyData(other.m_longData, m_longData, m_size);
        m_shortData[0] = '\0';
    }
}

SimpleString& SimpleString::operator=(const SimpleString& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (other.isShortString())
    {
        m_size = other.m_size;
        copyData(other.m_shortData, m_shortData, m_size);
    }
    else
    {
        if (m_capacity < other.m_size)
        {
            char* tempData = m_longData;

            try
            {
                m_longData = new char[other.m_capacity + 1];
            }
            catch (...)
            {
                m_longData = tempData;
                throw;
            }

            m_capacity = other.m_capacity;
            delete[] tempData;
        }

        m_size = other.m_size;
        copyData(other.m_longData, m_longData, other.m_size);
        m_shortData[0] = '\0';
    }
}

rav::SimpleString::SimpleString(SimpleString&& other) noexcept
{
    if (other.isShortString())
    {
        m_size = other.m_size;
        copyData(other.m_shortData, m_shortData, m_size);
    }
    else
    {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_longData = other.m_longData;
        m_shortData[0] = '\0';
    }

    other.bringToDefault();
}

SimpleString& SimpleString::operator=(SimpleString&& other) noexcept
{
    if (this != &other)
    {
        if (!m_longData)
        {
            delete[] m_longData;
            m_longData = nullptr;
        }

        m_size = other.m_size;
        m_capacity = other.m_capacity;

        if (other.isShortString())
        {
            copyData(other.m_shortData, m_shortData, other.m_size);
        }
        else
        {
            m_longData = other.m_longData;
            m_shortData[0] = '\0';
        }

        other.bringToDefault();
    }

    return *this;
}

SimpleString::~SimpleString()
{
    if (!(isShortString()))
    {
        delete[] m_longData;
    }
}

char& SimpleString::operator[](const size_t index)
{
    if (isShortString())
    {
        return m_shortData[index];
    }
    else
    {
        return m_longData[index];
    }
}

const char& SimpleString::operator[](const size_t index) const
{
    return this->operator[](index);
}

bool SimpleString::operator<(const SimpleString& other) noexcept
{
    if (m_size == 0 && other.m_size != 0)
    {
        return true;
    }

    if (m_size != 0 && other.m_size != 0)
    {
        const auto* first = data();
        const auto* second = other.data();

        for (size_t i = 0; i < m_size && i < other.m_size; ++i)
        {
            if (first[i] != second[i])
            {
                return first[i] < second[i] ? true : false;
            }
        }
        return m_size < other.m_size ? true : false;
    }
}

bool SimpleString::operator>(const SimpleString& other) noexcept
{
    return *this != other && !(*this < other);
}

bool SimpleString::operator==(const SimpleString& other) noexcept
{
    if (m_size != other.m_size)
    {
        return false;
    }

    if (m_size == 0 && other.m_size == 0)
    {
        return true;
    }

    const auto* first = data();
    const auto* second = other.data();

    for (size_t i = 0; i < m_size && i < other.m_size; ++i)
    {
        if (first[i] != second[i])
        {
            return false;
        }
    }
    return m_size == other.m_size ? true : false;
}

bool SimpleString::operator!=(const SimpleString& other) noexcept
{
    return !(*this == other);
}

SimpleString& SimpleString::operator+=(const SimpleString& other) noexcept
{
    const auto* second = other.data();

    this->reserve(m_size + other.m_size);
    copyData(second, begin(), other.m_size, m_size);
    m_size = m_size + other.m_size;

    return *this;
}

char* SimpleString::begin() noexcept
{
    if (isShortString())
    {
        return m_shortData;
    }
    else
    {
        return m_longData;
    }
}

char* SimpleString::end() noexcept
{
    if (isShortString())
    {
        return m_shortData + m_size;
    }
    else
    {
        return m_longData + m_size;
    }
}

size_t SimpleString::size() const noexcept
{
    return m_size;
}

size_t SimpleString::capacity() const noexcept
{
    return m_capacity;
}

bool SimpleString::empty() const noexcept
{
    return m_size == 0;
}

const char* SimpleString::data() const noexcept
{
    if (isShortString())
    {
        return m_shortData;
    }
    else
    {
        return m_longData;
    }
}

void SimpleString::reserve(size_t newCapacity)
{
    if (m_capacity < newCapacity)
    {
        char* tempData = m_longData;

        try
        {
            m_longData = new char[newCapacity + kExtraBuffer + 1];
        }
        catch (...)
        {
            m_longData = tempData;
            throw;
        }

        if (isShortString())
        {
            copyData(m_shortData, m_longData, m_size);
            m_shortData[0] = '\0';
        }
        else
        {
            copyData(tempData, m_longData, m_size);
            delete[] tempData;
        }

        m_capacity = newCapacity + kExtraBuffer;
    }
}

void SimpleString::bringToDefault()
{
    m_size = 0;
    m_capacity = kShortStringSize;
    m_shortData[0] = '\0';
    m_longData = nullptr;
}

bool SimpleString::isShortString() const
{
    return m_capacity > kShortStringSize ? false : true;
}

void SimpleString::copyData(const char* inputData, char* target, const size_t size, const size_t bedinIndex)
{
    if (inputData != nullptr)
    {
        for (size_t i = 0; i <= size; ++i)
        {
            target[bedinIndex + i] = inputData[i];
        }
    }
}

size_t SimpleString::stringLength(const char* begin)
{
    if (begin == nullptr)
        return 0;

    const char* end = begin;
    for (; *end != '\0'; ++end)
        ;
    return end - begin;
}

SimpleString rav::operator+(const SimpleString& first, const SimpleString& second)
{
    return SimpleString(first) += second;
}
