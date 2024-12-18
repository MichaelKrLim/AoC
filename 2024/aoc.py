#!/usr/bin/python3
import argparse
import subprocess
import sys
import requests
from datetime import datetime

# Usage: ./get_input.py > 1.in
# # You must fill in SESSION following the instructions below.
# # DO NOT run this in a loop, just once.
#
# # You can find SESSION by using Chrome tools:
# # 1) Go to https://adventofcode.com/2022/day/1/input
# # 2) right-click -> inspect -> click the "Application" tab.
# # 3) Refresh
# # 5) Click https://adventofcode.com under "Cookies"
# # 6) Grab the value for session. Fill it in.
SESSION = '53616c7465645f5f0c4dd15096896a507735e3ff9a5257bf4874c7e39cdf8733b621b88266da2e7b8f00c1e432b6a3a92074d579dd241b11dfc3a2d55f78a972'

useragent = 'https://github.com/jonathanpaulson/AdventOfCode/blob/master/get_input.py by jonathanpaulson@gmail.com'
parser = argparse.ArgumentParser(description='Read input')
parser.add_argument('--year', type=int, default=datetime.today().year)
parser.add_argument('--day', type=int, default=datetime.today().day)
args = parser.parse_args()

cmd = f'curl https://adventofcode.com/{args.year}/day/{args.day}/input --cookie "session={SESSION}" -A \'{useragent}\''
output = subprocess.check_output(cmd, shell=True)
output = output.decode('utf-8')
print(output, end='')
print('\n'.join(output.split('\n')[:10]), file=sys.stderr)
