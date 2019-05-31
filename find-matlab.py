#!/usr/bin/env python3

import os
import shutil
import sys

x = shutil.which("matlab")

if x is None:
    print("Cannot find MATLAB (search for `matlab` binary in PATH came back empty")
    sys.exit(1)

x = os.path.realpath(x)
x = os.path.dirname(x)
x = os.path.dirname(x)

with open(os.path.join(x, 'VersionInfo.xml')) as f:
    s = f.read()
    if not 'R2019a' in s:
        print("\n!!! Unsupported MATLAB version (could not find R2019a in VersionInfo.xml)\n!!! Continuing anyway, hoping for the best\n", file=sys.stderr)

print(x)
