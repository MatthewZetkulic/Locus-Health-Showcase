# Locus-Health-Showcase

In this repository are are two codes I have written in C and their associated files. In addition, rewritten one of the codes using Python and the PANDAS library of Python.

CSV summarizer:

Files: hiveParser8.15.16.cpp

Code in C that I wrote during my internship at the FDA Center for Biologics Evaluation and Research this summer, designed for DNA profiles. This takes any number of input .csv's and a column of interest and returns an output .csv with values in the different files from the column of interest. Here, I'm using dynamic memory allocation and small immediate memory use so that many files with many rows can be handled. Can also handle missing values, deleted columns, and files of different lengths.


Analysis of CERN data:

Files: mjz5zf_chi2fit.cpp signal_templates.dat, bkgd_templates.dat, data.dat, mjz5zf_BkgShape.pdf, mjz5zf_SigShape.pdf, mjz5zf_data.pdf, 

mjz5zf_chi2fit.cpp processes a signal template and background noise template, determining the proportion of signal and noise in an input data file. This is done by histogram binning the values from the three files, and determining at what proportion of sign/noise the minimum chi^2 value occurs.
