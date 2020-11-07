//
// Created by A Menges on 11/4/20.
//

#ifndef SEARCH_BFS_H
#define SEARCH_BFS_H

#include <deque>

#include "search.h"

template<typename T>
std::optional<std::shared_ptr<Node<T>>> bfs(T initial, Searchable<T> const &search_space) {

    // frontier is where we've yet to go
    std::deque<std::shared_ptr<Node<T>>> frontier{};
    frontier.push_back(std::make_shared<Node<T>>(Node<T>{initial}));

    // explored is where we've been
    std::set<T> explored{};
    explored.insert(initial);

    std::deque<std::shared_ptr<Node<T>>> path{};

    auto states_explored = 0;
    while (!frontier.empty()) {
        auto current_node = frontier.front();
        auto current_state = current_node->_state;
        frontier.pop_front();

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

            frontier.push_back(std::make_shared<Node<T>>(Node<T>{child, current_node}));
            path.push_back(std::make_shared<Node<T>>(Node<T>{child, current_node}));
        }

        BOOST_LOG_TRIVIAL(debug) << "\tFrontier size: " << frontier.size() << std::endl;
        BOOST_LOG_TRIVIAL(debug) << "\tPath size: " << path.size() << std::endl;
    }

    BOOST_LOG_TRIVIAL(debug) << "No path found" << std::endl;
    return {};
}

#endif //SEARCH_BFS_H
