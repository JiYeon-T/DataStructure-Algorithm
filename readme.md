TODO:
1. 创建一个基于文件实现的相对比较稳定的存储机制, kvdb, 
功能:通过 key 进行增删改查的操作;
原理:文件中进行存储
例如:miwear_kv.c
item0:[key][len][value][CRC/sumcheck]
item1:[key][len][value][CRC/sumcheck]
...

2. 可以优化的地方, 所有的源文件都会被编译, 很多文件其实在单次编译中都是用不到的





##### 1.创建了一个与数据结构与算法强化有关的项目，用于日常的算法积累与coding练习。
Talk is cheap, show me the code.-Linus Towards


##### 2. 通过时间戳计算公历时间的计算算法，肯定可以优化

##### 3. exit
