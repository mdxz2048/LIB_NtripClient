#include <stdio.h>
#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "mdxz_types.h"
#include "lib_ntripclient.h"
#include "lib_ntripclient_test.h"

static OPTION_t opts[] = {
    {"help", NO_ARGUMENT, 0, 'h'},
    {"printf version", NO_ARGUMENT, 0, 'v'},
    {"use default RTK(MDXZ)", NO_ARGUMENT, 0, 'd'},
    {"NTRIP1 | AUTO", REQUIRED_ARGUMENT, 0, 'M'},
    {"RTK server", REQUIRED_ARGUMENT, 0, 's'},
    {"RTK server port", REQUIRED_ARGUMENT, 0, 'r'},
    {"RTK login user", REQUIRED_ARGUMENT, 0, 'u'},
    {"RTK login user password", REQUIRED_ARGUMENT, 0, 'p'},
    {"mountpoint", REQUIRED_ARGUMENT, 0, 'm'},
    {"nema data", REQUIRED_ARGUMENT, 0, 'n'},
    {0, 0, 0, 0}};
static ARGS_t g_demo_args;

int rtk_platform = -1;
char rtkIp[32] = {0};
int rtkport = 0;
char userpwd[128] = {0};
char rtk_user[128] = {0};
char rtk_pwd[128] = {0};
int rtk_mode = 0;
char rtk_mountpoint[32] = {0};

char g_default_gga[] = "$GPGGA,003514.00,2940.38322311,N,10628.44756308,E,5,17,1.2,300.4490,M,0.0000,M,02,2723*54";

static uint32_t rtk_send_gga_frequency = 5; // rtk发送GGA到华测平台的频率

MDXZ_ERR_CODE_e getargs(int argc, char **argv, ARGS_t *args)
{
    int getoptr = -1;
    int help = -1;

    args->print_version_flag = MDXZ_DEV_FALSE;
    args->print_help_flag = MDXZ_DEV_FALSE;
    args->cfg_rtk_flag = MDXZ_DEV_FALSE;
    args->debug_flag = MDXZ_DEV_FALSE;

    do
    {
        switch ((getoptr = getopt(argc, argv, ARG_SHORT_OPTS)))
        {
        case 'h':
            help = 1;
            args->print_help_flag = MDXZ_DEV_TRUE;
            break;
        case 'v':
            args->print_version_flag = MDXZ_DEV_TRUE;
            break;
        case 'd':
            args->debug_flag = MDXZ_DEV_TRUE;
            break;
        case 'M':
            if (!strcmp(optarg, "NTRIP1"))
                args->srv_info.mode = NTRIP1;
            else if (!strcmp(optarg, "AUTO"))
                args->srv_info.mode = AUTO;
            break;
        case 's':
            strcpy(args->srv_info.ip, optarg);
            args->cfg_rtk_flag = MDXZ_DEV_TRUE;
            break;
        case 'r':
            args->srv_info.port = atoi(optarg);
            break;
        case 'u':
            strcpy(args->srv_info.user, optarg);
            break;
        case 'p':
            strcpy(args->srv_info.pwd, optarg);
            break;
        case 'm':
            strcpy(args->srv_info.mountpoint, optarg);
            break;
        case 'n':
            args->cfg_gga = optarg;
            break;
        }
    } while (getoptr != -1);
    if (help == 1)
    {
        printf("\nusage: ./libmdxzntripclienttest [OPTIONS]\n");
        printf("usage: ./libmdxzntripclienttest -M mode -s server -r port -u user -p password -m mountpoint -n $GPGGA...\n");

        printf("Options\tinclude:\n\n");

        for (int i = 0; i < ARRAY_SIZE(opts); i++)
        {
            printf("-%c\t%s\n", opts[i].val, opts[i].name);
        }
    }
    return MDXZ_SUCCESS;
}

/**
 * @brief 以十六进制打印buf的值
 *
 * @param buf
 * @param len
 * @return VOID
 */
VOID mdxz_tools_printf_hexdump(char *buf, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        printf("%02X ", buf[i]);
        if ((i + 1) % 24 == 0)
            printf("\n");
    }
    printf("\n");
    return;
}
/**
 * @brief RTCM数据处理回调
 *
 * @param param
 * @return int
 */
int handle_rtcm_data(mdxz_rtcm_info_t *param)
{
    mdxz_tools_printf_hexdump(param->rtcm_data, param->rtn_data_len);

    return MDXZ_SUCCESS;
}

MDXZ_ERR_CODE_e main(int argc, char **argv)
{
    MDXZ_ERR_CODE_e ret = -1;
    rtk_c rtkInfo;
    rtkServer_c default_rtk_server = {
        .Platform = RTK_PLATFORM_HUACE,
        .mode = NTRIP1,
        .ip = "113.204.231.107",
        .port = 33394,
        .user = "testrsu03",
        .pwd = "1789789",
        .mountpoint = "RTCM32",
    };

    if (MDXZ_SUCCESS == getargs(argc, argv, &g_demo_args))
    {
        if ((MDXZ_DEV_TRUE == g_demo_args.print_version_flag))
        {
            lib_mdxz_ntripclient_printf_lib_info();
        }
        else if (MDXZ_DEV_TRUE == g_demo_args.cfg_rtk_flag) //自定义配置
        {
            rtkInfo.rtk_server_info = &g_demo_args.srv_info;
            debug_printf("ntripclient test");
            if (!g_demo_args.cfg_gga)
            {
                rtkInfo.nmea = g_default_gga;
            }
            rtkInfo.rtk_callbak_function = handle_rtcm_data;

            // 1 初始化接口
            if (MDXZ_SUCCESS == lib_mdxz_ntripclient_init(&rtkInfo))
            {
                debug_printf("lib_mdxz_ntripclient_init() succeeded");
            }

            while (1)
            {
                debug_printf("libntripclient test.");
                sleep(1);
            }
        }
        else if (MDXZ_DEV_TRUE == g_demo_args.debug_flag) //默认配置
        {
            // 0 配置
            if (MDXZ_DEV_TRUE != g_demo_args.cfg_rtk_flag) //默认配置
            {
                rtkInfo.rtk_server_info = &default_rtk_server;
            }

            if (!g_demo_args.cfg_gga)
            {
                rtkInfo.nmea = g_default_gga;
            }

            rtkInfo.rtk_callbak_function = handle_rtcm_data;

            // 1 初始化接口
            if (MDXZ_SUCCESS == lib_mdxz_ntripclient_init(&rtkInfo))
            {
                debug_printf("lib_mdxz_ntripclient_init() succeeded");
            }

            while (1)
            {
                debug_printf("ntripclient test");
                sleep(1);
            }
        }
    }
    else
        debug_printf("getargs failed.");

    return MDXZ_SUCCESS;
}
