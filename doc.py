# Copyright 2020 The Khronos Group Inc.
# SPDX-License-Identifier: Apache-2.0

import argparse
import os
import os.path
import shutil
import subprocess
from functools import wraps
from os.path import join

sphinx_opts = '-W -n -N -j auto'
sphinx_build = 'sphinx-build'
source_dir = 'source'
build_dir = 'build'

indent = 0


def action(func):
    @wraps(func)
    def wrapped(*args, **kwargs):
        global indent
        log('%s:' % (wrapped.__name__))
        indent += 2
        x = func(*args, **kwargs)
        indent -= 2
        return x

    return wrapped


class cd:
    """Context manager for changing the current working directory"""

    def __init__(self, newPath):
        self.newPath = os.path.expanduser(newPath)

    def __enter__(self):
        self.savedPath = os.getcwd()
        log('cd ' + self.newPath)
        os.chdir(self.newPath)

    def __exit__(self, etype, value, traceback):
        os.chdir(self.savedPath)


def log(*args, **kwargs):
    print(indent * ' ' + ' '.join(map(str, args)), flush=True, **kwargs)


def shell(c):
    log(c)
    if args.dry_run:
        return
    subprocess.check_call(c, shell=True)


def rm(dir):
    log('rm -rf', dir)
    if args.dry_run:
        return
    shutil.rmtree(dir, ignore_errors=True)


def copytree(src, dst):
    log('cp -r', src, dst)
    if args.dry_run:
        return
    shutil.copytree(src, dst)


def copy(src, dst):
    log('cp', src, dst)
    if args.dry_run:
        return
    shutil.copy(src, dst)


def makedirs(path):
    if os.path.exists(path):
        return
    log('mkdir -p', path)
    if args.dry_run:
        return
    os.makedirs(path)


def sphinx(target):
    if not args.verbose:
        os.environ['LATEXMKOPTS'] = '--silent'
        os.environ['LATEXOPTS'] = '-interaction=nonstopmode -halt-on-error'
    opts = (
        sphinx_opts
        + (' -q' if not args.verbose else '')
        + (' -W' if args.W else '')
        + (' -a' if args.all else '')
    )
    shell(
        '%s -M %s %s %s %s'
        % (sphinx_build, target, source_dir, build_dir, opts)
    )


def up_to_date(target, deps):
    if not os.path.exists(target):
        return False
    for dep in deps:
        if os.path.getmtime(target) < os.path.getmtime(dep):
            print('time')
            return False
    return True


@action
def examples(target=None):
    run_examples = [
        'host-task',
        'gpu-platform',
        'std-vector',
        'event-elapsed-time',
        'get-platforms',
        'get_devices',
        'stream',
        'gpu-selector',
    ]
    compiler = 'dpcpp'
    compiler_options = '-Wall -Werror'
    build = join('build', 'examples')
    makedirs(build)

    for run_example in run_examples:
        bin = join(build, run_example)
        sources = ['%s.cpp' % join('source', 'examples', run_example)]
        output = join(build, '%s.out' % run_example)
        if not up_to_date(output, sources):
            shell(
                '%s %s -o %s %s'
                % (compiler, compiler_options, bin, ' '.join(sources))
            )
            try:
                shell('%s > %s' % (bin, output))
            except Exception:
                log('Failed')


@action
def build(target):
    sphinx(target)


@action
def site(target=None):
    rm('site')
    copytree(join('build', 'html'), 'site')
    copy(join('build', 'latex', '%sreference.pdf' % args.compiler), 'site')
    copy(join('build', 'spelling', 'output.txt'), 'site')


@action
def ci(target=None):
    build('html')
    build('spelling')
    build('latexpdf')
    site()


commands = {
    'ci': ci,
    'clean': build,
    'examples': examples,
    'html': build,
    'latexpdf': build,
    'pseudoxml': build,
    'site': site,
    'spelling': build,
}


def main():
    global args
    parser = argparse.ArgumentParser(description='Build doc.')
    parser.add_argument('action', choices=commands.keys())
    parser.add_argument('--compiler', default='sycl')
    parser.add_argument('--dry-run', action='store_true')
    parser.add_argument('-W', action='store_true')
    parser.add_argument('--verbose', action='store_true')
    parser.add_argument('--all', action='store_true', help='rebuild all files')
    args = parser.parse_args()

    commands[args.action](args.action)


main()
