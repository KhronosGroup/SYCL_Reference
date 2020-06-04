import string

# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'DPC++ Reference'
copyright = '2020, Intel'
author = 'Intel'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
#    'notfound.extension',
    'sphinx_rtd_theme',
    'sphinx.ext.todo',
    'sphinxcontrib.spelling',
]

html_context = {
    'display_github': True,
    'github_user': 'rscohn2',
    'github_repo': 'syclreference',
    'github_version': 'master/source/'
}

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['root/*.rst',
                    '*.inc.rst',
                    '**/*.inc.rst'
]


prolog_template = string.Template("""
.. |true| replace:: ``true``
.. |false| replace:: ``false``
.. _oneAPI:  https://oneapi.com
.. _SYCL: https://www.khronos.org/sycl/
.. _SYCL Specification: https://www.khronos.org/registry/SYCL/specs/sycl-1.2.1.pdf
.. _DPC++ book: https://www.apress.com/gp/book/9781484255735>
.. _oneAPI online training: https://software.seek.intel.com/learn-parallel-programming-dpc-essentials
.. _oneAPI Specification:  https://spec.oneapi.com
""")

rst_prolog = prolog_template.substitute({})

primary_domain = 'cpp'



# -- Options for todo extension -------------------------------------------------
todo_include_todos = True


# -- Options for HTML output -------------------------------------------------

html_favicon = '_static/favicon.png'

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'
html_theme_options = {
    # 'fixed_sidebar': True,
    # 'page_width': 'max-width'
}

html_context = {
    'display_github': True,
    'github_user': 'rscohn2',
    'github_repo': 'syclreference',
    'github_version': 'master/source/'
}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']


# -- notfound extension ------------------------------------

notfound_default_language = 'syclreference'
notfound_default_version = ''

# -- Add some directives for structure------------------------------------

from docutils.parsers.rst import Directive
from docutils.parsers.rst.directives.body import ParsedLiteral
from docutils import nodes

class TParamsDirective(Directive):

    def run(self):
        return [nodes.rubric(text='Template parameters')]
    
class ExceptionsDirective(Directive):

    def run(self):
        return [nodes.rubric(text='Exceptions')]
    
class ParamsDirective(Directive):

    def run(self):
        return [nodes.rubric(text='Parameters')]
    
class ReturnsDirective(Directive):

    def run(self):
        return [nodes.rubric(text='Return value')]
    
class MemberFunctionsDirective(Directive):

    def run(self):
        return [nodes.rubric(text='Member functions')]

class MemberTypesDirective(Directive):

    def run(self):
        return [nodes.rubric(text='Member types')]
    
class NonMemberFunctionsDirective(Directive):

    def run(self):
        return [nodes.rubric(text='Non-member functions')]
    
class ExampleDirective(Directive):

    def run(self):
        return [nodes.rubric(text='Example')]
    
def setup(app):
    if False:
        app.add_directive('tparams', TParamsDirective)
        app.add_directive('params', ParamsDirective)
        app.add_directive('returns', ReturnsDirective)
        app.add_directive('member-types', MemberTypesDirective)
        app.add_directive('member-functions', MemberFunctionsDirective)
        app.add_directive('non-member-functions', NonMemberFunctionsDirective)
        app.add_directive('example', ExampleDirective)
        app.add_directive('synopsis', ParsedLiteral)
        app.add_directive('exceptions', ExceptionsDirective)
    return {'version': '0.1'}
