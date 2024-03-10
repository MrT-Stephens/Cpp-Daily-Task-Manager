#define NODISCARD [[nodiscard]]

namespace mrt
{
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

    template <typename _Iter>
    void ForEach(_Iter first, _Iter last, void (*func)(typename _Iter::ValueType&))
    {
        for (; first != last; first++)
        {
            func(*first);
        }
    }

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