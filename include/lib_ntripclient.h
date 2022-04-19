#ifndef _LIB_MDXZ_NTRIPCLIENT_H_
#define _LIB_MDXZ_NTRIPCLIENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
#include "mdxz_types.h"

 #define MDXZ_RTCM_DATA_LEN 1024*10

/*RTK平台信息*/
/**
 * @brief RTK平台名称
 */
enum RTK_PLATFORM
{
    RTK_PLATFORM_HUACE = 1,     //华测
    RTK_PLATFORM_QXWZ = 2,      //千寻
    RTK_PLATFORM_SQTW = 3,      //上汽通五
    RTK_PLATFORM_RESERVED1 = 8, //保留1
    RTK_PLATFORM_RESERVED2 = 9, //保留1
    RTK_PLATFORM_RESERVED3 = 10,//保留3    
};
/*NTRIP服务器MODE*/
/**
 * @brief RTK平台名称
 */
enum RTK_MODE
{
  HTTP = 1,
  RTSP = 2,
  NTRIP1 = 3,
  AUTO = 4,
  UDP = 5,
  MODE_END
};
/**
 * @brief RTK平台注册信息
 */
typedef struct
{
    enum RTK_PLATFORM Platform;
    enum RTK_MODE mode;
    char ip[32];
    int port;
    char user[32];
    char pwd[32];
    char mountpoint[32];
} rtkServer_c;
/**
 * @brief  RTCM数据
 */
typedef struct
{
    int rtk_status;
    char rtcm_data[MDXZ_RTCM_DATA_LEN];
    int rtn_data_len;
} mdxz_rtcm_info_t;
/**
 * @brief  RTCM数据的回调函数格式
 */
typedef int (*mdxz_rtk_callbak_func)(mdxz_rtcm_info_t *param);
/**
 * @brief  RTK初始化参数
 */
typedef struct rtk_c
{
    rtkServer_c *rtk_server_info;
    char * nmea;//gga
    mdxz_rtk_callbak_func rtk_callbak_function;
} rtk_c;

/**
 * @brief 打印LIB版本信息
 * 
 * @return VOID 
 */
VOID lib_mdxz_ntripclient_printf_lib_info(VOID);

/**
 * @brief  初始胡连接rtk平台，挂接RTCM数据解析函数。
 * @param  rtk_info            参见rtk_c定义
 * @return 成功 MDXZ_SUCCESS
 *         超时 MDXZ_TIMEOUT
 *         失败 MDXZ_FAILURE  
 */
int lib_mdxz_ntripclient_init(rtk_c *rtk_info);

/**
 * @brief  发送GGA数据到RTK平台。
 * @param  gga_data         GGA数据
 * @param  gga_len          数据长度F
 * @return 成功 MDXZ_SUCCESS
 *         失败 MDXZ_FAILURE  
 */
int lib_mdxz_ntripclient_send_gga(char *gga_data, int gga_len);

#endif