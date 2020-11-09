package us.menges.classiccs.search;

import java.util.List;
import java.util.Optional;

public class Main {
    public static void main(String[] args) {
        Maze m1 = new MazeBuilder().setRows(4).setColumns(4).createMaze();

        System.out.println("Maze 1:");
        System.out.println(m1);

        Optional<Node<Maze.MazeLocation>> solution = Dfs.depthFirstSearch(m1.getStart(), m1);

        if (solution.isPresent()) {
            List<Maze.MazeLocation> path = solution.get().getPath();
            m1.mark(path);

            System.out.println("Maze solution:");
            System.out.println(m1);

            m1.clear(path);
        }
    }
}
