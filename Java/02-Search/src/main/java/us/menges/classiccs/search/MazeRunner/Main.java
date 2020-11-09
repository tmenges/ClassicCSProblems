package us.menges.classiccs.search.MazeRunner;

import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;
import us.menges.classiccs.search.Maze;
import us.menges.classiccs.search.MazeBuilder;

public class Main {
    private static final Logger logger = LogManager.getLogger(Main.class);

    public static void main(String[] args) {
        logger.info("Maze starting up.");

        Maze m1 = new MazeBuilder().setRows(4).setColumns(4).createMaze();

        System.out.println("Maze 1:");
        System.out.println(m1);
    }
}
