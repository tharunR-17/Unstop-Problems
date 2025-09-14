def remove_duplicates_and_reverse(s):
    result = []
    seen = set()
    for c in reversed(s):
        if c not in seen:
            result.append(c)
            seen.add(c)
    return ''.join(result)


def apply_operations(s):
    current = s
    while True:
        seen = set()
        has_duplicates = False
        for c in current:
            if c in seen:
                has_duplicates = True
                break
            seen.add(c)
        if has_duplicates:
            current = remove_duplicates_and_reverse(current)
        else:
            break
    return current


def main():
    import sys
    input = sys.stdin.read
    s = input().strip()
    result = apply_operations(s)
    print(result)


if __name__ == "__main__":
    main()
