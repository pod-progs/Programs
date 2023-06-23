#pragma once
#include <vector>
#include <string>

// Below utilities are already provided by standard library. 
// Just writting below for reference with basic implementation
namespace Utils
{
    // Simple implementation of algorithm std::isdigit
    inline bool isDigit(char c)
    {
        return (c >= '0' && c <= '9');
    }

    // Simple implementation of string to interger std::stoi
    // In case of invalid string it returns 0
    inline int stoi(const std::string& str)
    {
        int res = 0;

        for (const auto ch : str) {
            if (isDigit(ch))
                res = res * 10 + ch - '0';
            else
                return 0;
        }

        return res;
    }

    // Implementation of std::is_sorted
    inline bool isSorted(std::vector<std::string>& vec)
    {
        if (vec.size() <= 1)
            return true;
        for (auto i = 1; i < vec.size(); ++i)
        {
            if (vec[i] < vec[i - 1])
                return false;
        }
        return true;
    }

    // Partition function for QuickSort
    inline size_t partition(std::vector<std::string>& arr, size_t low, size_t high) {
        std::string pivot = arr[high];
        size_t i = low - 1;

        for (size_t j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // QuickSort function
    inline void quickSort(std::vector<std::string>& arr, size_t low, size_t high) {
        if (low < high) {
            size_t pi = partition(arr, low, high);

            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    // simple implementation of sorting algorithm std::sort
    inline void sort(std::vector<std::string>& arr) {
        auto n = arr.size();
        quickSort(arr, 0, n - 1);
    }
};
