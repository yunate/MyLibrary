
#ifndef _SOCKET_HTTP_CLIENT_H__
#define _SOCKET_HTTP_CLIENT_H__

#include "socket_tcp/SocketTcpClient.h"
#include "stream/IDogStream.h"
#include "typedef/DogInterger.h"

#include <functional>
#include <memory>

/** 进度回调函数
    @functional:
        @param [in] handledSize 已经处理的总大小
        @param [in] allSize 总大小
        @return 返回false时候，结束过程进度
*/
using  DogPercentCallBack = std::function<bool(const u64 handledSize, const u64 allSize)>;

/** 流的智能指针
*/
using SPDogStream = std::shared_ptr<IDogStream>;

class SocketHttpClient :
    public SocketTcpClient
{
public:
    /** 构造函数
    */
    SocketHttpClient();

    /** 析构函数
    */
    ~SocketHttpClient();

public:
    /** get 方法
    @param [in] urlStr 
    */
    bool Get(const DogStringA& urlStr);

    /** post 方法
    @param [in] urlStr
    */
    bool Post(const DogStringA& urlStr);

public:
    /** 设置下载进度回调
    @param [in] callback: 上传进度回调
    */
    void SetUploadPercentCallBack(const DogPercentCallBack& callback);

    /** 设置下载进度回调
    @param [in] callback: 下载进度回调
    */
    void SetDownloadPercentCallBack(const DogPercentCallBack& callback);

    /** 设置上传流
    @param [in] stream: 上传流
    */
    void SetUploadStream(const SPDogStream& stream);

    /** 设置下载流
    @param [in] stream: 下载流
    */
    void SetDownloadStream(const SPDogStream& stream);

protected:
    /** 上传进度回调
    */
    DogPercentCallBack m_upLoadPercentCallBack;

    /** 下载进度回调
    */
    DogPercentCallBack m_downLoadPercentCallBack;

    /** 上传流
    */
    SPDogStream m_upLoadStream;

    /** 下载流
    */
    SPDogStream m_downLoadLoadStream;
};


#endif // _SOCKET_HTTP_CLIENT_H__
