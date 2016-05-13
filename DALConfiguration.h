#pragma once

#define DEFAULT_POS -1              //操作块偏移量位置
#define BLOCK_SIZE 512              //单块大小
#define BLOCK_SIZE_DATA 500         //单块有效数据大小
#define BLOCK_SIZE_STATUS_FIELD 12  //块状态字段大小
#define CONTRL_STATUS_FILELD 12     //控制状态字段大小
#define ARRAY_LENGTH 100            //站点集合数组的初始最大长度
#define EACH_TIME_READ 50           //每次读取的数据量（按行计）
#define RECORD_SIZE 77   
#define ORIGIN_FILE_OPEN_MODE_OUT 1 //打开文件并清空内容，不存在该文件就创建
#define ORIGIN_FILE_OPEN_MODE_APP 2 //打开文件追加，不存在该文件就创建