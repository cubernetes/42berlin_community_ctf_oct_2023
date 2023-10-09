#!/usr/bin/env python3

import os


def main() -> int:
    first_file_name = 'NjRfYm90dGxlc19vZl9ib3R0bGVz'
    os.system(f'tar czf 1.tgz {first_file_name}')
    for i in range(1, 64):
        os.system(f'tar czf {i+1}.tgz {i}.tgz')
        os.system(f'rm -f {i}.tgz')
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
