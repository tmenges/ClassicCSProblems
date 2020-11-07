//
// Created by A Menges on 10/26/20.
//
#include <algorithm>
#include <iostream>
#include <stack>
#include <set>

#include "search.h"

template <typename InputIterator, typename T>
bool linear_contains(InputIterator begin, InputIterator end, T key) {
    auto it = std::find_if(begin(), end(), [key](T elem){ return key == elem; });

    return it == end();
}
