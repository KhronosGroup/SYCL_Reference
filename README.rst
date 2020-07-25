==========================
 SYCL Language Reference
==========================
 
Prerequisites
=============

Ubuntu::

   apt-get update -qq
   DEBIAN_FRONTEND=noninteractive xargs -a packages.txt apt-get install -qq
   pip3 install --upgrade --quiet -r requirements.txt

Building
========

To build::

  python doc.py html

Open build/html/sycl-index.html in your browser.

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

Resolve conflicts and commit.
