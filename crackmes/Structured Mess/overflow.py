#!/usr/bin/env python3

import os


BUFFER_SIZE = 50000
PARAMETER_SIZE = 50000


def main() -> int:
    # os.system(f'cc -DBUFFER_SIZE=\'{BUFFER_SIZE}\' -g3 -o fferbuf fferbuf.c -lm')
    os.execv('./fferbu', ['./fferbu', 'monica', '42ctf{w7f_57RncPY_15_50_uN53CUR3}'*0 + 'a'*PARAMETER_SIZE])

if __name__ == '__main__':
    raise SystemExit(main())
