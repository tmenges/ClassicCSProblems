from typing import List, Optional

from generic_search import Node, bfs, node_to_path

MAX_NUM: int = 3


class MCState:
    def __init__(self, missionaries: int, cannibals: int, boat: bool) -> None:
        self.wm: int = missionaries  # missionaries on west bank
        self.wc: int = cannibals  # cannibals on west bank
        self.em: int = MAX_NUM - self.wm  # missionaries on east bank
        self.ec: int = MAX_NUM - self.wc  # cannibals on east bank
        self.boat: bool = boat

    def __str__(self) -> str:
        return ("On the west bank there are {} missionaries and {} cannibals.\n"
                "On the east bank there are {} missionaries and {} cannibals.\n"
                "The boat is on the {} bank.") \
            .format(self.wm, self.wc, self.em, self.ec, "west" if self.boat else "east")

    def goal_test(self) -> bool:
        return self.is_legal and self.em == MAX_NUM and self.ec == MAX_NUM

    @property
    def is_legal(self) -> bool:
        if self.wc > self.wm > 0:
            return False
        if self.ec > self.em > 0:
            return False
        return True

    def successors(self):
        sucs: List[MCState] = []
        if self.boat:
            if self.wm > 1:
                sucs.append(MCState(self.wm - 2, self.wc, not self.boat))
            if self.wm > 0:
                sucs.append(MCState(self.wm - 1, self.wc, not self.boat))
            if self.wc > 1:
                sucs.append(MCState(self.wm, self.wc - 2, not self.boat))
            if self.wc > 0:
                sucs.append(MCState(self.wm, self.wc - 1, not self.boat))
            if (self.wc > 0) and (self.wm > 0):
                sucs.append(MCState(self.wm - 1, self.wc - 1, not self.boat))
        else:
            if self.em > 1:
                sucs.append(MCState(self.wm + 2, self.wc, not self.boat))
            if self.em > 0:
                sucs.append(MCState(self.wm + 1, self.wc, not self.boat))
            if self.ec > 1:
                sucs.append(MCState(self.wm, self.wc + 2, not self.boat))
            if self.ec > 0:
                sucs.append(MCState(self.wm, self.wc + 1, not self.boat))
            if (self.ec > 0) and (self.em > 0):
                sucs.append(MCState(self.wm + 1, self.wc + 1, not self.boat))

        return [x for x in sucs if x.is_legal]


def display_solution(path: List[MCState]):
    if len(path) == 0:
        return

    old_state: MCState = path[0]
    print(old_state)

    for current_state in path[1:]:
        if current_state.boat:
            print("{} missionaries and {} cannibals move from east bank to west bank.\n"
                  .format(old_state.em - current_state.em, old_state.ec - current_state.ec))
        else:
            print("{} missionaries and {} cannibals move from west bank to east bank.\n"
                  .format(old_state.wm - current_state.wm, old_state.wc - current_state.wc))
        old_state = current_state


if __name__ == "__main__":
    start: MCState = MCState(MAX_NUM, MAX_NUM, True)
    solution: Optional[Node[MCState]] = bfs(start, MCState.goal_test, MCState.successors)
    if solution is None:
        print("No solution found.")
    else:
        solution_path: List[MCState] = node_to_path(solution)
        display_solution(solution_path)

        i = 0
        for state in solution_path:
            print("[{}]:\n{}\n".format(i, str(state)))
            i += 1
