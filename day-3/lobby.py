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
    first_idx = 0
    for idx, i in enumerate(bank[1:-1]):
        if i > bank[first_idx]:
            first_idx = idx + 1
    first = bank[first_idx]
    second = max(bank[first_idx + 1 :])
    counter += int(f"{first}{second}")
    rcounter += int(rec(bank, 12))


print(f"Part 1: {counter}")
print(f"Part 2: {rcounter}")
