#ifndef shared_memor_manager_h_
#define shared_memor_manager_h_ 1

#include "shared_memory.h"

#include "base/singleton.hpp"
#include "base/nocopyable.hpp"

#include <string>
#include <unordered_map>
#include <Windows.h>

BEG_NSP_DDM
class shared_memor_manager : public nocopyable
{
protected:
    shared_memor_manager();
    ~shared_memor_manager();

public:
    /** ���������ڴ棬����Ѿ��������
    @param [in] name �����ڴ����ƣ�Ϊ��ʱʧ��
    @param [in] size ��С
    @return ӳ������ʧ�ܷ���nullptr
    */
    sp_shared_memory create(const ddstr name, size_t size);

    /** �򿪹����ڴ棬������������ʧ��
    @param [in] name �����ڴ����ƣ�Ϊ��ʱʧ��
    @return ӳ������ʧ�ܷ���nullptr
    */
    sp_shared_memory open(const ddstr name);

    // ������ʱĿ¼·�������ڴ��������ڴ�ʧ��ʱ�򴴽��ļ��ط�
    // ���û�����ã�Ĭ��Ϊ%tmp%·��
    void SetTmpDir(const ddstr& tmpDir);

private:
    /** ����map�Ƿ��Ѿ�������
    @param [in] name �����ڴ����ƣ�Ϊ��ʱʧ��
    @return ӳ�����������ڷ���nullptr
    */
    HANDLE find(const ddstr name);

private:
    /** �ڴ�ӳ�������������Ƶ�map
    */
    std::unordered_map<ddstr, HANDLE> m_handleMap;

    // ��ʱĿ¼
    ddstr m_tmpDir;
};

// ��������
#define SHARED_MEMORY_MANAGER (singleton<shared_memor_manager>::get_instance())

END_NSP_DDM
#endif // shared_memor_manager_h_

