`insilico`
========

![GNU GPLv3 License](http://img.shields.io/badge/license-GPLv3-green.svg)
[![insilico Trello](https://img.shields.io/badge/Trello-insilico-blue.svg)](https://trello.com/b/lkXzPGqD/insilico)

`insilico` is a Computational Neuroscience simulation library written in C++. `insilico` encourages ready-to-start approach for quick setup of simulation environment, without hindering programmers time and focus from intended experiment.

Library homepage: http://www.iiserpune.ac.in/~collins/insilico/

Install
=======

Please refer to `doc/INSTALL` file.

Build
=====

Clone the source and run the following commands on terminal.
```
   make SOURCE="path/to/source/file/with/main_function.cpp"
```
Execute
=======

Run the following command on terminal to execute the code.
```
  insilico.out -o <output_file>.csv -n <neuron_file.isf> -s <synapse_file.isf> -e <external_file.isfc>

  Options:
    -o   Output file
    -n   Neuron configuration file
    -s   Synapse configuration file (optional)
    -e   External current configuration file (optional)
```
Please read `doc/FILES` file for details about the input and output files and their formats.

License
=======

This simulator library is licensed under GNU GPLv3 which can be found in `LICENSE` file under home directory of this project.
# insilico-ENEURO.0293-19.2020

Biophysical basis of alpha rhythm disruption in Alzheimer’s Disease (AD)
=======

Go to insilico-0.25/examples/ENEURO.0293-19.2020/ for the specific set of files used for simulations in https://doi.org/10.1523/ENEURO.0293-19.2020


