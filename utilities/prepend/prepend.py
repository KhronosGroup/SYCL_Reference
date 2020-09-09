# Copyright 2020 The Khronos Group Inc.
# SPDX-License-Identifier: Apache-2.0

import argparse

def prepend(prefix_lines, file):
    with open(file, 'r') as fin:
        lines = fin.readlines()
    with open(file, 'w') as fout:
        fout.writelines(prefix_lines + lines)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('prefix')
    parser.add_argument('file')
    args = parser.parse_args()
    with open(args.prefix, 'r') as fin:
        prefix_lines = fin.readlines()
    prepend(prefix_lines, args.file)

main()

