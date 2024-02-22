# Build_SOS_PBN_FDD

Physics-informed dynamic Bayesian network for Building HVAC FDD purpose

## Description

This algorithm comprises a two-step dynamic Bayesian network file (.xdsl) and a main FDD execution program file (.cpp). Additionally, the FDD data file (.csv) of a real building application is provided.

## Getting Started

### Dependencies

* SMILE library academic version from BayesFusion: https://download.bayesfusion.com/files.html?category=Academia
* C++ compiler

### Configuration

* For installing the SMILE engine and configuring it in C++ compiler, please see detailed instruction from BayesFusion: https://download.bayesfusion.com/files.html?category=Academia
* For modifying the Bayesian network file, please edit .xdsl file directly or via GeNie software. GeNie software can be downloaded from BayesFusion website. Help documents can be found at https://support.bayesfusion.com/docs/

### Executing program

* Build and run the main FDD program file (.cpp), e.g., in Windows
```
g++ -o program DBN_HVAC.cpp
DBN_HVAC.exe
```

## Authors

Contributors names and contact info

[@Dongyu Chen](https://www.linkedin.com/in/dongyu-chen-umd/?trk=public_profile_browsemap)

[@Qun Zhou Sun](https://www.cecs.ucf.edu/faculty/qun-zhou/)
