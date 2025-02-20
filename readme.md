TODO:
循环链表: P35
https://baike.baidu.com/item/%E8%B7%B3%E8%A1%A8/22819833?fr=ge_ala


1. 创建一个基于文件实现的相对比较稳定的存储机制, kvdb, 
功能:通过 key 进行增删改查的操作;
原理:文件中进行存储
例如:miwear_kv.c
item0:[key][len][value][CRC/sumcheck]
item1:[key][len][value][CRC/sumcheck]
...

2. 可以优化的地方, 所有的源文件都会被编译, 很多文件其实在单次编译中都是用不到的

3.// TODO: 翻转链表



##### 1.创建了一个与数据结构与算法强化有关的项目，用于日常的算法积累与coding练习。
<<<<<<< Updated upstream
Talk is cheap, show me the code.-Linus Towards

=======
Talk is cheap, show me the code.
TODO:
1. kfifo
>>>>>>> Stashed changes

##### 2. 通过时间戳计算公历时间的计算算法，肯定可以优化


##### 2. build & run:
```shell
./build.sh
./build/data_structure_algorithm_test
```



##### 3. add a data structure method:
step1: 
创建源文件以及头文件;
step2:
CMakeLists.txt 中添加源文件, 以及路径;
```CMakeLists
file(GLOB SRC_LIST xxx.c)
include_directories( xxx_path)
```

step3:
build.config.h.in 中打开宏, 会自动生成对应的头文件 build_config.h;
```C
#define DataStructADT                    1
```
