==========================
 DPC++ Language Reference
==========================
 
The language reference documents the classes of DPC++ and their
interfaces. It is not intended to be a tututorial or read
cover-to-cover. Instead, you might find it useful if you are writing a
program and want to look up the member functions of a class or the
parameters of member function. It contains code examples to
demonstrate the common usages. It is HTML and pdf. The search feature
of the HTML manual makes it handy to look up specific names.

The document is a work in progress. It may be missing descriptions or
entire classes.

Relationship to SYCL
====================

DPC++ is SYCL + Intel Extensions. This repo contains a sycl branch
which documents the SYCL standard. The dpcpp branch is the DPC++
language reference. Unless a feature is DPC++-specific, we first
document it in the sycl branch, and then merge it into the dpcpp
branch::

  git checkout dpcpp
  git merge sycl

Resolve conflicts and commit.

Prerequisites
=============

The document is built with `Sphinx
<https://www.sphinx-doc.org/en/master>`__ and plugins. To install all
required software on Ubuntu::

   apt-get update -qq
   DEBIAN_FRONTEND=noninteractive xargs -a packages.txt apt-get install -qq
   pip3 install --upgrade --quiet -r requirements.txt

Building
========

To build::

  python doc.py html

To see the document, open build/html/dpcpp-index.html (or
build/html/sycl-index.html) in your browser.

Automatic Publishing
====================

Github CI builds and publishes the doc on commit using Github pages:
  
`HTML <https://oneapi-src.github.io/dpcpp-ref/index.html>`__

If you are working in a fork, you must change the above URL to point
to your Github pages root directory.

Documenting a Compiler Implementation
=====================================

If you want to customize the manual for a compiler (e.g. DPC++), but
be able to incorporate updates made to the SYCL doc, then create
another branch (e.g. dpcpp). In the branch copy source/sycl/conf.cpp
to source/dpcpp/conf.cpp and build the doc::

  python doc.py --compiler dpcpp html
