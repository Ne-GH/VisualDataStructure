//
// Created by yongheng on 23-1-23.
//

#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

#include "../mainwindow.h"
#include <vector>
#include <QPainterPath>
#include "BaseDataStructure.hpp"

template <typename T>
class Arr : BaseDataStructure<T> {
    using BaseDataStructure<T>::_x;
    using BaseDataStructure<T>::_y;
    std::vector<T> _arr;
public:
    Arr();
    ~Arr();
    void Create() override;
    void Insert(T insert) override;
    void Delete(T old,T need_delete) override;
    void Update(T old,T updated) override;
    std::optional<T&> Search(T search) override;

    void Draw(QPixmap &window) override;
    void Erase() override;
};

template <typename T>
Arr<T>::Arr() {
}
template <typename T>
Arr<T>::~Arr() {}
template <typename T>
void Arr<T>::Create() {}
template <typename T>
void Arr<T>::Insert(T insert) {
    _arr.push_back(insert);
}
template <typename T>
void Arr<T>::Delete(T old, T need_delete) {
    for (auto it = _arr.begin(); it != _arr.end(); ) {
        if (*it == old) {
            it = _arr.erase(it);
        }
        else {
            it ++;
        }
    }
}
template <typename T>
void Arr<T>::Update(T old, T updated) {
    for (auto& num : _arr) {
        if (num == old) {
            num = updated;
        }
    }
}
template <typename T>
std::optional<T&> Arr<T>::Search(T search) {
    for (auto& num : _arr) {
        if (num == search) {
            return num;
        }
    }
    return std::nullopt;
}
template <typename T>
void Arr<T>::Draw(QPixmap &pixmap) {
    QPainter painter(&pixmap);

}


template <typename T>
void Arr<T>::Erase() {}

//template<typename T = int>
//class Array {
//private:
//    class ArrayNode{
//        T val_;
//        int width_{}, height_{};
//        int x_{},y_{};
//    public:
//        explicit ArrayNode(T val);
//        ~ArrayNode() = default;
//        void Draw(QPixmap *pixmap);
//        void SetXY(int x,int y);
//        void SetWH(int w,int h);
//
//    };
//
//private:
//
//    std::vector<ArrayNode> array_{};
//
//public:
//    Array() = default;
//    ~Array() = default;
//
//
//
//
//    void Draw(QWidget *window);
//    void PushBack(T val);
//};
//
//template<typename T>
//void Array<T>::ArrayNode::SetXY(int x, int y) {
//    x_ = x;
//    y_ = y;
//}
//
//template<typename T>
//void Array<T>::ArrayNode::SetWH(int w, int h) {
//    width_ = w;
//    height_ = h;
//}
//
//
///*******************************************************************************
// * ArrayNode 的实现
//*******************************************************************************/
//template<typename T>
//Array<T>::ArrayNode::ArrayNode(T val) :val_(val) {  }
//
//
//template<typename T>
//void Array<T>::ArrayNode::Draw(QPixmap *pixmap) {
//    QPainter pp(pixmap);
//    pp.setRenderHint(QPainter::Antialiasing);
//    pp.setRenderHint(QPainter::SmoothPixmapTransform);
//
//    QRectF rect(x_,y_,width_,height_);
//    pp.drawRect(rect);
//    pp.drawText(rect,Qt::AlignCenter,std::to_string(val_).c_str());
//}
//
//
//
///*******************************************************************************
// * Array 的实现
// * Array 是ArrayNode的数组形式
//*******************************************************************************/
//
//template<typename T>
//void Array<T>::PushBack(T val) {
//    array_.emplace_back(val);
//}
///*******************************************************************************
// * 依次调用array中的Draw函数，但是要在之前计算窗口宽高，用来调整数组单个方块的长度
// *
//*******************************************************************************/
//
//template<typename T>
//void Array<T>::Draw(QWidget *window) {
//
////    int window_width = window->centralWidget()->width();
////    int window_height = window->centralWidget()->height();
//
//    int window_width = window->width();
//    int window_height = window->height();
//    std::cout << window_width << " " << window_height << std::endl;
//    size_t count_node = array_.size();
//    double available_width = window_width * 0.8;
//    double center_height = window_height*0.4;
//    double single_width = available_width / static_cast<double>(count_node);
//
//    // 将开始绘制的位置定位到窗口的特定位置
//    // width * 0.4?1
//
////    auto pixmap = new QPixmap(window_width,window_height);
////    pixmap->fill(Qt::yellow);
////
////    int x = 0;
////
////    for(auto node : array_) {
////        node.SetWH(single_width,single_width);
////        node.SetXY(x+window_width*0.1,window_height *0.4);
////        x += static_cast<int>(single_width);
////
////        node.Draw(pixmap);
////    }
////
////    QPainter painter(window);
////    // painter.translate(0,window->menuBar()->height());
////    painter.drawPixmap(0,0,*pixmap);
//
//
//    QPainter painter(window);
//    auto pixmap = new QPixmap(window_width,window_height);
//    QPainter pp(pixmap);
//    pp.drawLine(0,0,100,100);
//    painter.drawPixmap(0,0,*pixmap);
//
//
//
//
//}
//

#endif //ARRAY_ARRAY_H
