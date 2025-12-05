import fileinput
import time

ts = time.time()


def rec(bank: list[int], rem: int, acc: int = 0) -> int:
    if rem - 1 == 0:
        return acc * 10 + max(bank)
    d = max(bank[: -(rem - 1)])
    idx = bank.index(d)
    return rec(bank[idx + 1 :], rem - 1, (acc * 10) + d)


counter = 0
rcounter = 0
for line in fileinput.input():
    bank = [int(c) for c in line if c.isdigit()]
    counter += rec(bank, 2)
    rcounter += rec(bank, 12)


print(f"Part 1: {counter}")
print(f"Part 2: {rcounter}")
print(f"Time taken: {time.time() - ts}")
