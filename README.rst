==========================
 SYCL Language Reference
==========================
 
Prerequisites
=============

Install python3. Sphinx and plugins are python packages and can be
installed with this command::

   pip install -r requirements.txt

Building
========

To build::

  python doc.py html

View the document in your browser starting at: build/html/sycl-index.html

Automatic Publishing
====================

Gitlab CI builds and publishes the doc on commit:
  
.. image:: https://gitlab.com/rscohn2/sycl-ref/badges/sycl/pipeline.svg
    :target: https://gitlab.com/rscohn2/sycl-ref/-/jobs
    :alt: pipeline status
	  
`HTML <https://rscohn2.gitlab.io/sycl-ref/sycl/sycl-index.html>`__

Derived Manuals
===============

If you want to customize the manual for a compiler (e.g. DPC++), but
be able to incorporate updates made to the SYCL doc, then create
another branch (e.g. dpcpp). In the branch copy source/sycl/conf.cpp
to source/dpcpp/conf.cpp and build the doc::

  python doc.py --compiler dpcpp html

If the change is common to SYCL and DPC++, then commit the change to the
sycl branch and merge it into dpcpp branch::

  git checkout dpcpp
  git merge sycl
  # resolve conflicts and commit

Contributors and reviewers may submit a pull request, comment on an
existing merge request, or file an issue to provide input.
