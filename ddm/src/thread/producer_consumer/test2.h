
#pragma once

#include "IConsume.h"
#include "iproducer.h"
#include "producer_consumer.h"
#include "timer_recorder/timer_recorder.h"

namespace utilstest
{
    class Goods :
        public igoods
    {
    public:
        Goods(const std::string& str)
        {
            m_buff = str;
        }

        std::string m_buff;
    };

    /** 如果有成员变量，该加锁的加锁
    */
    class Producer :
        public iproducer
    {
    public:
        /** 生产一个商品
        @return 一个商品的指针，由消费者释放，如果返回nullptr说明生产结束
        */
        virtual void product(std::function<void(igoods*)> callBack)
        {
            //存取模式
            DWORD dAccessType = (GENERIC_READ | GENERIC_WRITE);

            //共享模式
            DWORD dShareType = FILE_SHARE_READ | FILE_SHARE_WRITE;

            // 打开文件句柄
            HANDLE hFile = ::CreateFile(L"D:\\test\\vs2015.ent_chs.iso"
                , dAccessType    // 访问模式
                , dShareType    // 共享模式
                , nullptr
                , OPEN_EXISTING    // 如果存在则打开，否则失败
                , FILE_FLAG_OVERLAPPED  // 。。。
                , nullptr);

            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }

            DWORD dFileSize = ::GetFileSize(hFile, nullptr);

            // 创建映射句柄
            HANDLE hFileMap = ::CreateFileMapping(hFile
                , nullptr
                , PAGE_READWRITE  // 注意，和createfile要一致
                , 0
                , dFileSize
                , nullptr);

            if (hFileMap == nullptr)
            {
                ::CloseHandle(hFile);
                return;
            }

            ::CloseHandle(hFile);

            // 每次取500M
            DWORD dFileBlock = 1024 * 1024 * 512;
            DWORD dBegin = 0;
            DWORD dLen = 0;
            int curLen = 0;
            std::string ss = "";

            while (dBegin < dFileSize)
            {
                if (dFileBlock > dFileSize - dBegin)
                {
                    dLen = dFileSize - dBegin;
                }
                else
                {
                    dLen = dFileBlock;
                }

                LPVOID pFileBlock = ::MapViewOfFile(hFileMap
                    , FILE_MAP_ALL_ACCESS  // 注意，和createfile要一致
                    , 0
                    , dBegin     // 开始位置
                    , dLen);     // 映射长度

                if (pFileBlock == nullptr)
                {
                    return;
                }

                for (unsigned int i = 0; i < dLen; ++i)
                {
                    // 简单处理，异或一下，测试加密，这儿的读是不占电脑内存的
                    char* a = (char*)pFileBlock + i;
                    ss.append(1, *a);
                    ++curLen;

                    if (curLen == 20)
                    {
                        Goods* p = new Goods(ss);
                        callBack(p);
                        curLen = 0;
                        ss = "";
                    }
                }

                // 释放
                ::UnmapViewOfFile(pFileBlock);
                dBegin += dLen;
            }

            if (curLen > 0)
            {

            }

            ::CloseHandle(hFileMap);
        }
        goods_vec m_goodsVec;

    };

    /** 如果有成员变量，该加锁的加锁
    */
    class Consume :
        public iconsumer
    {
    public:
        /** 消费一个商品，消费完以后负责释放这个商品
        @param [in] goods 商品指针
        @return 是否成功
        */
        virtual bool consumer(igoods* goods)
        {
            ((Goods*)goods)->m_buff;
            return true;
        }
    };

#include <iostream>
    static void Test_Producerconsumer()
    {
        xtimer tmi;
        p_c_model* pp_c_model = new p_c_model(new Producer(), new Consume());
        pp_c_model->SetNotUseThreadCount(1);
        pp_c_model->SetMaxProducerCount(1);
        pp_c_model->Start();
        delete pp_c_model;
        std::cout << tmi.get_time_pass() << std::endl;
    }
}
