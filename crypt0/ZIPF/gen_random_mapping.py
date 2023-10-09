#!/usr/bin/env python3

import random


def new_ascii_map() -> dict:
    ascii_map = {}
    all_printables = set(map(chr, range(32, 127)))
    for c in map(chr, range(32, 127)):
        ascii_map[c] = random.choice(list(all_printables))
        all_printables.remove(ascii_map[c])
    return ascii_map

def main() -> int:
    with open('./cleartext.txt') as f:
        clear = f.read()
    cipher = ''
    ascii_map = new_ascii_map()
    for c in clear:
        if c in ascii_map:
            cipher += ascii_map[c]
        else:
            cipher += c
    print(cipher)
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
