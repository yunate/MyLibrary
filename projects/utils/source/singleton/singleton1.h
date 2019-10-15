#ifndef __SIGLETON1_CLASS_H_
#define __SIGLETON1_CLASS_H_

#include <mutex>

template<class T>
class SingletonWrapper1 : public T
{
};

/** 懒汉模式
这个类有一定的问题，如果一定要使用懒汉模式，请自己考虑好内存问题
*/
template <class T>
class Singleton1
{
public:
    static T* GetInstance()
    {
        if (s_pInstance == NULL)
        {
            Lock();

            if (s_pInstance == NULL)
            {
                // 堆上的内存，我们没有机会去释放它，它的析构函数执行不到，有泄漏的风险
                s_pInstance = new SingletonWrapper1<T>();
            }

            UnLock();
        }

        return s_pInstance;
    }

private:
    Singleton1()
    {
    }

    Singleton1(const Singleton1&)
    {
    }

    Singleton1& operator = (const Singleton1&)
    {
    }

    ~Singleton1()
    {
    }

    static void Lock()
    {
        m_pMutex->lock();
    }

    static void UnLock()
    {
        m_pMutex->unlock();
    }

    static T* s_pInstance;
    static std::mutex* m_pMutex;
};

template<class T>
T* Singleton1<T>::s_pInstance = NULL;

template<class T>
std::mutex* Singleton1<T>::m_pMutex = new std::mutex();

#endif // __SIGLETON1_CLASS_H_
