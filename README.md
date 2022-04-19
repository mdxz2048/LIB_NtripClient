# 版本说明

## 当前版本

**NtripClient_LIB_1.0.1**

## 更新历史

### NtripClient_LIB_1.0.1
- 修改编译Makefile，重新编译库文件、单元测试程序; 
### NtripClient_LIB_1.0.0
- 创建源文件和demo程序；

# LIB功能说明

- 支持ntrip1协议的RTK平台(通过华测、上汽通五平台验证通过)

# 工程使用说明

## 编译

1. 加载交叉编译工具链；

2. 在工程根目录下执行`make`

3. 编译结果库文件在`./lib`目录；

4. demo测试程序在`./debug/bin`目录；

## demo接口说明

   1. 查看库版本信息指令；
        ```sh
         ./libmdxzlogtest -v
        ```

   2. help指令

        ```shell
        ./libmdxzntripclienttest -h
        ```

        

   3. 使用默认【RTK】平台测试

        ```sh
        ./libmdxzntripclienttest -d
        ```

        

   4. 使用自定义RTK平台测试

        ```sh
        ./libmdxzntripclienttest -M NTRIP1 -s 255.165.178.107 -r 33394 -u testrsu03 -p 1789789 -m RTCM32
        ```

        
