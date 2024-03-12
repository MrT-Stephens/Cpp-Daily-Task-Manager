#define NODISCARD [[nodiscard]]

namespace mrt
{
    /// <summary>
    /// Find the first occurrence of a value in a range.
    /// </summary>
    /// <typeparam name="_Iter"> Iterator type. </typeparam>
    /// <param name="first"> Iterator to the first element of the range. </param>
    /// <param name="last"> Iterator to the last element of the range. </param>
    /// <param name="value"> Value to find. </param>
    /// <returns> Iterator to the first occurrence of the value. </returns>
    template <typename _Iter>
    NODISCARD _Iter Find(_Iter first, _Iter last, const typename _Iter::ValueType& value)
    {
        for (; first != last; first++)
        {
            if (*first == value)
            {
                return first;
            }
        }

        return last;
    }

    /// <summary>
    /// Find the first occurrence of a value in a range. Using a lambda function to compare.
    /// </summary>
    /// <typeparam name="_Iter"> Iterator type. </typeparam>
    /// <typeparam name="_Predicate"> Predicate type. </typeparam>
    /// <param name="first"> Iterator to the first element of the range. </param>
    /// <param name="last"> Iterator to the last element of the range. </param>
    /// <param name="predicate"> Lambda function to compare. </param>
    /// <returns> Iterator to the first occurrence of the value. </returns>
    template <typename _Iter, typename _Predicate>
    NODISCARD _Iter FindIf(_Iter first, _Iter last, _Predicate predicate)
    {
        for (; first != last; first++)
        {
            if (predicate(*first))
            {
                return first;
            }
        }

        return last;
    }

    /// <summary>
    /// Loop through a range and execute a function for each element.
    /// </summary>
    /// <typeparam name="_Iter"> Iterator type. </typeparam>
    /// <param name="first"> Iterator to the first element of the range. </param>
    /// <param name="last"> Iterator to the last element of the range. </param>
    /// <param name="func"> Function to execute. </param>
    template <typename _Iter>
    void ForEach(_Iter first, _Iter last, void (*func)(typename _Iter::ValueType&))
    {
        for (; first != last; first++)
        {
            func(*first);
        }
    }

    /// <summary>
    /// Sorts a range using a lambda function to compare.
    /// </summary>
    /// <typeparam name="_Iter"> Iterator type. </typeparam>
    /// <param name="first"> Iterator to the first element of the range. </param>
    /// <param name="last"> Iterator to the last element of the range. </param>
    /// <param name="compare"> Lambda function to compare. </param>
    template <typename _Iter>
    void Sort(_Iter first, _Iter last, bool (*compare)(const typename _Iter::ValueType&, const typename _Iter::ValueType&)
        = [](const typename _Iter::ValueType& a, const typename _Iter::ValueType& b)
        {
            return a < b;
        }
    ) {
        for (auto it = first; it != last; it++)
        {
            for (auto it2 = first; it2 != last; it2++)
            {
                if (compare(*it, *it2))
                {
                    std::swap(*it, *it2);
                }
            }
        }
    }

    /// <summary>
    /// Reworks a range to remove all elements that satisfy a predicate. 
    /// All elements that satisfy the predicate are moved to the end of the range.
    /// A new iterator to the end of the range is returned.
    /// </summary>
    /// <typeparam name="_Iter"> Iterator type. </typeparam>
    /// <param name="first"> Iterator to the first element of the range. </param>
    /// <param name="last"> Iterator to the last element of the range. </param>
    /// <param name="predicate"> Lambda function to compare. </param>
    /// <returns> Iterator to the end of the range. </returns>
    template <typename _Iter>
    NODISCARD _Iter RemoveIf(_Iter first, _Iter last, bool (*predicate)(const typename _Iter::ValueType&))
    {
        _Iter result = first;

        for (; first != last; ++first)
        {
            if (!predicate(*first))
            {
                if (result != first)
                {
                    *result = std::move(*first);
                }

                ++result;
            }
        }

        return result;
    }
}