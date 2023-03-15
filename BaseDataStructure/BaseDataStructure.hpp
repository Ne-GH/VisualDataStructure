/*******************************************************************************
 * Created by yongheng on 2023/03/15.
*******************************************************************************/

#ifndef DATASTRUCTUREVISUALIZATION_BASEDATASTRUCTURE_HPP
#define DATASTRUCTUREVISUALIZATION_BASEDATASTRUCTURE_HPP

#include <QWidget>

template <typename T>
class BaseDataStructure {
public:
    BaseDataStructure() = default;
    ~BaseDataStructure() = default;

    virtual void Create() = 0;
    virtual void Insert(T insert) = 0;
    virtual void Delete(T old,T need_delete) = 0;
    virtual void Update(T old,T updated) = 0;
    virtual T& Search(T search) = 0;

    virtual void Draw(QWidget *window) = 0;
    virtual void Erase() = 0;
};


#endif //DATASTRUCTUREVISUALIZATION_BASEDATASTRUCTURE_HPP
