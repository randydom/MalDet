
# MalDet --  A Tool for Malware Detection

## Overview

![MalDet is a tool for malware detection](https://raw.githubusercontent.com/dkhuuthe/MalDet/path/images/MalDet_small.png)

### Prerequisites

This tool accompanies with 
  + [**IDA Pro**](https://www.hex-rays.com/products/ida/index.shtml)
  + [**Jakstab**](http://www.jakstab.org/)
  + [**Moped**](http://www2.informatik.uni-stuttgart.de/fmi/szs/tools/moped/)

### Installing

This tool is setup in the folder **MalDet** by the following steps:
+ Download [**MalDet.7z**](https://github.com/dkhuuthe/MalDet/raw/master/MalDet.7z) and decompress it.
+ You install [**IDA Pro**](https://www.hex-rays.com/products/ida/index.shtml). After install IDA Pro to your PC, you copy the installed folder to the folder containing this tool (**MalDet**). Then, you copy our two files **analysis.idc** and **idc.idc** to the folder **idc** of IDA Pro.
+ You copy the [***Jakstab**](http://www.jakstab.org/) folder to **MalDet**.
+ You download the source code of [**Moped**](http://www2.informatik.uni-stuttgart.de/fmi/szs/tools/moped/). Then, you copy our file **poststar.c** to the Moped folder. After compilation, you create **moped_src** folder in **MalDet** and copy the executable of moped to the folder **moped_src**.
 
**Extraction of Malious Behaviors**
```
Usage: MalDet.exe Train [options] <ListFiles>
```
```
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
+ Extracting the malicious behaviors from set of malwares and benwares listed in *trainSvm.txt*.
    This malicious graph is extracted by using Stragegy S1 with Equation Ratio and Fomular F3 with n=55.
```
MalDet.exe Train -N55 -S1 -W2 -F3 trainSvm.txt
```
![Training](https://github.com/dkhuuthe/MalDet/raw/path/images/train.png)

**Check New Programs**
```
Usage: MalDet.exe Test [options] <TestFile> <ListFiles>
```
+ Check the program **reg.exe** in the folder **Samples** whether contains any malicious behavior or not with the malicious graph which is extracted above.
```
MalDet.exe Test -N55 -S1 -W2 -F3 Samples\reg.exe trainSvm.txt
```
We obtained the answer "**Benign!**".
![reg.exe Benign](https://github.com/dkhuuthe/MalDet/raw/path/images/testreg.png)

+ Check the program **iexpress.exe** in the folder **Samples** whether contains any malicious behavior or not with the malicious graph which is extracted above.
```
MalDet.exe Test -N55 -S1 -W2 -F3 Samples\iexpress.exe trainSvm.txt
```
We obtained the answer "**Benign!**".
![iexpress.exe Benign](https://github.com/dkhuuthe/MalDet/raw/path/images/testiepress.png)

+ Check the program **Trojan-Downloader.Win32.Agent.hs.exe** in the folder **Samples** whether contains any malicious behavior or not with the malicious graph which is extracted above.
```
MalDet.exe Test -N55 -S1 -W2 -F3 Samples\Trojan-Downloader.Win32.Agent.hs.exe trainSvm.txt
```
We obtained the answer "**Malicious!**".
![Trojan-Downloader.Win32.Agent.hs.exe Malicious](https://github.com/dkhuuthe/MalDet/raw/path/images/testTrojan.png)


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
