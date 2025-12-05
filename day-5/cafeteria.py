import fileinput


ranges: list[tuple[int, int]] = []
ingredients: list[int] = []

for line in fileinput.input():
    r = line.rstrip("\r\n").split("-")
    if len(r) == 2:
        ranges.append((int(r[0]), int(r[1])))
    elif len(r) == 1:
        if r[0] == "":
            continue
        ingredients.append(int(r[0]))
    else:
        print(f"Unexpected input: {line}")
        exit(1)


ranges = sorted(ranges, key=lambda x: x[0])
# coalesce ranges
coalesced: list[tuple[int, int]] = [ranges[0]]
for r in ranges[1:]:
    (lo, hi) = r
    (prev_lo, prev_hi) = coalesced[-1]
    if lo <= prev_hi and hi > prev_hi:
        coalesced[-1] = (prev_lo, hi)
    elif lo > prev_hi:
        coalesced.append(r)


valid: list[int] = []

for id in ingredients:
    for lo, hi in coalesced:
        if lo > id:
            break
        if hi >= id:
            valid.append(id)
            break


print(f"Part 1: {len(valid)}")
print(f"Part 2: {sum([hi - lo + 1 for (lo, hi) in coalesced])}")
