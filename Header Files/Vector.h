#include <iostream>
#include <cstdint>
#include <vector>

#define NODISCARD [[nodiscard]]

namespace mrt
{
    template <typename _Vec>
    class VectorIterator
    {
    public:
        using ValueType = typename _Vec::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;
        using SizeType = typename _Vec::SizeType;

    public:
        VectorIterator(PointerType ptr)
            : m_Ptr(ptr)
        {
        }

        VectorIterator& operator++()
        {
            m_Ptr++;
            return *this;
        }

        VectorIterator operator++(int)
        {
            VectorIterator iterator = *this;
            ++(*this);
            return iterator;
        }

        VectorIterator& operator--()
        {
            m_Ptr--;
            return *this;
        }

        VectorIterator operator--(int)
        {
            VectorIterator iterator = *this;
            --(*this);
            return iterator;
        }

        VectorIterator operator+(int offset) const
        {
            return VectorIterator(m_Ptr + offset);
        }

        VectorIterator operator-(int offset) const
        {
            return VectorIterator(m_Ptr - offset);
        }

        SizeType operator-(const VectorIterator& other) const
        {
            return m_Ptr - other.m_Ptr;
        }

        SizeType operator+(const VectorIterator& other) const
        {
            return m_Ptr + other.m_Ptr;
        }

        ReferenceType operator[](int index)
        {
            return *(m_Ptr + index);
        }

        PointerType operator->()
        {
            return m_Ptr;
        }

        ReferenceType operator*()
        {
            return *m_Ptr;
        }

        bool operator==(const VectorIterator& other) const
        {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const VectorIterator& other) const
        {
            return !(*this == other);
        }

    private:
        PointerType m_Ptr;
    };

    template <typename _Vec>
    class ConstVectorIterator
    {
    public:
        using ValueType = typename _Vec::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;
        using SizeType = typename _Vec::SizeType;

    public:
        ConstVectorIterator(PointerType ptr)
            : m_Ptr(ptr)
        {
        }

        const ConstVectorIterator& operator++()
        {
            m_Ptr++;
            return *this;
        }

        const ConstVectorIterator operator++(int)
        {
            ConstVectorIterator iterator = *this;
            ++(*this);
            return iterator;
        }

        const ConstVectorIterator& operator--()
        {
            m_Ptr--;
            return *this;
        }

        const ConstVectorIterator operator--(int)
        {
            ConstVectorIterator iterator = *this;
            --(*this);
            return iterator;
        }

        const ConstVectorIterator operator+(int offset) const
        {
            return ConstVectorIterator(m_Ptr + offset);
        }

        const ConstVectorIterator operator-(int offset) const
        {
            return ConstVectorIterator(m_Ptr - offset);
        }

        SizeType operator-(const ConstVectorIterator& other) const
        {
            return m_Ptr - other.m_Ptr;
        }

        SizeType operator+(const ConstVectorIterator& other) const
        {
            return m_Ptr + other.m_Ptr;
        }

        const ReferenceType operator[](int index)
        {
            return *(m_Ptr + index);
        }

        const PointerType operator->() const
        {
            return m_Ptr;
        }

        const ReferenceType operator*() const
        {
            return *m_Ptr;
        }

        bool operator==(const ConstVectorIterator& other) const
        {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const ConstVectorIterator& other) const
        {
            return !(*this == other);
        }

    private:
        PointerType m_Ptr;
    };

    template <typename _Type>
    class Vector
    {
    public:
        using ValueType = _Type;
        using SizeType = uint64_t;
        using Iterator = VectorIterator<Vector<_Type>>;
        using ConstIterator = ConstVectorIterator<Vector<_Type>>;

    public:
        Vector()
            : m_Size(0), m_Capacity(20)
        {
            _Type* new_data = (_Type*)::operator new(m_Capacity * sizeof(_Type));

            if (new_data == nullptr)
            {
                throw std::bad_alloc();
            }

            m_Data = new_data;
        }

        Vector(SizeType size)
            : m_Size(0), m_Capacity(size)
        {
            _Type* new_data = (_Type*)::operator new(m_Capacity * sizeof(_Type));

            if (new_data == nullptr)
            {
                throw std::bad_alloc();
            }

            m_Data = new_data;
        }

        Vector(SizeType size, const _Type& value)
            : m_Size(size), m_Capacity(size)
        {
            _Type* new_data = (_Type*)::operator new(m_Capacity * sizeof(_Type));

            if (new_data == nullptr)
            {
                throw std::bad_alloc();
            }

            m_Data = new_data;

            for (SizeType i = 0; i < m_Size; i++)
            {
                m_Data[i] = value;
            }
        }

        Vector(const Vector<_Type>& other)
            : m_Size(other.m_Size), m_Capacity(other.m_Capacity)
        {
            _Type* new_data = (_Type*)::operator new(m_Capacity * sizeof(_Type));

            if (new_data == nullptr)
            {
                throw std::bad_alloc();
            }

            m_Data = new_data;

            for (SizeType i = 0; i < m_Size; i++)
            {
                m_Data[i] = other.m_Data[i];
            }
        }

