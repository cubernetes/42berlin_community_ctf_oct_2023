#!/usr/bin/env python3

from base64 import b64encode

def main() -> int:
    flag = '42ctf{inception_ininception_inininception}'
    cipher = flag.encode()
    for _ in range(26):
        cipher = b64encode(cipher)
    print(cipher.decode())
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
