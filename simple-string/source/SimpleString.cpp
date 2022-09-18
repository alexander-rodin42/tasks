#include "SimpleString.h"

using namespace rav;

SimpleString::SimpleString(const char* data) : m_size(stringLength(data)), m_capacity(m_size + kExtraBuffer)
{
    try
    {
        if (data)
        {
            m_data = new char[m_capacity + 1];
        }
    }
    catch (...)  // (const std::bad_alloc& e) "1. Written in C++11 without any third party libraries."
    {
        throw;  // std::runtime_error("Memory was not allocated for allocator.");
    }

    copyData(data, m_size);
}

SimpleString::SimpleString(const SimpleString& other) : m_size(other.m_size), m_capacity(other.m_capacity)
{
    try
    {
        if (other.m_data)
        {
            m_data = new char[m_capacity + 1];
        }
    }
    catch (...)
    {
        throw;
    }

    copyData(other.m_data, other.m_size);
}

SimpleString& SimpleString::operator=(const SimpleString& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (m_capacity < other.m_size)
    {
        char* tempData = m_data;

        try
        {
            if (other.m_data)
            {
                m_data = new char[other.m_capacity + 1];
            }
        }
        catch (...)
        {
            m_data = tempData;
            throw;
        }

        m_capacity = other.m_capacity;
        delete[] tempData;
    }

    m_size = other.m_size;
    copyData(other.m_data, other.m_size);

    return *this;
}

SimpleString::SimpleString(SimpleString&& other) noexcept
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = other.m_data;

    other.bringToDefault();
}

SimpleString& SimpleString::operator=(SimpleString&& other) noexcept
{
    if (this != &other)
    {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = other.m_data;

        other.bringToDefault();
    }

    return *this;
}

SimpleString::~SimpleString()
{
    delete[] m_data;
}

char& SimpleString::operator[](const size_t index)
{
    return m_data[index];
}

const char& SimpleString::operator[](const size_t index) const
{
    return m_data[index];
}

bool SimpleString::operator<(const SimpleString& other) noexcept
{
    if (m_size == 0 && other.m_size != 0)
    {
        return true;
    }

    if (m_size != 0 && other.m_size != 0)
    {
        for (size_t i = 0; i < m_size && i < other.m_size; ++i)
        {
            if (m_data[i] != other.m_data[i])
            {
                return m_data[i] < other.m_data[i] ? true : false;
            }
        }
        return m_size < other.m_size ? true : false;
    }

    return false;
}

bool SimpleString::operator>(const SimpleString& other) noexcept
{
    return *this != other && !(*this < other);
}

bool SimpleString::operator==(const SimpleString& other) noexcept
{
    if (m_size != 0 && other.m_size != 0)
    {
        for (size_t i = 0; i < m_size && i < other.m_size; ++i)
        {
            if (m_data[i] != other.m_data[i])
            {
                return false;
            }
        }
        return m_size == other.m_size ? true : false;
    }

    if (m_size == 0 && other.m_size == 0)
    {
        return true;
    }

    return false;
}

bool SimpleString::operator!=(const SimpleString& other) noexcept
{
    return !(*this == other);
}

char* SimpleString::begin() noexcept
{
    return m_data;
}

char* SimpleString::end() noexcept
{
    return m_data + m_size;
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
    return m_data;
}

void SimpleString::reserve(size_t newCapacity)
{
    char* tempData = m_data;

    try
    {
        m_data = new char[newCapacity + 1];
    }
    catch (...)
    {
        m_data = tempData;
        throw;
    }

    m_capacity = newCapacity;

    if (tempData != nullptr)
    {
        if (m_size <= m_capacity)
        {
            copyData(tempData, m_size);
        }
        else
        {
            copyData(tempData, m_capacity - 1);
            m_data[m_capacity] = '\0';
            m_size = m_capacity;
        }

        delete[] tempData;
    }
    else
    {
        m_data[0] = '\0';
    }
}

const SimpleString SimpleString::concatenate(const SimpleString& other) const
{
    if (m_size == 0 && other.m_size == 0)
    {
        return SimpleString();
    }

    SimpleString result;
    result.reserve(m_size + other.m_size + kExtraBuffer);
    result.copyData(m_data, m_size);
    result.copyData(other.m_data, other.m_size, m_size);
    result.m_size = m_size + other.m_size;

    return result;
}

void SimpleString::copyData(const char* inputData, const size_t size, const size_t bedinIndex)
{
    if (inputData != nullptr)
    {
        for (size_t i = 0; i <= size; ++i)
        {
            m_data[bedinIndex + i] = inputData[i];
        }
    }
}

void SimpleString::bringToDefault()
{
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
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

const SimpleString rav::operator+(const SimpleString& first, const SimpleString& second)
{
    return first.concatenate(second);
}
