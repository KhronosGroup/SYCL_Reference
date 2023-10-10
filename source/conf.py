# Copyright 2020 The Khronos Group Inc.
# SPDX-License-Identifier: Apache-2.0

import os
import re
import string
import sys
from os.path import join

from docutils import nodes
from docutils.parsers.rst import Directive
from docutils.parsers.rst.directives.body import ParsedLiteral
from sphinx.util import logging

sys.path.append(os.path.abspath("./_ext"))


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

project = "SYCL Reference"
copyright = "2020, The Khronos Group Inc."
author = ""


# -- General configuration ---------------------------------------------------

master_doc = "index"

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "sphinx.ext.todo",
    "sphinxcontrib.spelling",
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = [
    "root/*.rst",
    "*.inc.rst",
    "**/*.inc.rst",
    "iface/math.rst",
    "iface/integer.rst",
    "iface/common.rst",
    "iface/geometric.rst",
    "iface/relational.rst",
    "iface/vector.rst",
    "iface/synchronization.rst",
    "iface/printf.rst",
]

sycl_ref_url = (
    "https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html"
)


def make_ref(ref_str, ref_num, ref_sufix):
    return (
        f".. |{ref_str}| replace:: SYCL Specification "
        f"`Section {ref_num} <{sycl_ref_url}{ref_sufix}>`__"
        f"\n"
    )


prolog_template = string.Template(
    make_ref("SYCL_SPEC_HEADER_FILES", "4.3", "#sec:headers-and-namespaces")
    + make_ref("SYCL_SPEC_DEVICE_SELECTORS", "4.6.1.1", "#sec:device-selector")
    + make_ref("SYCL_SPEC_PLATFORM", "4.6.2", "#sec:platform-class")
    + make_ref("SYCL_SPEC_DEVICE", "4.6.4", "#sec:device-class")
    + make_ref("SYCL_MEMORY_ORDERING", "3.8.3.1", "#_memory_ordering")
    + make_ref("SYCL_MEMORY_SCOPE", "3.8.3.2", "#_memory_scope")
    + f"""
.. _`SYCL Specification`: {sycl_ref_url}
.. |true| replace:: ``true``
.. |false| replace:: ``false``
.. |2020| replace:: *Since SYCL 2020*
.. _oneAPI:  https://oneapi.com
.. _SYCL: https://www.khronos.org/sycl/
.. |SYCL_SPEC| replace:: `SYCL Specification`_
.. |SYCL_SPEC_CONTEXT| replace:: `SYCL Specification`_ Section 4.6.3
.. |SYCL_SPEC_QUEUE| replace:: `SYCL Specification`_ Section 4.6.5
.. |SYCL_SPEC_EVENT| replace:: `SYCL Specification`_ Section 4.6.6
.. |SYCL_SPEC_BUFFER| replace:: `SYCL Specification`_ Section 4.7.2
.. |SYCL_SPEC_IMAGE| replace:: `SYCL Specification`_ Section 4.7.3
.. |SYCL_SPEC_BUFFER_ACCESSOR| replace:: `SYCL Specification`_ Section 4.7.6.9
.. |SYCL_SPEC_LOCAL_ACCESSOR| replace:: `SYCL Specification`_ Section 4.7.6.11
.. |SYCL_SPEC_IMAGE_ACCESSOR| replace:: `SYCL Specification`_ Section 4.7.6.12
.. |SYCL_SPEC_MALLOC_DEVICE| replace:: `SYCL Specification`_ Section 4.8.5.1
.. |SYCL_SPEC_MALLOC_HOST| replace:: `SYCL Specification`_ Section 4.8.5.2
.. |SYCL_SPEC_MALLOC_SHARED| replace:: `SYCL Specification`_ Section 4.8.5.2
.. |SYCL_SPEC_FREE| replace:: `SYCL Specification`_ Section 4.8.5.4
.. |SYCL_SPEC_USM_ALLOCATOR| replace:: `SYCL Specification`_ Section 4.8.4
.. |SYCL_SPEC_USM_ALLOC| replace:: `SYCL Specification`_ Section 4.8.3
.. |SYCL_SPEC_MULTI_PTR| replace:: `SYCL Specification`_ Section 4.7.7.1
.. |SYCL_SPEC_ADDRESS_SPACE| replace:: `SYCL Specification`_ Section 4.7.7
.. |SYCL_SPEC_PRIVATE_MEMORY| replace:: `SYCL Specification`_ Section 4.10.7.3
.. |SYCL_SPEC_SAMPLER| replace:: `SYCL Specification`_ Section 4.7.8
.. |SYCL_SPEC_RANGE| replace:: `SYCL Specification`_ Section 4.10.1.1
.. |SYCL_SPEC_GROUP| replace:: `SYCL Specification`_ Section 4.10.1.7
.. |SYCL_SPEC_ID| replace:: `SYCL Specification`_ Section 4.10.1.3
.. |SYCL_SPEC_ITEM| replace:: `SYCL Specification`_ Section 4.10.1.4
.. |SYCL_SPEC_H_ITEM| replace:: `SYCL Specification`_ Section 4.10.1.6
.. |SYCL_SPEC_ND_ITEM| replace:: `SYCL Specification`_ Section 4.10.1.5
.. |SYCL_SPEC_ND_RANGE| replace:: `SYCL Specification`_ Section 4.10.1.2
.. |SYCL_SPEC_DEVICE_EVENT| replace:: `SYCL Specification`_ Section 4.7.8
.. |SYCL_SPEC_HANDLER| replace:: `SYCL Specification`_ Section 4.10.4
.. |SYCL_SPEC_KERNEL| replace:: `SYCL Specification`_ Section 4.12
.. |SYCL_SPEC_EXCEPTION| replace:: `SYCL Specification`_ Section 4.15.2
"""
)

