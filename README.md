# GetQuestion
Randomly select a question from a question set.

# 使用说明
请将题库文件夹命名为 "t"，且所有题目依序以 "tXXXX.txt" 命名后置于其中，并将该文件夹放入当前目录内。

你可以这样调用 "GetQuestion.exe" ：

    "GetQuestion.exe"        随机抽取未抽过的题目，并将题号记入询问记录
    "GetQuestion.exe -r"     初始化（清空）询问记录
    "GetQuestion.exe -c"     随机抽取所有题目（可重复），并将题号记入询问记录
    "GetQuestion.exe -q"     随机抽取未抽过的题目，不记入询问记录
    "GetQuestion.exe -cq"    随机抽取所有题目（可重复），不记入询问记录
    
在初次运行本程序前，请务必调用 "GetQuestion.exe -r" 以初始化询问记录，如果成功，当前目录下将产生"ask.dat"，如果此文件被删除，请重新调用 "GetQuestion.exe -r"。

使用除 "GetQuestion.exe -r" 之外的其他调用后，如果成功，当前目录下的 "GetQuestion.txt" 的内容将被更新（没有则创建）为抽取的题目，格式同原题目格式。

如果程序运行成功，将会返回0，否则将会返回以下值之一：

    101    不合法调用参数
    102    所有问题均已问过
    103    无法读取 "ask.dat"
    104    无法写入 "ask.dat"
    105    无法写入 "GetQuestion.txt"
    106    无法读取题目文件
    
在程序编写中，你可以这样使用本程序：（注："GetQuestion.exe" 在程序的当前文件夹下，Result 为返回值）
## VB
    Result = Shell("GetQuestion.exe", VbMinimizedNoFocus)
## Python
    import os
    Result = os.system('GetQuestion.exe') 