        Vector(Vector<_Type>&& other) noexcept
            : m_Size(other.m_Size), m_Capacity(other.m_Capacity)
        {
            m_Data = other.m_Data;
            other.m_Data = nullptr;
            other.m_Size = 0;
            other.m_Capacity = 20;
        }

        Vector& operator=(const Vector<_Type>& other)
        {
            if (this != &other)
            {
                Clear();
                Reserve(other.m_Capacity);

                for (SizeType i = 0; i < other.m_Size; i++)
                {
                    m_Data[i] = other.m_Data[i];
                }

                other.m_Data = nullptr;
                other.m_Size = 0;
                other.m_Capacity = 20;
            }

            return *this;
        }

        Vector& operator=(Vector<_Type>&& other) noexcept
        {
            if (this != &other)
            {
                Clear();
                ::operator delete(m_Data, m_Capacity * sizeof(_Type));

                m_Data = other.m_Data;
                m_Size = other.m_Size;
                m_Capacity = other.m_Capacity;

                other.m_Data = nullptr;
                other.m_Size = 0;
                other.m_Capacity = 20;
            }
        }

        bool operator==(const Vector<_Type>& other) const
        {
            if (m_Size != other.m_Size)
            {
                return false;
            }

            for (SizeType i = 0; i < m_Size; i++)
            {
                if (m_Data[i] != other.m_Data[i])
                {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const Vector<_Type>& other) const
        {
            return !(*this == other);
        }

        void PushBack(const _Type& value)
        {
            if (m_Size >= m_Capacity)
            {
                Reserve(m_Capacity * 2);
            }

            m_Data[m_Size++] = value;
        }

        template <typename... _Args>
        _Type& EmplaceBack(_Args... args)
        {
            if (m_Size >= m_Capacity)
            {
                Reserve(m_Capacity * 2);
            }

            new(&m_Data[m_Size]) _Type(std::forward<_Args>(args)...);
            return m_Data[m_Size++];
        }

        void PopBack()
        {
            if (m_Size > 0)
            {
                m_Size--;
                m_Data[m_Size].~_Type();
            }
        }

        void Clear()
        {
            for (SizeType i = 0; i < m_Size; i++)
            {
                m_Data[i].~_Type();
            }

            m_Size = 0;
        }

        void Reserve(SizeType new_capacity)
        {
            if (new_capacity <= m_Capacity)
            {
                return;
            }

            _Type* new_data = (_Type*)::operator new(new_capacity * sizeof(_Type));

            if (new_data == nullptr)
            {
                throw std::bad_alloc();
            }

            for (size_t i = 0; i < m_Size; ++i)
            {
                new (&new_data[i]) _Type(std::move(m_Data[i]));
                m_Data[i].~_Type();
            }

            ::operator delete(m_Data, m_Capacity * sizeof(_Type));

            m_Data = new_data;
            m_Capacity = new_capacity;
        }

        void Erase(SizeType index)
        {
            if (index >= m_Size)
            {
                throw std::out_of_range("Index out of range");
            }

            m_Data[index].~_Type();

            for (SizeType i = index; i < m_Size - 1; i++)
            {
                m_Data[i] = m_Data[i + 1];
            }

            m_Size--;
        }

        void Erase(Iterator position)
        {
            Erase(position - begin());
        }

        void Erase(ConstIterator position)
        {
            Erase(position - cbegin());
        }

        template <typename... _Args>
        void Emplace(Iterator position, _Args... args)
        {
            if (m_Size >= m_Capacity)
            {
                Reserve(m_Capacity * 2);
            }

            for (auto it = end(); it != position; it--)
            {
                *it = *(it - 1);
            }

            new (&*position) _Type(std::forward<_Args>(args)...);
            m_Size++;
        }

        template <typename... _Args>
        void Emplace(ConstIterator position, _Args... args)
        {
            if (m_Size >= m_Capacity)
            {
                Reserve(m_Capacity * 2);
            }

            for (auto it = cend(); it != position; it--)
            {
                *it = *(it - 1);
            }

            new (&*position) _Type(std::forward<_Args>(args)...);
            m_Size++;
        }

        NODISCARD SizeType Size() const
        {
            return m_Size;
        }

        NODISCARD SizeType Capacity() const
        {
            return m_Capacity;
        }

        NODISCARD _Type& At(SizeType index)
        {
            return m_Data[index];
        }

        NODISCARD const _Type& At(SizeType index) const
        {
            return m_Data[index];
        }

        NODISCARD _Type& operator[](SizeType index)
        {
            return m_Data[index];
        }

        NODISCARD const _Type& operator[](SizeType index) const
        {
            return m_Data[index];
        }

        NODISCARD bool Empty() const
        {
            return (m_Size == 0);
        }

        NODISCARD Iterator begin()
        {
            return Iterator(m_Data);
        }

        NODISCARD Iterator end()
        {
            return Iterator(m_Data + m_Size);
        }

        NODISCARD ConstIterator cbegin() const
        {
            return ConstIterator(m_Data);
        }

        NODISCARD ConstIterator cend() const
        {
            return ConstIterator(m_Data + m_Size);
        }

        ~Vector()
        {
            Clear();
            ::operator delete(m_Data, m_Capacity * sizeof(_Type));
        }

    private:
        _Type* m_Data;
        SizeType m_Size;
        SizeType m_Capacity;
    };
}