#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "dfs.h"
#include "bfs.h"
#include "maze.h"

namespace logging = boost::log;

static void init_logging() {
    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
}

std::unique_ptr<Maze> maze3;

bool Maze_goal_test(const MazeLocation& state)
{
    return maze3->goal_test(state);
}

std::vector<MazeLocation> Maze_successors(const MazeLocation& state)
{
    return maze3->successors(state);
}

int main() {
    init_logging();

    Maze m1{7, 7};
    Maze m2{4, 4, 0.2, MazeLocation{0, 0}, MazeLocation{3, 3}};

    maze3 = std::make_unique<Maze>(4, 4, 0.2, MazeLocation{0, 0}, MazeLocation{3, 3});

    std::cout << "Maze:" << std::endl;
    std::cout << m2.to_string() << std::endl;

    auto solution2 = dfs<MazeLocation>(m2.start(), m2);
    if (solution2.has_value()) {
        auto path = node_to_path<MazeLocation>(solution2);
        m2.mark(path);

        std::cout << "Maze solution:" << std::endl;
        std::cout << m2.to_string() << std::endl;

        m2.clear(path);
    }

//    goal_state_fn<MazeLocation> gfn = [](MazeLocation state) -> bool { return true; };
//    successors_fn<MazeLocation> sfn = [](MazeLocation state) -> std::vector<MazeLocation>{ return std::vector<MazeLocation>{}; };
#if 0
    std::cout << "Maze:" << std::endl;
    std::cout << maze3->to_string() << std::endl;

    auto solution3 = dfs2<MazeLocation>(maze3->start(), Maze_goal_test, Maze_successors);
    if (solution3.has_value()) {
        auto path = node_to_path<MazeLocation>(solution3);
        maze3->mark(path);

        std::cout << "Maze solution:" << std::endl;
        std::cout << maze3->to_string() << std::endl;

        m2.clear(path);
    }
#endif

    std::cout << std::endl << "--------------------------------------------------" << std::endl;
    std::cout << "Maze:" << std::endl;
    std::cout << m2.to_string() << std::endl;

    auto solutionbf2 = bfs<MazeLocation>(m2.start(), m2);
    if (solutionbf2.has_value()) {
        auto path = node_to_path<MazeLocation>(solutionbf2);
        m2.mark(path);

        std::cout << "Maze solution:" << std::endl;
        std::cout << m2.to_string() << std::endl;

        m2.clear(path);
    }


    return 0;
}
