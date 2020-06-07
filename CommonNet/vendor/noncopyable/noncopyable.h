
#ifndef __NOCOPYABLE_H_
#define __NOCOPYABLE_H_

/** ≤ª‘ –Ì∏¥÷∆
*/
class NonCopyable
{
protected:
    NonCopyable()
    {
    }

    ~NonCopyable()
    {
    }

private:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator= (const NonCopyable&) = delete;
};

#endif //__NOCOPYABLE_H_
