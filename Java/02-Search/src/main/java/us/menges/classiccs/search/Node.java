package us.menges.classiccs.search;


import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Node<T> {
    private static final Logger logger = LogManager.getLogger(Node.class);

    public Node(T state) {
        this(state,null, 0.0f, 0.0f);
    }

    public Node(T state, Node<T> parent) {
        this(state, parent, 0.0f, 0.0f);
    }

    public Node(T state, Node<T> node, float cost, float heuristic) {
        this.state = state;
        this.parent = node;
        this.cost = cost;
        this.heuristic = heuristic;
    }

    public T getState() {
        return state;
    }

    public float getCost() {
        return cost;
    }

    public float getHeuristic() {
        return heuristic;
    }

    public List<T> getPath() {
        List<T> path = new ArrayList<>();

        path.add(this.state);

        // work backwards from end to front
        Node<T> n = this;
        while (n.parent != null) {
            n = n.parent;
            path.add(n.state);
        }

        Collections.reverse(path);

        logger.debug("State: {} path: {}", state, path);
        return path;

    }

    private final Node<T> parent;
    private final T state;
    private final float cost;
    private final float heuristic;
}
