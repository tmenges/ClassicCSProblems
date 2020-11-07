//
// Created by A Menges on 10/26/20.
//

#ifndef SEARCH_SEARCH_H
#define SEARCH_SEARCH_H

#include <optional>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <stack>
#include <set>

#include <boost/log/trivial.hpp>

static const auto MAX_STATES_EXPLORED = 50;

template<typename T>
struct  Searchable {
    explicit Searchable() = default;
    virtual ~Searchable() = default;

    virtual bool goal_test(T state) const = 0;
    virtual std::vector<T> successors(T ml) const = 0;
};

template <typename InputIterator, typename T>
bool linear_contains(InputIterator begin, InputIterator end, T key);

template<typename T>
using IsGoalStateFn = bool (*)(T state);

template<typename T>
using SuccessorsFn = std::vector<T> (*)(T state);

template<typename T>
struct Node {
    explicit  Node(T state, std::shared_ptr<Node> parent = nullptr, float cost = 0.0, float heuristic = 0.0) :
                    _state(state), _parent(parent), _cost(cost), _heuristic(heuristic) {}

    Node(const Node& other) : _state(other._state), _parent(other._parent), _cost(other._cost), _heuristic(other._heuristic) {}

    bool operator<(const Node& other) const {
        return _cost + _heuristic < other._cost + other._heuristic;
    }

    [[nodiscard]] std::string to_string() const {
        std::stringstream output;
        output << "[" << _state << ", " << (_parent.has_value() ? _parent.value() : "[]") << ", "
               << _cost << ", " << _heuristic << "]";
        return output.str();
    }

    T _state;
    const std::shared_ptr<Node<T>> _parent;
    const float _cost;
    const float _heuristic;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& n) {
    os << n.to_string();
    return os;
}

template<typename T>
std::vector<T> node_to_path(std::optional<std::shared_ptr<Node<T>>> node) {
    std::vector<T> path{};

    if (node.has_value()) {
        auto n = node.value();

        BOOST_LOG_TRIVIAL(debug) << "Path: " << n;
        BOOST_LOG_TRIVIAL(debug) << n->_state;

        path.push_back(n->_state);

        // work backwards from end to front
        while (n->_parent) {
            n = n->_parent;
            BOOST_LOG_TRIVIAL(debug) << n->_state << std::endl;
            path.push_back(n->_state);
        }

        std::reverse(path.begin(), path.end());
    }

    return path;
}

#endif //SEARCH_SEARCH_H
