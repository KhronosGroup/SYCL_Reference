..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

.. image:: https://readthedocs.org/projects/sycl/badge/?version=latest
	   :target: https://sycl.readthedocs.io/en/latest/?badge=latest
           :alt: Documentation Status

==========================
 SYCL Language Reference
==========================
 
The document is a work in progress. It may be missing descriptions or
entire classes. If you see something wrong, file an issue or submit a
PR to fix it.

Prerequisites
=============

The document is built with `Sphinx
<https://www.sphinx-doc.org/en/master>`__ and plugins. To install all
required software on Ubuntu::

   apt-get update -qq
   DEBIAN_FRONTEND=noninteractive xargs -a packages.txt apt-get install -qq
   pip3 install --upgrade --quiet -r requirements.txt
   
 Testing github integration

Building
========

To build::

  python doc.py html

To see the document, open build/html/index.html

Automatic Publishing
====================

Commits to main branch are built and published at `ReadTheDocs
<https://sycl.readthedocs.io>`__
  
