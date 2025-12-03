# BRUTE FORCE

ranges = []

with open("input.txt") as f:
    input = f.read()
    ranges = input.split(",")


counter = 0
rcounter = 0
patterns: list[str] = []
for r in ranges:
    lo, hi = r.split("-")
    for i in range(int(lo), int(hi) + 1):
        s = str(i)
        middle = len(s) // 2

        # Part 1
        if len(s) % 2 == 0:
            if s[:middle] == s[middle:]:
                counter += i

        # Part 2
        for j in range(1, middle + 1):
            if len(s) % j == 0:
                pattern = s[:j]
                repeating = True
                for k in range(j, len(s), j):
                    if pattern != s[k : k + j]:
                        repeating = False
                        break
                if repeating:
                    patterns.append(s)
                    rcounter += i
                    break


print(f"Answer Part 1: {counter}")
print(f"Answer Part 2: {rcounter}")
