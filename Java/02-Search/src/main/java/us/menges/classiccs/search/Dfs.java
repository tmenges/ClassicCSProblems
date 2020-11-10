package us.menges.classiccs.search;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.*;
import java.util.function.Function;
import java.util.function.Predicate;

public class Dfs {
    private static final Logger logger = LogManager.getLogger(Dfs.class);
    private static final int MAX_STATES_EXPLORED = 20;

    public static <T> Optional<Node<T>> depthFirstSearch(T initial, final Searchable<T> searchSpace) {

        return depthFirstSearch(initial, searchSpace::isGoal, searchSpace::getSuccessors);
    }

    public static <T> Optional<Node<T>> depthFirstSearch(T initial, Predicate<T> isGoal, Function<T, List<T>> successors) {

        // frontier is where we've yet to go
        Deque<Node<T>> frontier = new ArrayDeque<>();
        frontier.push(new Node<>(initial));

        // explored is where we've been
        Set<T> explored = new HashSet<>();
        explored.add(initial);

        int statesExplored = 0;
        while (frontier.size() > 0) {
            Node<T> currentNode = frontier.pop();
            T currentState = currentNode.getState();

            logger.debug("Current state: {}", currentState);

            statesExplored++;

            // if we found the goal, we're done
            if (isGoal.test(currentState)) {
                System.out.printf("Found goal. Explored %d states.\n", statesExplored);
                return Optional.of(currentNode);
            }

            if (statesExplored == MAX_STATES_EXPLORED) {
                System.out.printf("Maximum number of states to explore exceeded. Explored: %d states.\n", statesExplored);
                return Optional.empty();
            }

            // check where we can go next and haven't explored
            for (T child : successors.apply(currentState)) {
                logger.debug("Child: {}", child);
                if (explored.contains(child)) {
                    logger.debug("Child: {} has already been explored.", child);
                    continue;
                }
                logger.debug("Unexplored child: {}", child);

                explored.add(child);

                logger.debug("Explored: {}", explored);

                frontier.push(new Node<>(child, currentNode));
            }

            logger.debug("Frontier size: {}", frontier.size());
        }

        System.out.printf("No path to the goal was found. Explored: %d states.\n", statesExplored);
        return Optional.empty();
    }
}
