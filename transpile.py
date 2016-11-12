#!/usr/bin/env python3
import json
import sys

with open(sys.argv[1]) as f:
    markov_dict = json.load(f)
for first, first_dict in markov_dict.items():
    for second, second_dict in first_dict.items():
        for third, count in second_dict.items():
            print(first, second, third, count)
