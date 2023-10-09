#!/usr/bin/env python3

import os


def main() -> int:
    for i in range(64, 0, -1):
        os.system(f'tar xf {i}.tgz')
        os.system(f'rm -f {i}.tgz')
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
