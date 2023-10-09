#!/usr/bin/env python3

from base64 import b64decode

def main() -> int:
    with open('./NjRfYm90dGxlc19vZl9ib3R0bGVz', 'rb') as f:
        cipher = f.read()
    for _ in range(26):
        cipher = b64decode(cipher)
    print(cipher.decode())
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
