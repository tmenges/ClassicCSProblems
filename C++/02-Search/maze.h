//
// Created by A Menges on 10/25/20.
//

#ifndef SEARCH_MAZE_H
#define SEARCH_MAZE_H

#include <string>
#include <functional>
#include <boost/multi_array.hpp>

#include "search.h"

enum Cell : std::int8_t {
    EMPTY,
    BLOCKED,
    START,
    GOAL,
    PATH,
};

class MazeLocation {
public:
    explicit MazeLocation(int row, int column) : _row(row), _column(column) {}

    MazeLocation(const MazeLocation& other)  : _row(other._row), _column(other._column) {}

    MazeLocation& operator=(const MazeLocation& other) {
        if (this != &other) {
            this->_row = other._row;
            this->_column = other._column;
        }

        return *this;
    }

    [[nodiscard]] auto tie() const { return std::tie(_row, _column); }
    bool operator==(const MazeLocation& other) const { return tie() == other.tie(); }
    bool operator!=(const MazeLocation& other) const { return tie() != other.tie(); }
    bool operator< (const MazeLocation& other) const { return _row < other._row || _column <other._column; }

    [[nodiscard]] std::string to_string() const {
        std::stringstream output;
        output << "<" << _row << ", " << _column << ">";
        return output.str();
    }

    [[nodiscard]] auto row() const { return _row; }
    [[nodiscard]] auto column() const { return _column; }

private:
    int _row;
    int _column;
};

std::ostream& operator<<(std::ostream& os, const MazeLocation& ml);

typedef boost::multi_array<Cell, 2> grid_type;

class Maze : public Searchable<MazeLocation> {
public:
    explicit Maze(int rows,
                  int columns,
                  float sparseness = 0.2,
                  MazeLocation start = MazeLocation(0, 0),
                  MazeLocation goal = MazeLocation(6, 6));

    [[nodiscard]] bool goal_test(MazeLocation ml) const override { return ml == _goal; }
    [[nodiscard]] std::vector<MazeLocation> successors(MazeLocation ml) const override;

    void mark(const std::vector<MazeLocation>& path);
    void clear(const std::vector<MazeLocation>& path);

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] MazeLocation start() const { return _start; }
    [[nodiscard]] MazeLocation goal() const { return _goal; }
private:
    void randomly_fill(size_t rows, size_t columns, double sparseness);

    const int _rows;
    const int _columns;
    const float _sparseness;
    const MazeLocation _start;
    const MazeLocation _goal;
    grid_type _grid;
};

#endif //SEARCH_MAZE_H
