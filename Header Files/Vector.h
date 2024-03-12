#pragma once

#include <cstdint>

#define NODISCARD [[nodiscard]]

namespace mrt
{
    /// <summary>
    /// VectorIterator class
    /// Used to iterate through the vector like the standard library iterators
    /// </summary>
    /// <typeparam name="_Vec"> Vector type. </typeparam>
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

    /// <summary>
    /// ConstVectorIterator class
    /// Used to iterate through the vector like the standard library iterators
    /// </summary>
    /// <typeparam name="_Vec"> Vector type. </typeparam>
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

    /// <summary>
    /// Vector class
    /// A simple vector implementation
    /// It is not a complete implementation of the standard library vector
    /// But implements most of the functionality
    /// </summary>
    /// <typeparam name="_Type"> Vector type. </typeparam>
    template <typename _Type>
    class Vector
    {
    public:
        using ValueType = _Type;
        using SizeType = uint64_t;
        using Iterator = VectorIterator<Vector<_Type>>;
        using ConstIterator = ConstVectorIterator<Vector<_Type>>;

    public:
        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// Allocates memory for 20 elements
        /// </summary>
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

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// Allocates memory for the specified number of elements
        /// </summary>
        /// <param name="size"> The size to allocate for. </param>
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

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// Allocates memory for the specified number of elements and initializes them with the specified value
        /// </summary>
        /// <param name="size"> The size to allocate for. </param>
        /// <param name="value"> The value to initialize the elements with. </param>
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

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// Initializes the vector with the elements of the specified vector
        /// </summary>
        /// <param name="other"> The vector to initialize with. </param>
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
                new(&m_Data[i]) _Type(other.m_Data[i]);
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// Initializes the vector with the elements of the specified vector
        /// Uses move semantics to initialize the vector
        /// </summary>
        /// <param name="other"> The vector to initialize with. </param>
        Vector(Vector<_Type>&& other) noexcept
            : m_Size(other.m_Size), m_Capacity(other.m_Capacity)
        {
            m_Data = other.m_Data;
            other.m_Data = nullptr;
            other.m_Size = 0;
            other.m_Capacity = 20;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// Initializes the vector with the elements of the specified vector
        /// Uses the assignment operator to initialize the vector
        /// </summary>
        /// <param name="other"> The vector to initialize with. </param>
        /// <returns> The initialized vector. </returns>
        Vector& operator=(const Vector<_Type>& other)
        {
            if (this != &other)
            {
                Clear();
                Reserve(other.m_Capacity);

                for (SizeType i = 0; i < other.m_Size; i++)
                {
                    new(&m_Data[i]) _Type(other.m_Data[i]);
                }

                other.m_Data = nullptr;
                other.m_Size = 0;
                other.m_Capacity = 20;
            }

            return *this;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// Initializes the vector with the elements of the specified vector
        /// Uses move semantics and the assignment operator to initialize the vector
        /// </summary>
        /// <param name="other"> The vector to initialize with. </param>
        /// <returns> The initialized vector. </returns>
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

        /// <summary>
        /// Checks if the vector is equal to the specified vector
        /// </summary>
        /// <param name="other"> The vector to compare with. </param>
        /// <returns> True if the vectors are equal, false otherwise. </returns>
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

        /// <summary>
        /// Checks if the vector is not equal to the specified vector
        /// </summary>
        /// <param name="other"> The vector to compare with. </param>
        /// <returns> True if the vectors are not equal, false otherwise. </returns>
        bool operator!=(const Vector<_Type>& other) const
        {
            return !(*this == other);
        }

        /// <summary>
        /// Adds the specified value to the end of the vector
        /// </summary>
        /// <param name="value"> The value to add. </param>
        void PushBack(const _Type& value)
        {
            if (m_Size >= m_Capacity)
            {
                Reserve(m_Capacity * 2);
            }

            new (&m_Data[m_Size++]) _Type(value);
        }

        /// <summary>
        /// Adds the specified value to the end of the vector
        /// Uses move semantics to add the value
        /// It will construct the value in place
        /// </summary>
        /// <typeparam name="_Args"> The argument types to initalise the value with. </typeparam>
        /// <param name="args"> The arguments to initalise the value with. </param>
        /// <returns> The added value. </returns>
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

        /// <summary>
        /// Removes the last element from the vector
        /// </summary>
        void PopBack()
        {
            if (m_Size > 0)
            {
                m_Size--;
                m_Data[m_Size].~_Type();
            }
        }

        /// <summary>
        /// Clears the vector, by calling the destructor of each element
        /// </summary>
        void Clear()
        {
            for (SizeType i = 0; i < m_Size; i++)
            {
                m_Data[i].~_Type();
            }

            m_Size = 0;
        }

        /// <summary>
        /// Resizes the vector to the specified size
        /// </summary>
        /// <param name="new_capacity"> The new size of the vector. </param>
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

        /// <summary>
        /// Removes the element at the specified index
        /// Will then shift all the elements after the index to the left
        /// </summary>
        /// <param name="index"></param>
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

        /// <summary>
        /// Removes the element at the specified iterator
        /// Will then shift all the elements after the iterator to the left
        /// </summary>
        /// <param name="position"> The iterator to remove. </param>
        void Erase(Iterator position)
        {
            Erase(position - begin());
        }

        /// <summary>
        /// Removes the element at the specified const iterator
        /// Will then shift all the elements after the const iterator to the left
        /// </summary>
        /// <param name="position"> The const iterator to remove. </param>
        void Erase(ConstIterator position)
        {
            Erase(position - cbegin());
        }

        /// <summary>
        /// Removes the elements in the range of the specified iterators
        /// Will then shift all the elements after the iterators to the left
        /// </summary>
        /// <param name="first"> The first iterator of the range. </param>
        /// <param name="last"> The last iterator of the range. </param>
        void Erase(Iterator first, Iterator last)
		{
			SizeType count = last - first;

			for (SizeType i = 0; i < count; i++)
			{
				Erase(first);
			}
		}

        /// <summary>
        /// Removes the elements in the range of the specified const iterators
        /// Will then shift all the elements after the const iterators to the left
        /// </summary>
        /// <param name="first"> The first const iterator of the range. </param>
        /// <param name="last"> The last const iterator of the range. </param>
        void Erase(ConstIterator first, ConstIterator last)
		{
            SizeType count = last - first;

            for (SizeType i = 0; i < count; i++)
            {
                Erase(first);
            }
        }

        /// <summary>
        /// Returns the element at the back of the vector
        /// </summary>
        /// <returns> The element at the back of the vector. </returns>
        NODISCARD _Type& Back()
        {
			return m_Data[m_Size - 1];
		}

        /// <summary>
        /// Returns the element at the back of the vector
        /// This is a const version of the function
        /// </summary>
        /// <returns> The element at the back of the vector. </returns>
        NODISCARD const _Type& Back() const
		{
            return m_Data[m_Size - 1];
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

        /// <summary>
        /// Emplaces the specified arguments at the specified position
        /// Will then shift all the elements after the position to the right
        /// Will then construct the value in place
        /// </summary>
        /// <typeparam name="_Args"> The argument types to initalise the value with. </typeparam>
        /// <param name="position"> The position to emplace the value at. </param>
        /// <param name="args"> The arguments to initalise the value with. </param>
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

        /// <summary>
        /// Returns the size of the vector
        /// </summary>
        /// <returns> The size of the vector. </returns>
        NODISCARD SizeType Size() const
        {
            return m_Size;
        }

        /// <summary>
        /// Returns the capacity of the vector
        /// </summary>
        /// <returns> The capacity of the vector. </returns>
        NODISCARD SizeType Capacity() const
        {
            return m_Capacity;
        }

        /// <summary>
        /// Returns the element at the specified index
        /// </summary>
        /// <param name="index"> The index of the element. </param>
        /// <returns> The element at the specified index. </returns>
        NODISCARD _Type& At(SizeType index)
        {
            return m_Data[index];
        }

        /// <summary>
        /// Returns the element at the specified index
        /// This is a const version of the function
        /// </summary>
        /// <param name="index"> The index of the element. </param>
        /// <returns> The element at the specified index. </returns>
        NODISCARD const _Type& At(SizeType index) const
        {
            return m_Data[index];
        }

        /// <summary>
        /// Returns the element at the specified index
        /// Uses the subscript operator to return the element
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        NODISCARD _Type& operator[](SizeType index)
        {
            return m_Data[index];
        }

        /// <summary>
        /// Returns the element at the specified index
        /// Uses the subscript operator to return the element
        /// This is a const version of the function
        /// </summary>
        /// <param name="index"> The index of the element. </param>
        /// <returns> The element at the specified index. </returns>
        NODISCARD const _Type& operator[](SizeType index) const
        {
            return m_Data[index];
        }

        /// <summary>
        /// Checks if the vector is empty
        /// </summary>
        /// <returns> True if the vector is empty, false otherwise. </returns>
        NODISCARD bool Empty() const
        {
            return (m_Size == 0);
        }

        /// <summary>
        /// The begin iterator of the vector
        /// </summary>
        /// <returns> The begin iterator of the vector. </returns>
        NODISCARD Iterator begin()
        {
            return Iterator(m_Data);
        }

        /// <summary>
        /// The end iterator of the vector
        /// </summary>
        /// <returns> The end iterator of the vector. </returns>
        NODISCARD Iterator end()
        {
            return Iterator(m_Data + m_Size);
        }

        /// <summary>
        /// The begin iterator of the vector
        /// This is a const version of the function
        /// </summary>
        /// <returns> The begin iterator of the vector. </returns>
        NODISCARD Iterator begin() const
        {
            return Iterator(m_Data);
        }

        /// <summary>
        /// The end iterator of the vector
        /// This is a const version of the function
        /// </summary>
        /// <returns> The end iterator of the vector. </returns>
        NODISCARD Iterator end() const
        {
            return Iterator(m_Data + m_Size);
        }

        /// <summary>
        /// The const begin iterator of the vector
        /// </summary>
        /// <returns> The const begin iterator of the vector. </returns>
        NODISCARD ConstIterator cbegin()
        {
            return ConstIterator(m_Data);
        }

        /// <summary>
        /// The const end iterator of the vector
        /// </summary>
        /// <returns> The const end iterator of the vector. </returns>
        NODISCARD ConstIterator cend()
        {
            return ConstIterator(m_Data + m_Size);
        }

        /// <summary>
        /// The const begin iterator of the vector
        /// This is a const version of the function
        /// </summary>
        /// <returns> The const begin iterator of the vector. </returns>
        NODISCARD ConstIterator cbegin() const
        {
            return ConstIterator(m_Data);
        }

        /// <summary>
        /// The const end iterator of the vector
        /// This is a const version of the function
        /// </summary>
        /// <returns> The const end iterator of the vector. </returns>
        NODISCARD ConstIterator cend() const
        {
            return ConstIterator(m_Data + m_Size);
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="Vector"/> class.
        /// Calls the clear function to clear the vector
        /// Then deallocates the allocated memory
        /// </summary>
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