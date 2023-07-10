/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/11 00:22
*******************************************************************************/


#ifndef MSTL_Sort_H_
#define MSTL_Sort_H_

namespace MSTL {
template <typename RandomIt, typename Compare>
void bubble_sort(RandomIt first, RandomIt last, Compare comp) {
    for (auto it = first; it != last; ++it) {
        for (auto inner_it = first; inner_it != last - 1; ++inner_it) {
            if (comp(*(inner_it + 1), *inner_it)) {
                std::iter_swap(inner_it, inner_it + 1);
            }
        }
    }
}
}


#endif  // MSTL_Sort_H_
