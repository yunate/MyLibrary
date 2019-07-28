
#ifndef __PRODUCER_H_
#define __PRODUCER_H_

#include "IGoods.h"
#include <functional>

/** 生产者接口
*/
class IProducer
{
public:
    /** 生产一个商品
    @param [in] functional 
    */
    virtual void Product(std::function<void(IGoods*)>) = 0;
    virtual ~IProducer() {}
};

#endif // __PRODUCER_H_
