import fileinput


def rec(bank: list[int], rem: int) -> str:
    if rem - 1 == 0:
        return str(max(bank))
    d = max(bank[: -(rem - 1)])
    idx = bank.index(d)
    return str(d) + rec(bank[idx + 1 :], rem - 1)


counter = 0
rcounter = 0
for line in fileinput.input():
    bank = [int(c) for c in line if c.isdigit()]
    counter += int(rec(bank, 2))
    rcounter += int(rec(bank, 12))


print(f"Part 1: {counter}")
print(f"Part 2: {rcounter}")
