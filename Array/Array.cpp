//
// Created by yongheng on 23-1-23.
//

#include "Array.h"

/*******************************************************************************
 * ArrayNode 是Array中的单个元素
*******************************************************************************/
ArrayNode::ArrayNode(int val) :val_(val) {  }

ArrayNode::~ArrayNode() = default;

void ArrayNode::Draw(QWidget *window) {

}




/*******************************************************************************
 * Array 是ArrayNode的数组形式
*******************************************************************************/
Array::Array() = default;

Array::~Array() = default;

void Array::PushBack(int val) {
    array_.emplace_back(val);
}
/*******************************************************************************
 * 依次调用array中的Draw函数，但是要在之前计算窗口宽高，用来调整数组单个方块的长度
 *
*******************************************************************************/
void Array::Draw(MainWindow *window) {

    int window_width = window->width();
    int window_height = window->height();
    PushBack(10);
    PushBack(20);
    PushBack(30);
    size_t count_node = array_.size();


    auto &log = window->GetLog();
    log.AddLog("总大小为：" + std::to_string(window_width));
    log.AddLog("预计使用大小为：" + std::to_string(window_width*0.8));
    log.AddLog(std::to_string(count_node));
    log.AddLog("单个元素使用宽度为：" + std::to_string(window_width*0.8/static_cast<double>(count_node)));


    for(auto node : array_) {
        node.Draw(window);
    }
}
