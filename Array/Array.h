//
// Created by yongheng on 23-1-23.
//

#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

#include "../mainwindow.h"
#include <vector>
#include <QPainterPath>

class ArrayNode{
    int val_;

    QPainterPath path_;
    int width_{}, height_{};
    int x_{},y_{};
public:
    explicit ArrayNode(int val);
    ~ArrayNode();

    void Draw(QWidget *window);


};
class Array {

    std::vector<ArrayNode> array_{};
    QPainterPath path_;


public:
    Array();
    ~Array();

    void Draw(QWidget *window);
    void Draw(MainWindow *window);
    void PushBack(int val);
};


#endif //ARRAY_ARRAY_H
