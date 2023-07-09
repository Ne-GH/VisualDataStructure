/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 15:06
*******************************************************************************/

#ifndef _STRUCTUREBASE_H_
#define _STRUCTUREBASE_H_

#include "GraphicsScene.h"
#include "GraphicsItem.h"

template <template<typename> class U>
class VisualStructureBase {
protected:
    U<GraphicsItem *> _val;
public:
    virtual void Draw(GraphicsScene*) = 0;
    virtual void Clear(GraphicsScene*) = 0;
    virtual void Insert(GraphicsItem*) = 0;
    virtual void Delete(GraphicsItem*) = 0;
    virtual void Updata(GraphicsItem*) = 0;
    virtual GraphicsItem* Search(GraphicsItem*) = 0;

    VisualStructureBase() = default;
    virtual ~VisualStructureBase() = default;
};



#endif // _STRUCTUREBASE_H_