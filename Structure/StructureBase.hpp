/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/05 23:08
*******************************************************************************/

#ifndef _StructureBase_H_
#define _StructureBase_H_
#include "../CustomGraphics/CustomGraphics.h"

template <template<typename> class U>
class StructureBase {
protected:
    U<CustomItem *> _val;
public:
    virtual void Draw(CustomScene*) = 0;
    virtual void Clear(CustomScene*) = 0;
    virtual void Install(CustomItem*) = 0;
    virtual void Delete(CustomItem*) = 0;
    virtual void Updata(CustomItem*) = 0;
    virtual CustomItem* Search(CustomItem*) = 0;

    StructureBase() = default;
    virtual ~StructureBase() = default;
};


#endif // _StructureBase_H_
