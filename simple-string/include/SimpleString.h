#pragma once

namespace rav {

    enum
    {
        kExtraBuffer = 5
    };

    class SimpleString
    {
    public:
        SimpleString() = default;
        SimpleString(const char* data);

        SimpleString(const SimpleString& other);
        SimpleString& operator=(const SimpleString& other);

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

        // Returns "nullptr" for objects:
        // 1) created by the default constructor
        // 2) after moving (std::move())
        const char* data() const noexcept;

        void reserve(size_t newCapacity);
        const SimpleString concatenate(const SimpleString& other) const;

    private:
        char* m_data = nullptr;
        size_t m_size = 0;
        size_t m_capacity = 0;

        void copyData(const char* inputData, const size_t size, const size_t bedinIndex = 0);
        void bringToDefault();
        static size_t stringLength(const char* begin);
    };

    // You can combine it with the concatenate() function and make it a friend of the SimpleString class.
    const SimpleString operator+(const SimpleString& first, const SimpleString& second);

}  // namespace rav
