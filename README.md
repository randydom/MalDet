
# MalDet --  A Tool for Malware Detection

## Overview
Since the number of malwares is increasing very fast, the malware detection is a big challenge. The well-known technique is based on matching the signature (a sequence of binary) to detect malware. This technique is easily evaded by the obfuscation technique where the binary code of malware is changed while keeping the same behaviors.  Another technique in malware detection is the emulating technique  where the behaviors of malware are dynamically observed while running the program on an emulated environment. Although the running behaviors of the program are easily captured in this controlled environment, it is hard to get the malicious behaviors  in a short period since they may require a delay or only show up after user interaction. To sidestep limitations of these techniques, the static analysis approach is implemented for malware detection since it allows to analyze the behaviors (not the syntax) of the program without executing it. However, in this technique, one have to find a formula to specify the malicious behaviors. Currently, this task is done manually. Hence, we introduce an approach in order to automatize the task from extraction of malicious behaviors  and to detect malwares. First, we apply the term weighting scheme in Information Retrieval Community to compute the *malicious API call graph*, which is relevant to malware graphs but irrelevant to benign program graphs, from the malwares and benign programs. Then, we use this graph to detect a new program.
![MalDet is a tool for malware detection](https://raw.githubusercontent.com/dkhuuthe/MalDet/path/images/MalDet_small.png)
We implement **MalDet** for malware detection. It takes an input sets of malwares and benwares and computes the malicious behaviors (*the malicious API call graph*) in the training phase. Then, it uses the malicious behaviors extracted from the training phase to verify a new program. If the graph of the new program contains any malicious behavior, it says "**Malicious!**". Otherwise, it says "**Benign!**".

## Prerequisites

This tool accompanies with 
  + [**IDA Pro**](https://www.hex-rays.com/products/ida/index.shtml)
  + [**Jakstab**](http://www.jakstab.org/)
  + [**Moped**](http://www2.informatik.uni-stuttgart.de/fmi/szs/tools/moped/)

## Installing

This tool is setup in the folder *MalDet* by the following steps:
+ Download [*MalDet.7z*](https://github.com/dkhuuthe/MalDet/raw/master/MalDet.7z) and decompress it.
+ Install [*IDA Pro*](https://www.hex-rays.com/products/ida/index.shtml). Then, copy the IDA Pro folder to *MalDet* and copy two files *analysis.idc* and *idc.idc* to the folder *idc* in the IDA Pro folder.
+ Copy the [Jakstab](http://www.jakstab.org/) folder to *MalDet*.
+ Download the source code of [Moped](http://www2.informatik.uni-stuttgart.de/fmi/szs/tools/moped/) and replace *poststar.c* in *moped_src*. Then, compile this source code to get the executable file and copy it to *moped_src* in *MalDet*.

## How to
There are two phases:
### Training phase: 
```
Usage: MalDet.exe Train [options] <ListFiles>
```
```
Options:
   -g<n>  specify the kind of graph to compute
          n=0 denotes Extended API call graph (default),
          n=1 denotes API call graph,
   -N<n>  specify the number of highest terms in the malicious API graph.
   -F<f>  specify the type of the function for term weight computation.
          f=0 denotes function F1 (a linear function),
          f=1 denotes function F2 (a rational function),
          f=2 denotes function F3 (a logarithmic function),
          f=2 denotes function F4 (a sigmoid function).
   -W<w>  specify the Equation for term weight computation.
          w=1 denotes Rocchio Equation,
          w=2 denotes Ratio Equation.
   -S<s>  specify the strategy (s=1,2,3) to compute graphs.
```
It takes an input *ListFiles* which contains a set of malwares and a set benwares and gives the malicious API call graph which is extracted from these two set. An example of *ListFiles* (*trainSvm.txt*) is as follows.
```
@Backdoor
Backdoor.Win32.Hupigon.are.exe
Backdoor.Win32.WCRat.11.exe
Backdoor.Win32.Plunix.c.exe.upx
Backdoor.Win32.Sneaker.exe.upx
Backdoor.Win32.DSNX.plugin.PortScan.exe.upx
@Worm
Worm.Win32.Shorm.120.a.exe
Worm.Win32.Lioten.exe.upx
Worm.Win32.Petik.c.exe.upx
@NegativeSet
aafire.exe
aaflip.exe
aainfo.exe
aasavefont.exe
aatest.exe
```
This example of *ListFiles* contains Backdoor family (*Backdoor*), Worm family (*Worm*) and a set of benign programs (*NegativeSet*).

There are different options to compute the malicious API call graph according to the parameters **S** (strategy), **F** (Frequency Function), **W** (Equation), **N** (the number of nodes/edges). The output of the training phase is stored in the folder *specification*.

**Extraction of Malious Behaviors** We will extract the malicious behaviors from the set of malwares and benwares listed in *trainSvm.txt*.
This malicious graph is extracted by using Stragegy S1 with Equation Ratio and Fomular F3 with n=55.
```
MalDet.exe Train -N55 -S1 -W2 -F3 trainSvm.txt
```
![Training](https://github.com/dkhuuthe/MalDet/raw/path/images/train.png)
**Output:**
```
n55_S1_w2_f3_@Backdoor_Edge.txt
n55_S1_w2_f3_@Backdoor_Node.txt
n55_S1_w2_f3_@Worm_Edge.txt
n55_S1_w2_f3_@Worm_Node.txt
```
(In [**Samples.7z**](https://github.com/dkhuuthe/MalDet/raw/master/Samples.7z), we give the folder *specification*)

### Test phase:
Use the malicious API call graph extracted from the training phase, we check malicious behaviors in a new program.
```
Usage: MalDet.exe Test [options] <TestFile> <ListFiles>
```
We have to choose the options according to the specifications computed in the training phase.
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

