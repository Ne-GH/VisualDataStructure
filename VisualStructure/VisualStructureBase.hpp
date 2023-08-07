/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 15:06
*******************************************************************************/

#ifndef VISUAL_STRUCTURE_BASE_HPP
#define VISUAL_STRUCTURE_BASE_HPP

#include "GraphicsScene.h"
#include "GraphicsItem.h"

template <typename T>
class VisualStructureBase {
protected:
    T _val;
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
