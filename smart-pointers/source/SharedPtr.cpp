#include <iostream>

template <typename Type>
class SharedPtr
{
public:
    explicit SharedPtr(Type* pointer) noexcept : m_pointer(pointer), m_referencesCount(new std::uint16_t(1)) {}

    explicit SharedPtr(const SharedPtr& another) noexcept;
    SharedPtr& operator=(const SharedPtr& another) noexcept;

    ~SharedPtr();

    Type operator*() const noexcept;
    Type* operator->() const noexcept;
    operator bool() const noexcept;

    Type* get() const noexcept;
    bool isUnique() const noexcept;
    std::uint16_t getReferencesCount() const noexcept;
    void reset(Type* pointer = nullptr) noexcept;

private:
    Type* m_pointer;
    std::uint16_t* m_referencesCount;
};

template <typename Type>
SharedPtr<Type>::SharedPtr(const SharedPtr& another) noexcept
{
    m_pointer = another.m_pointer;
    m_referencesCount = another.m_referencesCount;
    ++(*m_referencesCount);
}

template <typename Type>
SharedPtr<Type>& SharedPtr<Type>::operator=(const SharedPtr& another) noexcept
{
    if (this != &another)
    {
        --(*m_referencesCount);
        if (*m_referencesCount == 0)
        {
            delete m_pointer;
        }

        m_pointer = another.m_pointer;
        m_referencesCount = another.m_referencesCount;
        ++(*m_referencesCount);
    }
    return *this;
}

template <typename Type>
Type SharedPtr<Type>::operator*() const noexcept
{
    return *m_pointer;
}

template <typename Type>
Type* SharedPtr<Type>::operator->() const noexcept
{
    return m_pointer;
}

template <typename Type>
SharedPtr<Type>::operator bool() const noexcept
{
    return m_pointer != nullptr;
}

template <typename Type>
Type* SharedPtr<Type>::get() const noexcept
{
    return m_pointer;
}

template <typename Type>
bool SharedPtr<Type>::isUnique() const noexcept
{
    return *m_referencesCount == 1;
}

template <typename Type>
std::uint16_t SharedPtr<Type>::getReferencesCount() const noexcept
{
    return *m_referencesCount;
}

template <typename Type>
void SharedPtr<Type>::reset(Type* pointer) noexcept
{
    --(*m_referencesCount);
    if (*m_referencesCount == 0)
    {
        delete m_pointer;
        delete m_referencesCount;
    }

    if (m_pointer)
    {
        m_pointer = pointer;
        m_referencesCount = new std::uint16_t(1);
    }
}

template <typename Type>
SharedPtr<Type>::~SharedPtr()
{
    --(*m_referencesCount);
    if (*m_referencesCount == 0)
    {
        delete m_pointer;
        delete m_referencesCount;
    }
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
        SharedPtr<MyStruct> ptr2(nullptr);
        {
            SharedPtr<MyStruct> ptr1(new MyStruct());
            ptr1->a = 10.5;
            ptr1->b = 5;
            ptr1->c = 'C';

            ptr2 = ptr1;
        }  // End of visibility scope ptr1
        std::cout << "a: " << ptr2->a << " b: " << ptr2->b << " c: " << ptr2->c << std::endl;
    }  // End of visibility scope ptr2

    std::cout << "End of program." << std::endl;
    return EXIT_SUCCESS;
}
