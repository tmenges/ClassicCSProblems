from collections import deque

towers = [
    deque(),
    deque(),
    deque()
]

tower_indexes = {0, 1, 2}


def move_disk(src, dest):
    d = towers[src].pop()
    print("MOVING {} from {} to {}".format(d, src, dest))
    towers[dest].append(d)


def move_2_disks(start, end):
    intermediate = (tower_indexes - {start, end}).pop()
    move_disk(start, intermediate)
    move_disk(start, end)
    move_disk(intermediate, end)


def move_disks(n, start, end):
    intermediate = (tower_indexes - {start, end}).pop()
    if n == 1:
        move_disk(start, end)
    elif n == 2:
        move_2_disks(start, end)
    else:
        move_disks(n - 1, start, intermediate)
        move_disk(start, end)
        move_disks(n - 1, intermediate, end)


def initialize_towers(n):
    for i in range(n, 0, -1):
        towers[0].append("Disk-{}".format(i))
        towers[1] = deque()
        towers[2] = deque()


if __name__ == "__main__":
    print("3 disks")
    initialize_towers(3)
    print("Towers: {}".format(towers))
    move_disks(len(towers[0]), 0, 2)
    print("Towers: {}".format(towers))

    print("4 disks")
    initialize_towers(4)
    print("Towers: {}".format(towers))
    move_disks(len(towers[0]), 0, 2)
    print("Towers: {}".format(towers))
