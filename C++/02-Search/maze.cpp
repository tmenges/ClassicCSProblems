//
// Created by A Menges on 10/25/20.
//

#include "maze.h"
#include <random>
#include <boost/log/trivial.hpp>

static std::random_device rd{};
static auto mtgen = std::mt19937{ rd() };

static const char mapCellToChar[] = {
        '_',        // EMPTY
        'X',        // BLOCKED
        'S',        // START
        'G',        // GOAL
        '*'         // PATH
};

std::ostream& operator<<(std::ostream& os, const MazeLocation& ml) {
    os << ml.to_string();
    return os;
}

Maze::Maze(int rows,
           int columns,
           float sparseness,
           MazeLocation start,
           MazeLocation goal)  : _rows(rows), _columns(columns), _sparseness(sparseness), _start(start), _goal(goal) {

    _grid.resize(boost::extents[_rows][_columns]);

    // Fill the _data with empty cells
    std::fill_n(_grid.data(), _grid.num_elements(), Cell::EMPTY);

    // Populate the _data with blocked cells
    randomly_fill(_rows, _columns, _sparseness);

    // Fill the start and goal location
    _grid[_start.row()][_start.column()] = Cell::START;
    _grid[_goal.row()][_goal.column()] = Cell::GOAL;
}

void Maze::randomly_fill(size_t rows, size_t columns, double sparseness) {
    auto ud = std::uniform_real_distribution<>{0.0, 1.0};

    for (auto r = 0; r < rows; r++) {
        for (auto c = 0; c < columns; c++) {
            auto number = ud(mtgen);

            if (number < sparseness)
                _grid[r][c] = Cell::BLOCKED;
        }
    }
}

std::vector<MazeLocation> Maze::successors(MazeLocation ml) const {
    auto locations{std::vector<MazeLocation>()};

    auto r = ml.row();
    auto c = ml.column();

    if (r + 1 < _rows && _grid[r + 1][c] != Cell::BLOCKED) {
        locations.emplace_back(MazeLocation(r + 1, c));
    }

    if (r - 1 >= 0 && _grid[r - 1][c] != Cell::BLOCKED) {
        locations.emplace_back(MazeLocation(r - 1, c));
    }

    if (c + 1 < _columns && _grid[r][c + 1] != Cell::BLOCKED) {
        locations.emplace_back(MazeLocation(r, c + 1));
    }

    if (c - 1 >= 0 && _grid[r][c - 1] != Cell::BLOCKED) {
        locations.emplace_back(MazeLocation(r, c - 1));
    }

    BOOST_LOG_TRIVIAL(debug) << "successors of " << ml << " size: " << locations.size() << std::endl;

    BOOST_LOG_TRIVIAL(debug) << "\tSuccessors: ";
    std::for_each(locations.begin(), locations.end(), [](auto ml) { BOOST_LOG_TRIVIAL(debug) << " " << ml; });
    BOOST_LOG_TRIVIAL(debug) << std::endl;

    return locations;
}

void Maze::mark(const std::vector<MazeLocation>& path) {
    for (auto maze_location : path) {
        _grid[maze_location.row()][maze_location.column()] = Cell::PATH;
    }

    _grid[_start.row()][_start.column()] = Cell::START;
    _grid[_goal.row()][_goal.column()] = Cell::GOAL;
}

void Maze::clear(const std::vector<MazeLocation>& path) {
    for (auto maze_location : path) {
        _grid[maze_location.row()][maze_location.column()] = Cell::EMPTY;
    }

    _grid[_start.row()][_start.column()] = Cell::START;
    _grid[_goal.row()][_goal.column()] = Cell::GOAL;
}

std::string Maze::to_string() const {
    std::stringstream output;

    for (auto r = 0; r < _rows; r++) {
        for (auto c = 0; c < _columns; c++)
            output << mapCellToChar[_grid[r][c]];

        output << "\n";
    }

    return output.str();
}
