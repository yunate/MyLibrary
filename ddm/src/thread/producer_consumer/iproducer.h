
#ifndef iproducer_h_
#define iproducer_h_ 1
#include "base/g_def.h"
#include "igoods.h"
#include <functional>
BEG_NSP_DDM
/** 生产者接口
*/
class iproducer
{
public:
    /** 生产一个商品
    @param [in] functional 
    */
    virtual void product(std::function<void(igoods*)>) = 0;
    virtual ~iproducer() {}
};
END_NSP_DDM
#endif // iproducer_h_
