#!/usr/bin/env python3

from collections import defaultdict


freq = defaultdict(int)
with open('./cipher_Me.txt') as f:
    cipher = f.read()
for c in cipher:
    freq[c] += 1
sorted_freqs = sorted(list(freq.items()), key=lambda tup: tup[1], reverse=True)
print(sorted_freqs)

mapping = {
    'c': ' ',
    '$': 'e',
    '&': 'a',
    '8': 'c',
    'l': 'k',
    'U': 'm',
    '^': 'H',
    '!': 'q',
    'n': 'P',
    'V': 'G',
    '|': 'O',
    '5': 'I',
    ']': '"',
    'v': 'n',
    's': 'e',
    ':': 'F',
    '.': 'R',
    'F': 'b',
    'w': 'p',
    'r': 'A',
    '*': 'n',
    'a': 'v',
    'R': 'g',
    '\\': 'f',
    '{': 't',
    'E': 'h',
    '4': 'i',
    '<': 'l',
    '~': 'd',
    'e': '4',
    'S': '-',
    '"': 'S',
    'q': 'z',
    'Y': '@',
    'P': '2',
    'Q': 'C',
    'C': 'L',
    'G': ',',
    'b': 'D',
    'h': "'",
    '[': 'u',
    'k': 'y',
    'W': 'w',
    'L': 'r',
    'u': 'o',
    ',': '.',
    'x': 'T',
    'z': 's',
}


new_cipher = ''
for c in cipher:
    for x, f in mapping.items():
        if c == x:
           new_cipher += '\033[31m' + mapping[c] + '\033[m'
           break
    else:
        new_cipher += c
print(new_cipher)
