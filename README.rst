..
  Copyright 2020 The Khronos Group Inc.
  SPDX-License-Identifier: CC-BY-4.0

==========================
 SYCL Language Reference
==========================

.. image:: https://github.com/KhronosGroup/SYCL_Reference/actions/workflows/checks.yml/badge.svg
   :target: https://github.com/KhronosGroup/SYCL_Reference/actions/workflows/checks.yml

This document is incomplete and inconsistent in the current state, as
work is ongoing to update it.  Please do not use as a reference or
propose bug fixes at the moment, since the content is being updated
and is known to be in an inconsistent state. See `SYCL specification`_
for reference documentation for SYCL.

Resolving Errors When Submitting a PR
=====================================

The ``checks`` job in GitHub Actions runs some static tests with the
``pre-commit`` python package. You can resolve issues faster by
running the checks locally before submitting the PR.

Run pre-commit checks::

  pre-commit run --all

Do pre-commit testing as part of ``git commit``::

  pre-commit install

To do a commit without running checks::

  git commit -n -m 'Commit message'

To skip a single test, e.g. sphinx::

  SKIP=sphinx pre-commit run --all

``pre-commit`` will automatically fix most issues. After
``pre-commit`` finds and fixes issues, do a ``git add`` to add the
changes and run ``pre-commit`` or ``git commit`` again. You must
manually fix spelling errors, broken links, and long lines.

To resolve spelling errors, you can manually run the spell checker::

  make spelling

Unrecognized words ``spelling_wordlist.txt``. If the spell checker is
warning about code, it means you have not properly delimited the code
in the rst. Do not add it to ``spelling_wordlist.txt`` add, back
quotes or other delimeters so it will be ignored.

.. _`SYCL specification`: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
