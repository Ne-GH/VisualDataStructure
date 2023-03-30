/*******************************************************************************
 * Created by yongheng on 2023/03/15.
*******************************************************************************/

#ifndef DATASTRUCTUREVISUALIZATION_BASEDATASTRUCTURE_HPP
#define DATASTRUCTUREVISUALIZATION_BASEDATASTRUCTURE_HPP

#include <optional>
#include <QPixmap>
#include <QPainterPath>
template <typename T,typename Derived>
class BaseDataStructure {
protected:
    int _x = 0,_y = 0;
public:
    BaseDataStructure() = default;
    ~BaseDataStructure() = default;

    virtual void SetDrawPos(int x,int y) final;
    virtual Derived& Create() = 0;
    virtual void Insert(T insert) = 0;
    virtual void Delete(T old,T need_delete) = 0;
    virtual void Update(T old,T updated) = 0;
    virtual std::optional<T&> Search(T search) = 0;

    virtual void Draw(QPixmap &pixmap) = 0;
    virtual void Erase() = 0;
};

template <typename T,typename Derived>
void BaseDataStructure<T,Derived>::SetDrawPos(int x, int y) {
    _x = x;
    _y = y;
}


#endif //DATASTRUCTUREVISUALIZATION_BASEDATASTRUCTURE_HPP
