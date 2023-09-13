这个什么他妈的filemapping  什么fileview这那的我已经碰到过很多次了，但是我一直都不理解他到底是个啥意思，今天看mimikatz的代码，又看到了这个东西，我这次一定要彻底弄明白他


参考链接：https://learn.microsoft.com/en-us/windows/win32/memory/file-mapping


所谓FileMapping就是把一个文件的内容关联到一个进程的一段虚拟地址空间中

系统会创建一个fileMapping对象，也被称作section object，来维护这个关联

一个fileView是一个进程的一段虚拟地址空间，这段地址空间被用来访问文件的内容

fileMapping允许进程使用随机IO和序列化IO，（不明白这两个IO是啥意思，手动输入？和程序输入？）

也允许进程高效的处理一个大的数据文件，比如数据库，而不需要把整个文件映射到内存中，多进程也可以使用内存映射的文件来共享数据


进程可以使用指针对fileView进行读写操作

fileMapping的使用提高了效率，因为文件存在于磁盘中，但是fileView存在于内存中，而内存要比磁盘高效太多了

进程还可以通过VirtualProtect函数来操作fileView

下面这张图演示了在磁盘上的文件、fileMapping对象和fileView之间的关系：

![image](https://github.com/wqreytuk/file_mapping/assets/48377190/5e157b9f-588c-41a3-bc5c-51c5e0a35f47)


存在于磁盘上的文件可以是任意你想要map到内存中的文件，或者也可以是系统的pagefile，

fileMapping对象可以包含文件的全部或者部分

这意味着当操作系统将fileMapping对象关联的内存 page交换出去时，所有在此期间发生的改动都会被写入到fileMapping关联的磁盘文件中

当fileMapping对象关联的内存 page交换回内存的时候，会从磁盘文件中恢复内容

一个fileView可以包含fileMapping对象的一部分或所有

一个进程可以通过fileView来操作这个文件，一个进程可以针对一个fileMapping对象创建出多个fileView

每一个进程创建出来的fileView都存在于该进程的虚拟地址空间中

当进程需要文件中的一部分数据时，但是这一部分数据并不在当前的fileView中，那么进程就可以unmap当前的fileView，
然后创建一个新的fileView

当多个进程使用同一个fileMapping对象来创建一个本地文件的fileView的时候，数据是一致的

也就是说，fileView包含了完全一样的磁盘文件的内容

如果你想要在进程间共享内存，那么这个文件是不可以存在于远程计算机中的



## 示例程序

https://github.com/wqreytuk/file_mapping/blob/main/ConsoleApplication2.cpp

C:\users\lc\1.txt

```
0
2
3
4
5
6
7
8
9
0
1
2
3
4
5
6
7
8
9
0
1
2
3
4
5
6
7
8
9
0
1
2
3
4
5
6
7
8
9
0
1
2
3
4
5
6
7
8
9
0
```



