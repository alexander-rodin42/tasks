#pragma once

/*
    Comment to the task:
    A naive implementation of the string type without the use of third-party libraries and STL.
    Using the STL, you can add an STL-compatible iterator, as well as correctly handle std::bad_alloc exceptions.
*/

namespace rav {

    enum
    {
        kExtraBuffer = 5,
        kShortStringSize = 15
    };

    // A string up to and including 15 characters is stored on the stack, strings over 15 characters are stored on the heap.
    class SimpleString
    {
    public:
        class Iterator;

        SimpleString();

        // Not declared as "explicit" because an implicit conversion is needed for the outer operator+().
        SimpleString(const char* data);

        SimpleString(const SimpleString& other);
        SimpleString& operator=(const SimpleString& other);

        // A string of up to 15 characters inclusive is copied, more is moved.
        SimpleString(SimpleString&& other) noexcept;
        SimpleString& operator=(SimpleString&& other) noexcept;

        ~SimpleString();

        char& operator[](const size_t index);
        const char& operator[](const size_t index) const;

        bool operator<(const SimpleString& other) noexcept;
        bool operator>(const SimpleString& other) noexcept;
        bool operator==(const SimpleString& other) noexcept;
        bool operator!=(const SimpleString& other) noexcept;

        char* begin() noexcept;
        char* end() noexcept;
        size_t size() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;
        const char* data() const noexcept;

        void reserve(size_t newCapacity);

        // Returns a non-const object for std::move() to work.
        SimpleString concatenate(const SimpleString& other) const;

    private:
        size_t m_size = 0u;
        size_t m_capacity = kShortStringSize;

        // Short string (size <= 15), located on the stack. (SSO)
        char m_shortData[kShortStringSize + 1];

        // Long string (size > 15), placed on the heap.
        char* m_longData = nullptr;

        void bringToDefault();
        bool isShortString() const;
        static void copyData(const char* inputData, char* target, const size_t size, const size_t bedinIndex = 0u);
        static size_t stringLength(const char* begin);
    };

    // It could have been implemented as concatenate() and made a friend of the SimpleString class.
    // Returns a non-constant object, like a std::string from the STL.
    SimpleString operator+(const SimpleString& first, const SimpleString& second);

}  // namespace rav
