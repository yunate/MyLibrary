
#ifndef _SOCKET_HTTP_CLIENT_H__
#define _SOCKET_HTTP_CLIENT_H__

#include "noncopyable/noncopyable.h"
#include "stream/IDogStream.h"
#include "timer_recorder/timer_recorder.h"
#include "typedef/DogInterger.h"
#include "typedef/DogString.h"
#include "Url/DogUrl.h"

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

/** socket 封装类智能指针
*/
class SocketBase;
using SPSocketClient = std::shared_ptr<SocketBase>;

/** http类
*/
class SocketHttpClient:
    public NonCopyable
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
    @return 是否成功
    */
    bool Get(const DogStringA& urlStr);

    /** post 方法
    @param [in] urlStr
    @return 是否成功
    */
    bool Post(const DogStringA& urlStr);

private:
    /** 请求
    @param [in] urlStr
    @param [in] method 请求方法
    @return 是否成功,该函数不会去检查返回数据是否有效，是否完整，只要有数据返回，就为true
    */
    bool MakeRequest(const DogStringA& urlStr, const DogStringA& method);

    /** 创建socket client
    @param [in] urlStr
    @param [in] method 请求方法
    @param [out] url 如果成功的话返回的url
    @return 创建的socket对象，失败的话为空
    */
    SPSocketClient CreateSocketClient(const DogStringA& urlStr, const DogStringA& method, DogUrl& url);

    /** 拼接请求头
    @param [in] url
    @param [method] method 请求方法
    @param [out] strHttpHead输出
    */
    void CreateHead(const DogUrl& url, const DogStringA& method, DogStringA& strHttpHead);

    /** 接受数据
    @param [in] spClient tcp对象，它的有效性在外边判断，函数内部将会assert
    @param [in] gTimer 全局超时
    @param [out] head 接受的头部，主体在m_downLoadLoadStream中返回
    @return 是否成功
    */
    bool RecvResponse(SPSocketClient spClient, TimerRecorder& gTimer, DogStringA& head);

    /** 发送body，目前只POST发送
    @param [in] spClient tcp对象，它的有效性在外边判断，函数内部将会assert
    @param [in] gTimer全局超时
    @return 是否成功
    */
    bool SendBody(SPSocketClient spClient, TimerRecorder& gTimer);

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

    /** 绝对超时时间，从进入函数开始，到退出函数的最长等待时间，这是一个绝对超时时间，如果你不希望接受的数据只接受一般就结束了，请设置为0
    @note: 默认0
    @note: 为0时候为永不超时
    @param [in] timeOut: 超时时间 (ms)
    */
    void SetGTimeOut(u32 timeOut);

    /** 数据超时时间，指的是上一次数据到下一次数据之间的最长等待时间
    @note: 默认15000ms
    @note: 为0时候为永不超时
    @param [in] timeOut: 超时时间 (ms)
    */
    void SetDataTimeOut(u32 timeOut);

    /** 停止请求
    */
    void Stop();

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

    /** (ms) 绝对超时时间，从进入函数开始，到退出函数的最长等待时间，这是一个绝对超时时间，如果你不希望接受的数据只接受一般就结束了，请设置为0
    @note: 为0时候为永不超时
    */
    u32 m_gTimeOut;

    /** (ms) 数据超时时间，指的是上一次数据到下一次数据之间的最长等待时间
    @note: 显然它的优先级低于m_gTimeOut
    */
    u32 m_dataTimeOut;

    /** 是否停止
    */
    bool m_stop;
};

#endif // _SOCKET_HTTP_CLIENT_H__
