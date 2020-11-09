package us.menges.classiccs.search;

import java.util.*;

import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;

public class Maze implements Searchable<Maze.MazeLocation> {
    private static final Logger logger = LogManager.getLogger(Maze.class);

    static class MazeLocation {
        MazeLocation(int row, int column) {
            this.row = row;
            this.column = column;
        }

        @Override
        public String toString() {
            return "<" + row + ", " + column + ">";
        }

        @Override
        public int hashCode() {
            return Objects.hash(row, column);
        }

        @Override
        public boolean equals(Object obj) {
            if (obj == this)
                return true;

            if (!(obj instanceof MazeLocation))
                return false;

            MazeLocation other = (MazeLocation) obj;
            return this.row == other.row && this.column == other.column;
        }

        final int row;
        final int column;
    }

    private static final char CELL_EMPTY = '_';
    private static final char CELL_START = 'S';
    private static final char CELL_GOAL = 'G';
    private static final char CELL_BLOCKED = 'X';
    private static final char CELL_PATH = '*';

    public Maze(int rows, int columns, float sparseness, MazeLocation start, MazeLocation goal) {
        this.rows = rows;
        this.columns = columns;
        this.sparseness = sparseness;
        this.start = start;
        this.goal = goal;

        logger.debug("Creating Maze");

        grid = new char[rows][columns];

        // Fill the _data with empty cells
        Arrays.stream(grid).forEach(r -> Arrays.fill(r, CELL_EMPTY));

        // Populate the _data with blocked cells
        randomlyFill();

        // Fill the start and goal location
        grid[start.row][start.column] = CELL_START;
        grid[goal.row][goal.column] = CELL_GOAL;
    }

    @Override
    public boolean isGoal(final MazeLocation state) {
        return state.equals(goal);
    }

    @Override
    public List<MazeLocation> getSuccessors(final MazeLocation state) {
        ArrayList<MazeLocation> locations = new ArrayList<>();

        int r = state.row;
        int c = state.column;

        if (r + 1 < rows && grid[r + 1][c] != CELL_BLOCKED) {
            locations.add(new MazeLocation(r + 1, c));
        }

        if (r - 1 >= 0 && grid[r - 1][c] != CELL_BLOCKED) {
            locations.add(new MazeLocation(r - 1, c));
        }

        if (c + 1 < columns && grid[r][c + 1] != CELL_BLOCKED) {
            locations.add(new MazeLocation(r, c + 1));
        }

        if (c - 1 >= 0 && grid[r][c - 1] != CELL_BLOCKED) {
            locations.add(new MazeLocation(r, c - 1));
        }

        logger.debug("Successors: {}", locations);

        return locations;
    }

    public void mark(final List<MazeLocation> path) {
        for (MazeLocation ml : path) {
            grid[ml.row][ml.column] = CELL_PATH;
        }

        grid[start.row][start.column] = CELL_START;
        grid[goal.row][goal.column] = CELL_GOAL;
    }

    public void clear(final List<MazeLocation> path) {
        for (MazeLocation ml : path) {
          grid[ml.row][ml.column] = CELL_EMPTY;
        }

        grid[start.row][start.column] = CELL_START;
        grid[goal.row][goal.column] = CELL_GOAL;
    }

    private void randomlyFill() {
        Random ud = new Random(System.currentTimeMillis());

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                if (ud.nextDouble() < sparseness) {
                    grid[r][c] = CELL_BLOCKED;
                }
            }
        }
    }

    public MazeLocation getStart() { return start; }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++)
                sb.append(grid[r][c]);

            sb.append('\n');
        }

        return sb.toString();
    }

    private final int rows;
    private final int columns;
    private final float sparseness;
    private final MazeLocation start;
    private final MazeLocation goal;
    private final char[][] grid;
}
