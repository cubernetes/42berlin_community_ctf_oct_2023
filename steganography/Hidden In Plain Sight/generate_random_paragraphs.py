#!/usr/bin/env python3

import random

def main() -> int:
    for _ in range(3000):
        paragraph = ''
        for _ in range(20):
            paragraph += chr(random.randint(97, 97+26))
        print(f'<p>{paragraph}</p>')
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
