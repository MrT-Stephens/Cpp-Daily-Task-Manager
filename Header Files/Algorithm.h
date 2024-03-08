namespace mrt
{
    template <typename _Iter>
    _Iter Find(_Iter first, _Iter last, const typename _Iter::ValueType& value)
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

    template <typename _Iter>
    _Iter FindIf(_Iter first, _Iter last, bool (*predicate)(const typename _Iter::ValueType&))
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
    typename _Iter::ValueType Accumulate(_Iter first, _Iter last, typename _Iter::ValueType init)
    {
        for (; first != last; first++)
        {
            init += *first;
        }

        return init;
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
}