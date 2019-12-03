#include "HttpUtil.h"

#include "stream/MemoryStream.h"


namespace DogHttp
{
    bool HttpGet(const DogStringA& url, DogStringA& out)
    {
        SPRequest request(new(std::nothrow) HttpRequest(HttpRequest::GET, url));
        SPResponse response(new(std::nothrow) HttpResponse());
        SPDogStream responseStream(new(std::nothrow)MemoryStream());
        SPHttpClient httpClient(new(std::nothrow) SocketHttpClient());

        if (request == NULL || response == NULL || responseStream == NULL || httpClient == NULL)
        {
            return false;
        }

        // 关闭长连接
        request->Set("Connection", "close");

        // 设置请求
        httpClient->SetRequest(request);

        // 设置输出流
        response->SetStream(responseStream);

        // 设置回复
        httpClient->SetResponse(response);

        // 设置超时时间
        httpClient->SetGTimeOut(15000);
        bool res = httpClient->MakeRequest();
        int statucCode = response->GetStatusCode();

        if (res && statucCode >= 200 && statucCode <= 300)
        {
            s64 size = responseStream->Size();
            out.resize((size_t)size);
            responseStream->ReadAllA((u8*)out.c_str());
            return true;
        }
        else
        {
            DogStringA body;
            s64 size = responseStream->Size();
            body.resize((size_t)size);
            responseStream->ReadAllA((u8*)body.c_str());
            out = response->GetRawHead();
            out += body;
            return false;
        }
    }

    bool HttpPost(const DogStringA& url, const DogStringA& data, DogStringA& out)
    {
        SPRequest request(new(std::nothrow) HttpRequest(HttpRequest::POST, url));
        SPResponse response(new(std::nothrow) HttpResponse());
        SPDogStream requestStream(new(std::nothrow)MemoryStream());
        SPDogStream responseStream(new(std::nothrow)MemoryStream());
        SPHttpClient httpClient(new(std::nothrow) SocketHttpClient());

        if (request == NULL ||
            response == NULL ||
            requestStream == NULL ||
            responseStream == NULL ||
            httpClient == NULL)
        {
            return false;
        }

        // 设置输入流
        requestStream->Write((u8*)data.c_str(), data.length());
        request->SetStream(requestStream);

        // 关闭长连接
        request->Set("Connection", " close");

        // 设置请求
        httpClient->SetRequest(request);

        // 设置输出流
        response->SetStream(responseStream);

        // 设置回复
        httpClient->SetResponse(response);

        // 设置超时时间
        httpClient->SetGTimeOut(15000);

        bool res = httpClient->MakeRequest();
        int statucCode = response->GetStatusCode();

        if (res && statucCode >= 200 && statucCode <= 300)
        {
            s64 size = responseStream->Size();
            out.resize((size_t)size);
            responseStream->ReadAllA((u8*)out.c_str());
            return true;
        }
        else
        {
            DogStringA body;
            s64 size = responseStream->Size();
            body.resize((size_t)size);
            responseStream->ReadAllA((u8*)body.c_str());
            out = response->GetRawHead();
            out += body;
            return false;
        }
    }
}

