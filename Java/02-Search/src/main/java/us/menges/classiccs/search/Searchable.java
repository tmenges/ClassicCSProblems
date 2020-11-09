package us.menges.classiccs.search;

import java.util.List;

public interface Searchable<T> {
    boolean isGoal(final T currentState);
    List<T> getSuccessors(final T currentState);
}
