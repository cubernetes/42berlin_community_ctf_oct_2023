#!/usr/bin/env python3

import re
from itertools import permutations


orig_bytes = '''
​﻿‌​
​﻿​‍
‌‍​﻿
‌﻿‌​
‌‍‌‍
‌﻿‍﻿
‌‍﻿‍
​﻿​﻿
‌﻿‌‍
​﻿​﻿
‌﻿​‍
‌‌﻿﻿
‌﻿‌​
‌﻿​‍
‌﻿‌‌
​﻿‌‌
‌﻿‌​
‌‌﻿﻿
‌﻿​​
‌‍﻿​
​﻿‌​
​﻿​‌
‌‍﻿‍
‌‌﻿﻿
‌﻿‌​
​﻿​﻿
‌﻿‍​
‌﻿‌​
‌﻿﻿‌
'''.strip().replace('\n', '')

from_ = [
    '\u200d',
    '\u200c',
    '\ufeff',
    '\u200b',
]

to = [
    '00',
    '01',
    '10',
    '11',
]

for perm in permutations(from_):
    bytes = orig_bytes
    for i, byte in enumerate(perm):
        bytes = bytes.replace(byte, to[i])

    ftuples = list(map(re.Match.group, re.finditer('.{8}', bytes)))
    for tup in ftuples:
        print(end=chr(int(tup, 2)))
    print()
