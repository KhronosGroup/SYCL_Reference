==========================
 DPC++ Language Reference
==========================
 
dpcpp
=====

.. image:: https://gitlab.devtools.intel.com/infodev/dpcpp-language-reference/badges/dpcpp/pipeline.svg
    :target: https://gitlab.devtools.intel.com/infodev/dpcpp-language-reference/-/jobs
    :alt: pipeline status

`HTML
<https://infodev.gitlab-pages.devtools.intel.com/dpcpp-language-reference/dpcpp/dpcpp-index.html>`__


SYCL
====

.. image:: https://gitlab.devtools.intel.com/infodev/dpcpp-language-reference/badges/sycl/pipeline.svg
    :target: https://gitlab.devtools.intel.com/infodev/dpcpp-language-reference/-/jobs
    :alt: pipeline status
	  
`HTML
<https://infodev.gitlab-pages.devtools.intel.com/dpcpp-language-reference/sycl/sycl-index.html>`__

Updates
=======

If the change is common to SYCL and DPC++, then commit the change to the
sycl branch and merge it into dpcpp branch::

  git checkout dpcpp
  git merge sycl
  # resolve conflicts and commit


Contributors and reviewers may submit a pull request, comment on an
existing merge request, or file an issue to provide input.

Contact `Robert Cohn <mailto:robert.s.cohn@intel.com>`__ or `Jacqui
DuPont <mailto:jacqui.b.dupont@intel.com>`__ with questions.
