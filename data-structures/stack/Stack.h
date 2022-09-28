#include <iostream>

namespace rav {
    template <typename T>
    class Stack
    {
    public:
        explicit Stack(const size_t inCapacity = 0u);
        Stack(const Stack<T>& other);
        Stack<T>& operator=(const Stack<T>& other);
        Stack(Stack<T>&& other) noexcept;
        Stack<T>& operator=(Stack<T>&& other) noexcept;
        ~Stack();

        T& top() const;
        bool empty() const;
        size_t size() const;

        void push(const T& value);
        void pop();
        void swap(T& other);

    private:
        T* m_data = nullptr;
        size_t m_size = 0u;
        size_t m_capacity = 0u;

        void reserve(const size_t newCapacity);
    };


    template <typename T>
    Stack<T>::Stack(const size_t inCapacity) : m_capacity(inCapacity)
    {
        if (inCapacity > 0)
        {
            try
            {
                m_data = static_cast<T*>(operator new(sizeof(T) * inCapacity));
            }
            catch (const std::bad_alloc& e)
            {
                throw std::runtime_error("Memory was not allocated.");
            }
        }
    }

    template <typename T>
    Stack<T>::Stack(const Stack<T>& other) : m_size(other.m_size), m_capacity(other.m_capacity)
    {
        if (other.m_data)
        {
            try
            {
                m_data = static_cast<T*>(operator new(sizeof(T) * m_capacity));
            }
            catch (const std::bad_alloc& e)
            {
                throw std::runtime_error("Memory was not allocated.");
            }

            for (size_t i = 0; i < m_size; ++i)
            {
                new (m_data + i) T(other.m_data[i]);
            }
        }
    }

    template <typename T>
    inline Stack<T>& Stack<T>::operator=(const Stack<T>& other)
    {
        if (this != &other)
        {
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            if (other.m_data)
            {
                try
                {
                    m_data = static_cast<T*>(operator new(sizeof(T) * m_capacity));
                }
                catch (const std::bad_alloc& e)
                {
                    throw std::runtime_error("Memory was not allocated.");
                }

                for (size_t i = 0; i < m_size; ++i)
                {
                    new (m_data + i) T(other.m_data[i]);
                }
            }
        }

        return *this;
    }

    template <typename T>
    Stack<T>::Stack(Stack<T>&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        other.m_data = nullptr;
        other.m_size = 0u;
        other.m_capacity = 0u;
    }

    template <typename T>
    Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
    {
        if (this != &other)
        {
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = nullptr;
            other.m_size = 0u;
            other.m_capacity = 0u;
        }

        return *this;
    }

    template <typename T>
    Stack<T>::~Stack()
    {
        if (m_size > 0)
        {
            std::destroy(m_data, m_data + m_size);
        }
        operator delete(m_data);
    }

    template <typename T>
    T& Stack<T>::top() const
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty.");
        }

        return m_data[m_size - 1];
    }

    template <typename T>
    bool Stack<T>::empty() const
    {
        return m_size == 0 ? true : false;
    }

    template <typename T>
    inline size_t Stack<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    void Stack<T>::push(const T& value)
    {
        if (m_size == m_capacity)
        {
            try
            {
                reserve(m_capacity * 2 + 1);
            }
            catch (const std::runtime_error& e)
            {
                throw e;
            }
        }

        new (m_data + m_size) T(value);
        ++m_size;
    }

    template <typename T>
    void Stack<T>::pop()
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty.");
        }

        --m_size;
        T* pointer = m_data + m_size;
        pointer->~T();
    }

    template <typename T>
    void Stack<T>::swap(T& other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    template <typename T>
    void Stack<T>::reserve(const size_t newCapacity)
    {
        if (m_capacity < newCapacity)
        {
            T* tempData = m_data;

            try
            {
                m_data = static_cast<T*>(operator new(sizeof(T) * newCapacity));
            }
            catch (const std::bad_alloc& e)
            {
                m_data = tempData;
                throw std::runtime_error("Memory was not allocated.");
            }

            for (size_t i = 0; i < m_size; ++i)
            {
                new (m_data + i) T(tempData[i]);
            }

            if (m_size > 0)
            {
                std::destroy(tempData, tempData + m_size);
            }
            operator delete(tempData);
        }

        m_capacity = newCapacity;
    }


}  // namespace rav
