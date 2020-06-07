
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

    /** ����г�Ա�������ü����ļ���
    */
    class Producer :
        public iproducer
    {
    public:
        /** ����һ����Ʒ
        @return һ����Ʒ��ָ�룬���������ͷţ��������nullptr˵����������
        */
        virtual void product(std::function<void(igoods*)> callBack)
        {
            //��ȡģʽ
            DWORD dAccessType = (GENERIC_READ | GENERIC_WRITE);

            //����ģʽ
            DWORD dShareType = FILE_SHARE_READ | FILE_SHARE_WRITE;

            // ���ļ����
            HANDLE hFile = ::CreateFile(L"D:\\test\\vs2015.ent_chs.iso"
                , dAccessType    // ����ģʽ
                , dShareType    // ����ģʽ
                , nullptr
                , OPEN_EXISTING    // ���������򿪣�����ʧ��
                , FILE_FLAG_OVERLAPPED  // ������
                , nullptr);

            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }

            DWORD dFileSize = ::GetFileSize(hFile, nullptr);

            // ����ӳ����
            HANDLE hFileMap = ::CreateFileMapping(hFile
                , nullptr
                , PAGE_READWRITE  // ע�⣬��createfileҪһ��
                , 0
                , dFileSize
                , nullptr);

            if (hFileMap == nullptr)
            {
                ::CloseHandle(hFile);
                return;
            }

            ::CloseHandle(hFile);

            // ÿ��ȡ500M
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
                    , FILE_MAP_ALL_ACCESS  // ע�⣬��createfileҪһ��
                    , 0
                    , dBegin     // ��ʼλ��
                    , dLen);     // ӳ�䳤��

                if (pFileBlock == nullptr)
                {
                    return;
                }

                for (unsigned int i = 0; i < dLen; ++i)
                {
                    // �򵥴������һ�£����Լ��ܣ�����Ķ��ǲ�ռ�����ڴ��
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

                // �ͷ�
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

    /** ����г�Ա�������ü����ļ���
    */
    class Consume :
        public iconsumer
    {
    public:
        /** ����һ����Ʒ���������Ժ����ͷ������Ʒ
        @param [in] goods ��Ʒָ��
        @return �Ƿ�ɹ�
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
        TimerRecorder tmi;
        p_c_model* pp_c_model = new p_c_model(new Producer(), new Consume());
        pp_c_model->SetNotUseThreadCount(1);
        pp_c_model->SetMaxProducerCount(1);
        pp_c_model->Start();
        delete pp_c_model;
        std::cout << tmi.GetTimePass() << std::endl;
    }
}
