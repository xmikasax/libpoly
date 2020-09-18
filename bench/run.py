#!/usr/bin/env python3

import os
import re
import subprocess

with open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "data.txt"), "r") as f:
    data = f.read()

segments = re.findall(r"# ([a-z0-9 ]+)\nsys := \[([a-z0-9+\-*^, \n]+)", data)

print("Name|Time (seconds)")
print(":-:|:-:")

cnt = 0
for name, data in segments:
    data = data.replace('\n', '').replace(' ', '')
    polynomials = data.split(',')
    for i in range(len(polynomials)):
        if polynomials[i][0] != '-':
            polynomials[i] = '+' + polynomials[i]
    polynomials = list(map(lambda x : x.replace('+', ' +').replace('-', ' -')[1:].split(' '), polynomials))
    test_data = f"{len(polynomials)}\n"
    for polynomial in polynomials:
        test_data += f"{len(polynomial)}\n"
        for term in polynomial:
            sign = term[0]
            left = term[1:]
            test_data += f"{sign} "
            if left[0] != 'x':
                coefficient = left.split('*')[0]
                left = left.split('*')[1:]
            else:
                coefficient = 1
                left = left.split('*')
            test_data += f"{coefficient} {len(left)}\n"
            for variable in left:
                if variable.find('^') == -1:
                    variable_index = variable[1:]
                    power = 1
                else:
                    variable_index = variable.split('^')[0][1:]
                    power = variable.split('^')[1]
                test_data += f"{variable_index} {power}\n"

    program = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "build", "bench")

    process = subprocess.Popen(
        [program],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )

    outs, errs = process.communicate(input=test_data.encode())
    print(f"{name}|{outs.decode().strip()}")
