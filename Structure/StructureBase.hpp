/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/05 23:08
*******************************************************************************/

#ifndef _StructureBase_H_
#define _StructureBase_H_
#include "../CustomGraphics/CustomGraphics.h"

template <template<typename> class U, typename T>
class StructureBase {
protected:
    U<T> _val;
public:
    virtual void Draw(CustomScene*) = 0;
    virtual void Clear(CustomScene*) = 0;
    virtual void Install(T) = 0;
    virtual void Delete(T*) = 0;
    virtual void Updata(T*) = 0;
    virtual void Search(T*) = 0;

};


#endif // _StructureBase_H_
