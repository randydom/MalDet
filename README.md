# svmTool --  A Tool for Android Malware Detection

A static tool for android malware detection

## Requirements
- Java version 1.8 or above.

## Included data:
+ svmTool.jar is the main application.
+ noAPI.txt  declares the prefix of APIs.
+ DataBen and DataMal are archive files containing all training data.
+ svmTool.bat and tfidfTool.sh are script files to execute the main application.
+ TrainData folder contains the training configuration and training model.
+ Sample folder contains sample data.

## How to install?
The data and executable files of svmTool are packed in svmTool.tar. In order to use this tool, we do as follows.
+ Download svmTool.tar
	https://drive.google.com/open?id=0B9PO-H8CY0J_YUFuMGpGVzg1U0k
+ Extract files from svmTool.tar
	'''
  tar xvf	svmTool.tar
  '''
Now, the tool is ready!

## Functionality
This tool have two main functionalities: computing training model and detecting malicious behaviors in the given applications.
### Compute the training model
	+ Collect benign applications  in a folder named benignApkFolder and malicious applications in a folder named maliciousApkFolder.
	+ Prepare training data by using the commands: 
		svmTool packAPK -PB benignApkFolder -B benignPack -PM maliciousApkFolder -M maliciousPack
	+ Use this command for computing the training model:
		svmTool train -B benignPack -M maliciousPack
### Malicious behavior detection
	+ Collect new  applications and put  them in a folder named checkApk
	+ Detect malicious behaviors of applications in the folder checkApk by using the command:
		'''
    svmTool check -S checkApk
    '''

'''
Commands:
svmTool train <Options>
        Compute the classifier for given training data.
                -T <T>: max length of the common walks (default value = 3).
                -l <lambda>: lambda value to control the importance of length of walks (default value = 0.4).
                -B <filename>: the archive file contains all graphs of training benwares.
                -M <filename>: the archive file contains all graphs of training malwares.

svmTool check <Options>
        Check malicious behaviors in the applications in a folder.
                -S <foldername>: the folder contains all apk files.

svmTool test <Options>
        Test the classifier for given graph data.
                -S <foldername>: the folder contains all graphs of test data.
                -n <n>: the number of test samples.

svmTool clear
        Clean all training data.
'''

## Examples:
### To train new data:
+ First collect training applications (APK files) and store them in two folders named MalApkFolder and BenApkFolder.
+ Pack applications into archive files named MalPack and BenPack for training by using the command: 
	'''
  svmTool packAPK -PM MalApkFolder -M MalPack -PB BenApkFolder -B BenPack
  '''
+ Clean old training data:
'''
	svmTool clear
'''
+ Train new data:
'''
	svmTool train -B BenPack -M MalPack
'''
Wait for training to finish, the training model is stored in the folder named TrainData .

### To check new applications: 
+ Put these applications in the a folder named *checkApk* and use this command:
'''
	svmTool check -S checkApk
'''

## Included Packages:
+ apktool-2.2.1 (https://ibotpeaches.github.io/Apktool/)
+ ojalgo-41.0.0 (https://github.com/optimatika/ojAlgo)
+ libsvm (http://www.csie.ntu.edu.tw/~cjlin/libsvm/)
## References
+ Khanh Huu The Dam and Tayssir Touili. Learn Android malware. In Proceedings of IWSMA@ARES 2017.
