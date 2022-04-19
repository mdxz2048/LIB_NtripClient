/**
 * @file lib_mdxz_tools.h
 * @author lzp (lvzhipeng@mdxz.com.cn)
 * @brief 
 * @version 0.1
 * @date 2022-03-28
 * 
 * @copyright Copyright (c) MDXZ 2022
 * 
 */
#ifndef __LIB_MDXZ_TOOLS__H_
#define __LIB_MDXZ_TOOLS__H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdxz_types.h"

/**
 * @brief 打印LIB版本信息
 * 
 * @return VOID 
 */

VOID mdxz_tools_printf_lib_info(VOID);

/**
 * @brief 以十六进制打印buf的值
 * 
 * @param buf
 * @param len 
 * @return VOID 
 */
VOID mdxz_tools_printf_hexdump(char *buf, int len);
#ifdef __cplusplus
}

#endif

#endif