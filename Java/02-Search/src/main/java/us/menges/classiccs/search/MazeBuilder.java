package us.menges.classiccs.search;

public class MazeBuilder {
    private int rows = 7;
    private int columns = 7;
    private float sparseness = 0.2f;
    private Maze.MazeLocation start = new Maze.MazeLocation(0, 0);
    private Maze.MazeLocation goal;

    public MazeBuilder setRows(int rows) {
        this.rows = rows;
        return this;
    }

    public MazeBuilder setColumns(int columns) {
        this.columns = columns;
        return this;
    }

    public MazeBuilder setSparseness(float sparseness) {
        this.sparseness = sparseness;
        return this;
    }

    public MazeBuilder setStart(Maze.MazeLocation start) {
        this.start = start;
        return this;
    }

    public MazeBuilder setGoal(Maze.MazeLocation goal) {
        this.goal = goal;
        return this;
    }

    public Maze createMaze() {
        if (goal == null) {
            goal = new Maze.MazeLocation(rows - 1, columns - 1);
        }
        return new Maze(rows, columns, sparseness, start, goal);
    }
}