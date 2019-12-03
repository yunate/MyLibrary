
#ifndef __HTTP_UTILS_H_
#define __HTTP_UTILS_H_

#include "SocketHttpClient.h"

namespace DogHttp
{
    /** http Get请求
    @param[in] url请求的url
    @param[out] out请求返回的结果（成功不包含返回头，不成功只返回请求头）
    @return 是否成功，只有返回头为2XX才算成功
    */
    bool HttpGet(const DogStringA& url, DogStringA& out);

    /** http Post请求
    @param[in] url请求的url
    @param[in] data请求的body
    @param[out] out请求返回的结果（成功不包含返回头，不成功只返回请求头）
    @return 是否成功，只有返回头为2XX才算成功
    */
    bool HttpPost(const DogStringA& url, const DogStringA& data, DogStringA& out);
}

#endif //__HTTP_UTILS_H_
