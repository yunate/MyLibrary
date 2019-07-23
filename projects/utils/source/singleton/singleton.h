#ifndef __SIGLETON_CLASS_H_
#define __SIGLETON_CLASS_H_

/** 饿汉模式
*/
template <class T>
class Singleton
{
public:
    static T* GetInstance()
    {
        // 为了能够在main函数前初始化s_pInstance
        s_pInstance;
        static T instance;
        return &instance;
    }

private:
    Singleton()
    {
    }

    Singleton(const Singleton&)
    {
    }

    Singleton& operator = (const Singleton&)
    {
    }

    ~Singleton()
    {
    }

    /** 强制饿汉模式，这种写法主要是为了防止初始化依赖问题
    */
    static T& s_pInstance;
};

template<class T>
T& Singleton<T>::s_pInstance = *Singleton<T>::GetInstance();

#endif // __SIGLETON_CLASS_H_
