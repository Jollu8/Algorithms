///// @Jollu
// Liner Searching sorted Element

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>




#include <vector>
#include <iostream>

template<typename T>
using ValType = typename T::value_type;

template<typename T>
using SizeType = typename T::size_type;

template<typename T>
int linear_search_non_recursive(const T& collection, const ValType<T>& value) noexcept
{
    for (SizeType<T> i = 0; i < collection.size(); ++i)
    {
        if (collection[i] == value)
        {
            return i;
        }
    }

    return -1;
}

template<typename T>
int linear_search_recursive(const T& collection, const ValType<T>& value, SizeType<T> index) noexcept
{
    if (collection.size() == index)
    {
        return -1;
    }
    else if (collection[index] == value)
    {
        return index;
    }
    else
    {
        return linear_search_recursive(collection, value, index + 1);
    }
}

int main() {
    const std::vector<int> vector = {1,2,3,4,5,6,6,4,4,3,73,3,43,43,};
    std::cout << "Index: " << linear_search_recursive(vector, 73, 0u) << std::endl;
    std::cout << "Index: " << linear_search_non_recursive(vector, 72) << std::endl;

}