/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/11 00:22
*******************************************************************************/


#ifndef MSTL_SORT_HPP
#define MSTL_SORT_HPP

namespace MSTL {
template <typename RandomIt, typename Compare>
void BubbleSort(RandomIt first, RandomIt last, Compare comp) {
    for (auto it = first; it != last; ++it) {
        for (auto inner_it = first; inner_it != last - 1; ++inner_it) {
            if (comp(*(inner_it + 1), *inner_it)) {
                std::iter_swap(inner_it, inner_it + 1);
            }
        }
    }
}

template <typename RandomIt, typename Compare>
void SelectionSort(RandomIt first, RandomIt last, Compare comp) {
    for (auto it = first; it != last - 1; ++it) {
        auto min_it = std::min_element(it, last, comp);
        std::iter_swap(it, min_it);
    }
}

template <typename RandomIt, typename Compare>
void InsertionSort(RandomIt first, RandomIt last, Compare comp) {
    for (auto it = first + 1; it != last; ++it) {
        auto key = *it;
        auto j = it - 1;

        while (j >= first && comp(key, *j)) {
            *(j + 1) = *j;
            --j;
        }

        *(j + 1) = key;
    }
}

template <typename RandomIt, typename Compare>
void QuickSort(RandomIt first, RandomIt last, Compare comp) {
    if (first < last) {
        auto pivot = *std::next(first, std::distance(first, last) / 2);
        auto middle1 = std::partition(first, last, [=](const auto& element) {
            return comp(element, pivot);
        });
        auto middle2 = std::partition(middle1, last, [=](const auto& element) {
            return !comp(pivot, element);
        });

        QuickSort(first, middle1, comp);
        QuickSort(middle2, last, comp);
    }
}
template <typename RandomIt, typename Compare>
static void merge(RandomIt first, RandomIt middle, RandomIt last, Compare comp) {
    std::vector<typename RandomIt::value_type> buffer;
    buffer.reserve(std::distance(first, last));

    auto left = first;
    auto right = middle;

    while (left != middle && right != last) {
        if (comp(*left, *right)) {
            buffer.push_back(std::move(*left));
            ++left;
        } else {
            buffer.push_back(std::move(*right));
            ++right;
        }
    }

    buffer.insert(buffer.end(), std::make_move_iterator(left), std::make_move_iterator(middle));
    buffer.insert(buffer.end(), std::make_move_iterator(right), std::make_move_iterator(last));

    std::move(buffer.begin(), buffer.end(), first);
}

template <typename RandomIt, typename Compare>
void MergeSort(RandomIt first, RandomIt last, Compare comp) {
    auto size = std::distance(first, last);
    if (size < 2) {
        return;
    }

    auto middle = std::next(first, size / 2);
    MergeSort(first, middle, comp);
    MergeSort(middle, last, comp);
    merge(first, middle, last, comp);
}

}   // MSTL


#endif  // MSTL_Sort_H_
