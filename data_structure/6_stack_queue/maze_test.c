/**
 * @file maze_test.c
 * @author your name (you@domain.com)
 * @brief // 4. 迷宫求解:深度优先算法以及广度优先算法
 * @version 0.1
 * @date 2022-11-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "maze_test.h"
#include "stack_v1.h"
#include <stdio.h>
#include <stdlib.h>
#include "../2_linklist/LinkList.h"

typedef int Status;
#define OK      1
#define ERROR   0
typedef unsigned int size_t;


// 迷宫
typedef struct Maze
{
    void *maze;
    size_t row;
    size_t col;
} maze_t;

// 位置
typedef struct Positon
{
    // size_t x; // col
    // size_t y; // row
    size_t col; // start from 0
    size_t row;
} position_t;

// TODO:
// 最终路径是一堆位置点的集合, 要保证顺序, 使用链表管理
// 暂时先用一个数组来保存路径
typedef struct Road
{
    Node *head; // 链表
    position_t position; // 数据部分保存位置
} road_t;

// 路径
position_t *road;
size_t roadCount; // 途径中经过的点


/**
 * @brief 1 - 代表墙壁, 不可以通过
 *        0 - 代表可以通过
 * 
 * @param[in] fileName
 * @param[out] maze 
 * @return Status
 */
static Status LoadMaze(const char *fileName, maze_t *maze)
{
    FILE *fp = NULL;
    size_t row, col;
    // maze_t maze;
    char ch;
    size_t idx = 0;
    char buff[100];

    // 读入迷宫
    fp = fopen(fileName, "r");
    if(!fp){
        printf("open %s error\r\n", fileName);
        return ERROR;
    }
    
    // 从文件中读取路径
    // facanf() 出错或者到达文件结尾返回 EOF
    // TODO:
    // 通过文件判断地图大小 row and col
    maze->row = 2;
    maze->col = 2;

    // 还需要动态扩容
    maze->maze = (char*)malloc(sizeof(char) * maze->row * maze->col);
    if(!maze->maze){
        printf("malloc failed\r\n");
        return ERROR;
    }

    while(fscanf(fp, "%s", buff) != EOF){
        printf("%s", (char*)maze->maze);
    }

    fclose(fp);

    return OK;
}

/**
 * @brief 根据地图大小初始化路径
 *        后面优化 -> 通过链表管理路径后就可以不传入地图了
 * 
 * @param maze 
 * @return Status 
 */
static position_t* InitRoad(maze_t *maze)
{
    // 初始化路径
    // TODO:
    // 初始化链表
    // InitLinkList();
    position_t *road = (position_t*)malloc(sizeof(position_t) * maze->row * maze->col);
    if(!road){
        printf("malloc failed\r\n");
        return NULL;
    }
    memset(road, 0, sizeof(position_t) * maze->row * maze->col);

    return road;
}

/**
 * @brief 打印地图和路径
 * 
 * @param maze 
 * @param road 路径数组
 * @return Status 
 */
static Status ShowMazeAndRoad(maze_t *maze, position_t *road)
{

}

/**
 * @brief 求路径
 * 
 * @param maze 
 * @param road 
 * @param start 开始点
 * @param end 结束点
 * @return Status 
 */
static Status SearchRoad(const maze_t *maze, position_t *road, const position_t start, const position_t end)
{
    if(!maze || !road || start.row > maze->row || start.col > maze->col || end.row > maze->row || end.col > maze->col){
        printf("error\r\n");
        return ERROR;
    }
    
}

/**
 * @brief 保存求得的路径
 * 
 * @param road 
 * @return Status 
 */
Status SaveRoad(position_t *road)
{

}

void maze_test()
{
    char *fileName = "./maze/maze_2.txt";
    maze_t maze;
    position_t *road;
    position_t start, end;

    if(LoadMaze(fileName, &maze) != OK){
        printf("load maze failed\r\n");
        return;
    }

    road = InitRoad(&maze);
    if(!road){
        printf("init road failed\r\n");
        return;
    }

    if(ShowMazeAndRoad(&maze, road) != OK){
        return;
    }

    start.row = 1;
    start.col = 1;
    end.row = 2;
    end.col = 2;
    if(SearchRoad(&maze, road, start, end) != OK){
        return;
    }

    if(ShowMazeAndRoad(&maze, road) != OK){
        return;
    }

    return;
}