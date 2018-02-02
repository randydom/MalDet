# MalDet --  A Tool for Malware Detection

A static tool for malware detection

## Overview

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

This tool accompanies with 
  + [**IDA Pro**](https://www.hex-rays.com/products/ida/index.shtml)
  + [**Jakstab**](http://www.jakstab.org/)
  + [**Moped**](http://www2.informatik.uni-stuttgart.de/fmi/szs/tools/moped/)

### Installing

This tool is setup in the folder **MalDet** by the following steps:
+ Download [**MalDet.7z**](https://dkhuuthe.github.io) and decompress it.
+ You install [**IDA Pro**](https://www.hex-rays.com/products/ida/index.shtml). After install IDA Pro to your PC, you copy the installed folder to the folder containing this tool (**MalDet**). Then, you copy our two files **analysis.idc** and **idc.idc** to the folder **idc** of IDA Pro.
+ You copy the Jakstab folder to **MalDet**.
+ You download the source code of [**Moped**](http://www2.informatik.uni-stuttgart.de/fmi/szs/tools/moped/). Then, you copy our file **poststar.c** to the Moped folder. After compilation, you create **moped_src** folder in **MalDet** and copy the executable of moped to the folder **moped_src**.
 

```
 Commands:
      Train  Compute the malicious API graphs from executables in <ListFiles>
                   Usage: MalDet.exe Train [options] <ListFiles>

      Test   Check an executable file (<TestFile>)
                   Usage: MalDet.exe Test [options] <TestFile> <ListFiles>

    Options:
    -g<n>  specify the kind of graph to compute
                n=0 denotes Extended API call graph (default),
                n=1 denotes API call graph,
    -N<n>  specify the number of highest terms in the malicious API graph.
    -F<f>  specify the type of the function used in the term weighting scheme.
                f=0 denotes function F1 (a linear function),
                f=1 denotes function F2 (a rational function),
                f=2 denotes function F3 (a logarithmic function),
                f=2 denotes function F4 (a sigmoid function).
    -W<w>  specify the Equation used in the term weighting scheme.
                w=1 denotes Rocchio Equation,
                w=2 denotes Ratio Equation.
    -S<s>  specify the strategy (s=1,2,3) to compute graphs.
```
 
End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone who's code was used
* Inspiration
* etc
