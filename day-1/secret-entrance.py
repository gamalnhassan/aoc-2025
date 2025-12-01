import fileinput
from math import floor

pointer = 50
count = 0
rcount = 0
for line in fileinput.input():
    offset = int(line[1:])
    dir = line[0]
    prev = pointer
    if dir == "L":
        pointer = pointer - offset
    else:
        pointer = pointer + offset

    crossed = (pointer < 0) != (prev < 0)
    rotations = floor(abs(pointer) / 100)
    if (crossed and prev != 0) or pointer == 0:
        rotations += 1
    pointer %= 100
    if pointer == 0:
        count += 1  # Part 1
    rcount += rotations  # Part 2

    # get prev distance to 0 if rotating left
    # dl = prev
    # if dir == "L" and offset >= dl:
    #    # we rotate past or onto 0 at least once
    #    rcount += floor((offset - dl) / 100)
    #    if prev != 0:
    #        rcount += 1
    # get prev distance to 0 if rotating righ
    # dr = 100 - prev
    # if dir == "R" and offset >= dr:
    #    # we rotate past or onto 0 at least once
    #    rcount += floor((offset - dr) / 100)
    #    if prev != 0:
    #        rcount += 1


print(f"Password: {count}")
print(f"Actual Password: {rcount}")
