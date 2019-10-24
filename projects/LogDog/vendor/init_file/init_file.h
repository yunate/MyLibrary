#ifndef __INITFILE_H_
#define __INITFILE_H_

#include <vector>

#include "typedef/DogString.h"

/** windows ini 文件的读写等
*/
class IniFile
{
public:
    ~IniFile();

    /** 创建一个实例
    @param [in] sPath 文件路径
    @param [in] bAlwaysCreate 文件不存在时是否自动创建，文件不存在时如果为false，返回0，否则自动创建文件
    @return 返回实例对象，需自己释放内存
    */
    static IniFile * CreateObj(const DogString& sPath, bool bAlwaysCreate = false);

    /** 添加一个key
    @param [in] sSection 哪一个section，如果不存在则创建
    @param [in] sKey 哪一个key
    @param [in] sValue 要设置的值
    @return 是否成功
    */
    bool AddKey(const DogChar * sSection, const DogChar * sKey, const DogChar * sValue);

    /** 删除一个key
    @param [in] sSection 哪一个section
    @param [in] sKey 哪一个key
    @return 是否成功
    */
    bool DelKey(const DogChar * sSection, const DogChar * sKey);

    /** 删除一个section
    @param [in] sSection 哪一个section
    @return 是否成功
    */
    bool DelSection(const DogChar * sSection);

    /** 修改一个key对应的值
    @param [in] sSection 哪一个section
    @param [in] sKey 哪一个key
    @param [in] sValue 要设置的值
    @return 是否成功
    */
    bool ChangKey(const DogChar * sSection, const DogChar * sKey, const DogChar * sValue);

    /** 获得一个key对应的值
    @param [in] sSection 哪一个section sSection == NULL 时候，枚举所有的section
    @param [in] sKey 哪一个key sKey == NULL 枚举section下所有的key
    @param [in] size 内部buff大小，默认的不够用的时候指定
    @return key对应的值
    */
    std::vector<DogString> Get(const DogChar * sSection, const DogChar * sKey, const int size = 512);

private:
    /** 构造函数
    */
    IniFile(const DogString& sPath);

private:
    /** 全路径
    */
    DogString    m_sFileFullPath;
};

#endif
