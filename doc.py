import argparse
from functools import wraps
import glob
import os
import os.path
from os.path import join
import os.path
import shutil
import subprocess

sphinx_opts    = '-n -N -j auto'
sphinx_build   = 'sphinx-build'
source_dir     = 'source'
build_dir      = 'build'
doxygen_xml    = join(build_dir, 'doxygen', 'xml', 'index.xml')
doxyfile       = join('source', 'Doxyfile')

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
    print(indent * ' ' + ' '.join(map(str,args)), flush = True, **kwargs)
    
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
    os.environ['LATEXMKOPTS'] = '--silent'
    os.environ['LATEXOPTS'] = '-interaction=nonstopmode -halt-on-error'
    opts = (sphinx_opts
            + (' -c %s' % join('source', args.compiler))
            + (' -q' if not args.verbose else '')
            + (' -W' if args.W else '')
            + (' -a' if args.all else ''))
    shell('%s -M %s %s %s %s' % (sphinx_build,
                                 target,
                                 source_dir,
                                 build_dir,
                                 opts))

def up_to_date(target, deps):
    if not os.path.exists(target):
        return False
    for dep in deps:
        if os.path.getmtime(target) < os.path.getmtime(dep):
            print('time')
            return False
    return True

def doxygen_files():
    makedirs('build')
    return [doxyfile] + glob.glob(join('source','headers','**'), recursive=True)

def doxygen(target=None):
    if (not os.path.exists(doxyfile) or
        up_to_date(doxygen_xml, doxygen_files())):
        return
    shell('DOXYGEN_QUIET=%s doxygen %s' % ('NO' if args.verbose else 'YES', doxyfile))

@action
def examples(target=None):
    run_examples = ['vector-add',
                    'fall-back',
                    'kernel-model',
                    'memory-model',
                    'nd-range',
                    'get-platforms',
                    'gpu-selector',
                    'execution-model']
    compiler = 'dpcpp'
    compiler_options = '-Wall -Werror'
    build = join('build', 'examples')
    source = join('source', 'examples')
    makedirs(build)

    for run_example in run_examples:
        bin = join(build, run_example)
        sources = ['%s.cpp' % join('source', 'examples', run_example)]
        output = join(source, '%s.out' % run_example)
        if not up_to_date(output, sources):
            shell('%s %s -o %s %s' % (compiler, compiler_options, bin, ' '.join(sources)))
            try:
                shell('%s > %s' % (bin, output))
            except:
                log('Failed')

@action
def prep(target=None):
#    examples()
#    doxygen()
    pass

@action
def build(target):
    if target != 'clean':
        prep()
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

commands = {'ci': ci,
            'clean': build,
            'examples': examples,
            'html': build,
            'latexpdf': build,
            'prep': prep,
            'pseudoxml': build,
            'site': site,
            'spelling': build
}

def main():
    global args
    parser = argparse.ArgumentParser(description='Build doc.')
    parser.add_argument('action',choices=commands.keys())
    parser.add_argument('--compiler', default='sycl')
    parser.add_argument('--dry-run', action='store_true')
    parser.add_argument('-W', action='store_true')
    parser.add_argument('--verbose', action='store_true')
    parser.add_argument('--all', action='store_true', help='rebuild all files')
    args = parser.parse_args()

    commands[args.action](args.action)

main()
