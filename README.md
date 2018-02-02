
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
+ Install [**IDA Pro**](https://www.hex-rays.com/products/ida/index.shtml). Then, copy the IDA Pro folder to **MalDet** and copy two files **analysis.idc** and **idc.idc** to the folder **idc** in the IDA Pro folder.
+ Copy the [***Jakstab**](http://www.jakstab.org/) folder to **MalDet**.
+ Download the source code of [**Moped**](http://www2.informatik.uni-stuttgart.de/fmi/szs/tools/moped/) and replace **poststar.c** in *moped_src*. Then, compile this source code to get the executable file and copy it to *moped_src* in **MalDet**.

**Extraction of Malious Behaviors**
We first compute the malicious API call graph from a set of malwares and a set of benwares (*trainSvm.txt*) by the command as follows.
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
Use the malicious API call graph extracted from the training phase, we check malicious behaviors in a new program as follows.
```
Usage: MalDet.exe Test [options] <TestFile> <ListFiles>
```
We have to choose the options according to the training phase.
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

