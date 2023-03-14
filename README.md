# Reconstruction

Documentation on the MDT reconstruction code.
The mdtreco package decodes the data taken from the MDT and fills a root tree

## Version installed on the lab pc:

Can be found in:
/mdt/reconstruction/mdtreco

## Install the code on your computer

You need to have first of all installed ROOT ( from https://root.cern.ch )

You also need the code building tool cmake ( https://cmake.org ), that you can either download from the page, 
or install with the package manager on you pc. 
For example, yum install cmake , or snap install cmake , depending on the linux version you are using

Then to install the reconstruction code, first of all clone it from this repository:

git clone https://github.com/MDTCosmicLab/reconstruction.git

Then to compile:

cd mdtreco

cmake .

make   
( or make -jN where N is the number of threads you want to use for compilation )

## How to run the reconstruction

To run the analysis on a given run:
./mdtreco nevents runnumber directory

where:

nevents is the number of events to process ( 0 means all the available events ) 

runnumber is the number of the run to process

directory is the directory where the runs are stored (/mdt/data is the default, used in the lab pc) 
 

 


