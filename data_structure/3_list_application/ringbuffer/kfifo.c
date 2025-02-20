#include "kfifo.h"
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>

// #include <linux/kfifo.h>
/* linux 内核中常见的数据结构, 自身是环形队列, 
 适用于单生产者, 单消费者形式的数据流操作, 不需要加锁(入队和出队使用不同的变量, 互不影响)
 如果有多个生产者线程, 则入队需要加锁
 数据结构:
 ------------------------------------------------
 | | | | | | | | | | | | | | | | | | | | | | | |
 ------------------------------------------------
  in                                          out
  ------------------------------------------------

  参考文献:
  https://blog.csdn.net/hinewcc/article/details/139460090
  https://zhuanlan.zhihu.com/p/500070147
 */
struct kfifo {
    unsigned int in;
    unsigned int out;
	unsigned int	mask;         //向上扩展成2的幂queue_size-1
	unsigned int	esize;        //每个元素的大小，单位为字节
	void		*data;            //存储数据的缓冲区
};



