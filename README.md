                              MalDet -- A Tool for Malware Detection

Usage: MalDet.exe <Command> [options] [<TestFile>] [<ListFiles>]

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

Version 0.0.1 (31.01.2018)

HOW TO INSTALL
This tool accompanies with 
  + IDA Pro (https://www.hex-rays.com/products/ida/index.shtml)
  + Jakstab (http://www.jakstab.org/)
  + PEiD (
  + UPX (https://upx.github.io)
  + Moped (http://www2.informatik.uni-stuttgart.de/fmi/szs/tools/moped/)

