//
// Created by A Menges on 11/3/20.
//

#ifndef SEARCH_DFS_H
#define SEARCH_DFS_H

#include "search.h"

template<typename T>
std::optional<std::shared_ptr<Node<T>>> dfs(T initial, Searchable<T> const &search_space) {

    // frontier is where we've yet to go
    std::stack<std::shared_ptr<Node<T>>> frontier{};
    frontier.push(std::make_shared<Node<T>>(Node<T>{initial}));

    // explored is where we've been
    std::set<T> explored{};
    explored.insert(initial);

    auto states_explored = 0;
    while (!frontier.empty()) {
        auto current_node = frontier.top();
        auto current_state = current_node->_state;
        frontier.pop();

        BOOST_LOG_TRIVIAL(debug) << "Current state: " << current_state << std::endl;

        states_explored++;

        // if we found the goal, we're done
        if (search_space.goal_test(current_state)) {
            BOOST_LOG_TRIVIAL(debug) << "Found Goal (explored " << states_explored << ")" << std::endl;
            return current_node;
        }

        if (states_explored == MAX_STATES_EXPLORED) {
            BOOST_LOG_TRIVIAL(debug) << "Maximum number of states to explore exceeded" << std::endl;
            return {};
        }

        // check where we can go next and haven't explored
        for (auto child : search_space.successors(current_state)) {
            if (std::find(explored.begin(), explored.end(), child) != explored.end()) {
                continue;
            }
            BOOST_LOG_TRIVIAL(debug) << "\tUnexplored child: " << child << std::endl;

            explored.insert(child);

            BOOST_LOG_TRIVIAL(debug) << "\tExplored: ";
            std::for_each(explored.begin(), explored.end(),
                          [](auto state) { BOOST_LOG_TRIVIAL(debug) << " " << state; });
            BOOST_LOG_TRIVIAL(debug) << std::endl;

            frontier.push(std::make_shared<Node<T>>(Node<T>{child, current_node}));
        }

        BOOST_LOG_TRIVIAL(debug) << "\tFrontier size: " << frontier.size() << std::endl;
    }

    BOOST_LOG_TRIVIAL(debug) << "No path found" << std::endl;
    return {};
}

template<typename T>
using goal_state_fn = bool (*)(const T&);

template<typename T>
using successors_fn = std::vector<T> (*)(const T&);

template<typename T>
std::optional<std::shared_ptr<Node<T>>> dfs2(T initial, goal_state_fn<T> is_goal,successors_fn<T> successors) {

    // frontier is where we've yet to go
    std::stack<std::shared_ptr<Node<T>>> frontier{};
    frontier.push(std::make_shared<Node<T>>(Node<T>{initial}));

    // explored is where we've been
    std::set<T> explored{};
    explored.insert(initial);

    auto states_explored = 0;
    while (!frontier.empty()) {
        auto current_node = frontier.top();
        auto current_state = current_node->_state;
        frontier.pop();

        BOOST_LOG_TRIVIAL(debug) << "Current state: " << current_state << std::endl;

        states_explored++;

        // if we found the goal, we're done
        if (is_goal(current_state)) {
            BOOST_LOG_TRIVIAL(debug) << "Found Goal (explored " << states_explored << ")" << std::endl;
            return current_node;
        }

        if (states_explored == MAX_STATES_EXPLORED) {
            BOOST_LOG_TRIVIAL(debug) << "Maximum number of states to explore exceeded" << std::endl;
            return {};
        }

        // check where we can go next and haven't explored
        for (auto child : successors(current_state)) {
            if (std::find(explored.begin(), explored.end(), child) != explored.end()) {
                continue;
            }
            BOOST_LOG_TRIVIAL(debug) << "\tUnexplored child: " << child << std::endl;

            explored.insert(child);

            BOOST_LOG_TRIVIAL(debug) << "\tExplored: ";
            std::for_each(explored.begin(), explored.end(),
                          [](auto state) { BOOST_LOG_TRIVIAL(debug) << " " << state; });
            BOOST_LOG_TRIVIAL(debug) << std::endl;

            frontier.push(std::make_shared<Node<T>>(Node<T>{child, current_node}));
        }

        BOOST_LOG_TRIVIAL(debug) << "\tFrontier size: " << frontier.size() << std::endl;
    }

    BOOST_LOG_TRIVIAL(debug) << "No path found" << std::endl;
    return {};
}
#endif //SEARCH_DFS_H
