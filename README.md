# VBF invisible k-factor producer

## Introduction

This framework produces the k-factors used in the CMS Run 2 Higgs to Invisible analysis, as well as some generator level control distributions.
In addition to this README, the code is commented throughout.

The `master` branch contains everything necessary to produce the k-factors.

The `version-0.9` branch contains an older version, not fully described, but has more features and studies.
The output for the functions common to `master` will be the same though.

## Initial setup

The code should work with most versions of `ROOT` and/or `CMSSW`. It has only been fully tested with `CMSSW_9_4_10` and `CMSSW_10_1_7` though.

To compile simply type: `make`

The code is then split into two parts, first filling the histograms, and then plotting them and producing the k-factor files.

## Filling the histograms

The initial program called `FillHistograms` is run like:

-  `FillHistograms --filein path_to_input_root_file --fileout path_to_output_root_file`

This creates a class instance of `HiggsInvisible`, which in turn calls the functions in `src/Histogramming.cxx` (where the majority of the code is housed).
These functions perform a generator level selection (including identifying the correct boson), and fills `ROOT` histograms, which are stored in the output `ROOT` file.

Normally you will want to run `FillHistograms` over all samples, so there is a script `submit.py` provided, which will submit all of the relevant samples to the Imperial batch system. Run like:

-  `./submit.py`

You will need to change the `outputpath`, the `cmsswdir` and the `analysisdir` variables to ones corresponding to your system.

Finally when all jobs are completed you need to run:

-  `./merge.py`

This will merge (`hadd`) all individual `ROOT` output files, so there is exactly one for each initial dataset. Note that `merge.py` merges the same files that are listed in `submit.py` (i.e. it imports the list of datasets from `submit.py`).

##Plotting the Histograms

The main function for plotting the histograms is contained within `src/PlotHistograms.cxx`, which creates a class of `HiggsPlotting` (the code of which is contained within `src/HiggsPlotting` -- this contains the bulk of the functions).

The code is run like:

-- `./PlotHistograms --outdir path_to_output_directory`

Aside from some control distributions, contained within `path_to_output_directory/log and path_to_output_directory/linear`, the k-factors are output within `path_to_output_directory`.

The relevant output files for the analysis are as follows:

For the non-VBF analysis there are 6 files:
-  `2Dkfactor_nonVBF_znn.root`
-  `2Dkfactor_nonVBF_zjet.root`
-  `2Dkfactor_nonVBF_wjet.root`

-  `2Dkfactor_nonVBF_njet_znn.root`
-  `2Dkfactor_nonVBF_njet_zjet.root`
-  `2Dkfactor_nonVBF_njet_wjet.root`

Then there are 3 files each for the VTR and MTR (labelled VBF) VBF-analyses:
-  `2Dkfactor_VTR_znn.root`
-  `2Dkfactor_VTR_zjet.root`
-  `2Dkfactor_VTR_wjet.root`

-  `2Dkfactor_VBF_znn.root`
-  `2Dkfactor_VBF_zjet.root`
-  `2Dkfactor_VBF_wjet.root`

There is a post-processing stage for these files, which is performed by a second repository: https://github.com/snwebb/kfactors.
This is necessary due to missing uncertainty values in some samples, as well as the need to produce an input for `FAST` that does not cause a crash 