rst_prolog = prolog_template.substitute({})
primary_domain = "cpp"


# -- Options for spelling extension -------------------------------------------

spelling_show_suggestions = True

# -- Options for todo extension -----------------------------------------------
todo_include_todos = False


# -- Options for HTML output -------------------------------------------------

html_logo = "_static/Khronos_Group_SYCL_logo.svg"
html_favicon = "_static/favicon.png"

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_book_theme"

html_theme_options = {
    "repository_url": "https://github.com/KhronosGroup/SYCL_Reference",
    "path_to_docs": "source",
    "use_issues_button": True,
    "use_edit_page_button": True,
    "repository_branch": "main",
}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]


# -- Options for latex output -------------------------------------------------

latex_logo = "_static/Khronos_Group_SYCL_logo.pdf"

# -- notfound extension ------------------------------------

notfound_default_language = "syclreference"
notfound_default_version = ""

# -- Add some directives for structure------------------------------------


logger = logging.getLogger(__name__)

class_layout_pattern = (
    ":title"
    "(:rubric Template parameters:table)?"
    "(:rubric Example)?"
    "(:rubric Kernel dispatch:table)?"
    "(:rubric Memory operations:table)?"
    "(:rubric Member types:table)?"
    "(:rubric Nonmember data:table)?"
    "(:seealso)?"
    "(:rubric Member and nonmember functions)?"
    "(:rubric Example)?"
    "(:section)*"
)

class_ignore = [
    "definition_list",
    "target",
    "transition",
    "block_quote",
    "todo_node",
    "paragraph",
    "literal_block",
    "system_message",
]
class_layout = re.compile(class_layout_pattern)

class_section_layout_pattern = (
    ":title"
    "(:comment)?"
    "(:rubric Template parameters:table)?"
    "(:rubric Parameters:table)?"
    "(:rubric Parameters:definition_list)?"
    "(:rubric Returns)?"
    "(:rubric Exceptions)?"
    "(:rubric Exceptions:definition_list)?"
    "(:rubric Example)?"
)

class_section_layout = re.compile(class_section_layout_pattern)


def check_class(object_file, section):
    enc = ""
    for n in section:
        name = type(n).__name__
        if name == "title":
            class_name = n[0]
            print("class:", class_name, file=object_file)
        if name in class_ignore:
            continue
        enc += ":" + name
        if name == "rubric":
            enc += " " + n[0]
    if not class_layout.fullmatch(enc):
        logger.warning("Class structure mismatch", location=n)
        logger.warning("  got: %s" % enc)
        logger.warning("  expected: %s" % class_layout_pattern)
    for subsection in section.traverse(nodes.section, include_self=False):
        check_class_section(object_file, class_name, subsection)


def check_class_section(object_file, class_name, section):
    enc = ""
    for n in section:
        name = type(n).__name__
        if name == "title":
            member_name = n[0]
            print("  member:", member_name, file=object_file)
        if name in class_ignore:
            continue
        enc += ":" + name
        if name == "rubric":
            enc += " " + n[0]
    if not class_section_layout.fullmatch(enc):
        logger.warning("Class section structure mismatch", location=n)
        logger.warning("  got: %s" % enc)
        logger.warning("  expected: %s" % class_section_layout_pattern)


def check_doc(app, doctree, docname):
    obj_path = join("build", "objects", "%s.txt" % docname)
    os.makedirs(os.path.dirname(obj_path), exist_ok=True)
    with open(obj_path, "w") as object_file:
        for section in doctree.traverse(nodes.section, descend=True):
            classes = section["classes"]
            if "api-class" in classes:
                check_class(object_file, section)


class TParamsDirective(Directive):
    def run(self):
        return [nodes.rubric(text="Template parameters")]


class ExceptionsDirective(Directive):
    def run(self):
        return [nodes.rubric(text="Exceptions")]


class ParamsDirective(Directive):
    def run(self):
        return [nodes.rubric(text="Parameters")]


class ReturnsDirective(Directive):
    def run(self):
        return [nodes.rubric(text="Return value")]


class MemberFunctionsDirective(Directive):
    def run(self):
        return [nodes.rubric(text="Member functions")]


class MemberTypesDirective(Directive):
    def run(self):
        return [nodes.rubric(text="Member types")]


class NonMemberFunctionsDirective(Directive):
    def run(self):
        return [nodes.rubric(text="Non-member functions")]


class ExampleDirective(Directive):
    def run(self):
        return [nodes.rubric(text="Example")]


def setup(app):
    app.connect("doctree-resolved", check_doc)
    if False:
        app.add_directive("tparams", TParamsDirective)
        app.add_directive("params", ParamsDirective)
        app.add_directive("returns", ReturnsDirective)
        app.add_directive("member-types", MemberTypesDirective)
        app.add_directive("member-functions", MemberFunctionsDirective)
        app.add_directive("non-member-functions", NonMemberFunctionsDirective)
        app.add_directive("example", ExampleDirective)
        app.add_directive("synopsis", ParsedLiteral)
        app.add_directive("exceptions", ExceptionsDirective)
    return {"version": "0.1"}
