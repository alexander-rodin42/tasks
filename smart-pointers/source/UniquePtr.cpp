#include <iostream>

template <typename Type>
class UniquePtr
{
public:
    explicit UniquePtr(Type* pointer) noexcept : m_pointer(pointer) {}

    explicit UniquePtr(const UniquePtr& another) = delete;
    UniquePtr& operator=(const UniquePtr& another) = delete;

    explicit UniquePtr(UniquePtr&& another) noexcept;
    UniquePtr& operator=(UniquePtr&& another) noexcept;

    ~UniquePtr();

    Type operator*() const noexcept;
    Type* operator->() const noexcept;
    operator bool() const noexcept;

    Type* get() const noexcept;
    Type* release() noexcept;
    void reset(Type* pointer = nullptr) noexcept;

private:
    Type* m_pointer;
};

template <typename Type>
UniquePtr<Type>::UniquePtr(UniquePtr&& another) noexcept
{
    m_pointer = another.m_pointer;
    another.m_pointer = nullptr;
}

template <typename Type>
UniquePtr<Type>& UniquePtr<Type>::operator=(UniquePtr&& another) noexcept
{
    if (this != &another)
    {
        delete m_pointer;
        m_pointer = another.m_pointer;
        another.m_pointer = nullptr;
    }
    return *this;
}

template <typename Type>
Type UniquePtr<Type>::operator*() const noexcept
{
    return *m_pointer;
}

template <typename Type>
Type* UniquePtr<Type>::operator->() const noexcept
{
    return m_pointer;
}

template <typename Type>
UniquePtr<Type>::operator bool() const noexcept
{
    return m_pointer != nullptr;
}

template <typename Type>
Type* UniquePtr<Type>::get() const noexcept
{
    return m_pointer;
}

template <typename Type>
Type* UniquePtr<Type>::release() noexcept
{
    Type* tmp = m_pointer;
    m_pointer = nullptr;
    return tmp;
}

template <typename Type>
void UniquePtr<Type>::reset(Type* pointer) noexcept
{
    delete m_pointer;
    m_pointer = pointer;
}

template <typename Type>
UniquePtr<Type>::~UniquePtr()
{
    delete m_pointer;
}

//------------------------------------------------------------------------

struct MyStruct
{
    double a;
    int b;
    char c;

    ~MyStruct()
    {
        std::cout << "MyStruct removed" << std::endl;
    }
};

int main()
{
    {
        UniquePtr<MyStruct> ptr1(new MyStruct());
        ptr1->a = 10.5;
        ptr1->b = 5;
        ptr1->c = 'C';

        UniquePtr<MyStruct> ptr2(std::move(ptr1));
        std::cout << "a: " << ptr2->a << " b: " << ptr2->b << " c: " << ptr2->c << std::endl;
    }  // End of visibility scope ptr2

    std::cout << "End of program." << std::endl;
    return EXIT_SUCCESS;
}
