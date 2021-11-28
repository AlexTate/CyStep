# CyStep: a Cython conversion of HTSeq's StepVector

This project addresses performance issues associated with the Swig implementation of HTSeq's StepVector. While there are memory issues that need to be addressed, initial testing shows runtimes have been reduced by as much as **70%**.

Step storage containers are limited to Python sets for now. Think of it as a GenomicArray which is by default a GenomicArrayOfSets, from the ChromVector's perspective. Assignment from iterable containers is supported. Iterator unpacking and all set operations are handled in C++ via the CPython API. This means that strings (being iterables) should be passed via an iterable container such as a tuple to avoid tokenizing strings.

## Installation
```
# Clone the repository
git clone https://github.com/AlexTate/CyStep.git

# Build
cd CyStep
python setup.py build_ext

# Install
python setup.py install
```

## Usage
Simply patch it in:
```
import HTSeq
import CyStep._stepvector as StepVector

# This tells HTSeq to use the CyStep StepVector
setattr(HTSeq._HTSeq, "StepVector", StepVector)

# Notice: use a GenomicArray, not a GenomicArrayOfSets
feats = HTSeq.GenomicArray("auto", stranded=True, typecode='O')
iv = HTSeq.GenomicInterval( "chr3", 123203, 127245, "+" )

# Notice: since strings are tokenized on iteration in Python
# we have to wrap the string in an iterable to keep it "whole"
feats[iv] += {"featA"}
```
