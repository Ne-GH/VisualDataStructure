/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/19 15:46
*********************************************************************/
#ifndef MSTL_BINARYTREE_HPP
#define MSTL_BINARYTREE_HPP
#include <iostream>
#include <stack>
#include <queue>
#include "GraphicsItem.h"


namespace MSTL{


template<typename T>
struct TreeNode {
public:
    TreeNode *_parent = nullptr;

    TreeNode *_left = nullptr;
    TreeNode *_right = nullptr;
    bool _modify_flag = false;
    int _height = 0;
    T _val = 0;
    TreeNode() {  }
    TreeNode(T val) {
        _val = val;
        _height = 1;
    }
    friend std::ostream & operator << (std::ostream &out,TreeNode node){
        out << node._val;
        return out;
    }
    friend std::ostream & operator << (std::ostream &out,TreeNode *pnode){
        out << pnode->_val;
        return out;
    }
    ~TreeNode() {
        _parent = nullptr;
        _left = _right = nullptr;
        _modify_flag = false;
//        if (_val != nullptr) {
//            delete _val;
//        }
        _val = nullptr;
    }

};


template<typename T>
TreeNode<T> *Build(int left,int right,std::vector<T>& vec){
    int mid = (left + right) >> 1;
    TreeNode<T> *root = new TreeNode<T>(vec[mid]);
    if(left <= mid - 1){
        root->_left = Build(left,mid - 1,vec);
    }
    if(mid + 1 <= right){
        root->_right = Build(mid + 1,right,vec);
    }
    return root;
}


template <typename T>
auto GetVal(T node) {
    if constexpr (std::is_same_v<T,TreeNode<GraphicsItem *> *>) {
        return node->_val->GetVal();

    }
    else if constexpr (std::is_same_v<T,GraphicsItem *>) {
        return node->GetVal();
    }
    else {
        std::cout << typeid(T).name() << std::endl;
    }
    return 0;

}




template <typename T>
TreeNode<T>* RotateLeft (TreeNode<T> *root) {
    auto tmp = root->_right;
    root->_right = tmp->_left;
    if (tmp->_left) {
        tmp->_left->_parent = root;
    }
    tmp->_left = root;
    tmp->_parent = root->_parent;
    root->_parent = tmp;
    root->_height = _GetDeep(root);
    tmp->_height = _GetDeep(tmp);
    return tmp;
}

template<typename T>
TreeNode<T> *RotateRight(TreeNode<T>* root) {
    auto tmp = root->_left;
    root->_left = tmp->_right;
    if (tmp->_right) {
        tmp->_right->_parent = root;
    }
    tmp->_right = root;
    tmp->_parent = root->_parent;
    root->_parent = tmp;
    root->_height = _GetDeep(root);
    tmp->_height = _GetDeep(tmp);
    return tmp;
}

template<typename T>
TreeNode<T> *RotateLeftRight(TreeNode<T>* root) {
    root->_left = RotateLeft(root->_left);
    return RotateRight(root);
}

template<typename T>
TreeNode<T> *RotateRightLeft(TreeNode<T>* root) {
    root->_left = RotateRight(root->_left);
    return RotateLeft(root);
}


template<typename T>
TreeNode<T>* insert(TreeNode<T> *parent,TreeNode<T> *root,TreeNode<T> *data) {
    if (root == nullptr) {
        data->_parent = parent;
//        if (parent) {
//            parent->_modify_flag = true;
//        }
        return data;
    }
    // 插入到左子树
    if (GetVal(data) < GetVal(root)) {
        root->_left = insert(root,root->_left,data);
        root->_height = _GetDeep(root);
        if (_GetDeep(root->_left) - _GetDeep(root->_right) == 2) {
            if(GetVal(data) < GetVal(root)) {
                root = RotateRight(root);
            }
            else {
                root = RotateLeftRight(root);
            }
        }
    }
        // >= 插入到右子树
    else {
        root->_right = insert(root,root->_right,data);
        root->_height = _GetDeep(root);

        if (_GetDeep(root->_left) - _GetDeep(root->_right) == -2) {
            if (GetVal(data) > GetVal(root)) {
                root = RotateLeft(root);
            }
            else {
                root = RotateRightLeft(root);
            }
        }
    }
    return root;
}

    /*******************************************************************************
 * mode 为 是否开启平衡二叉树
*******************************************************************************/
template<typename T,bool mode = true>
class BinaryTree {
    TreeNode<T> *_root = nullptr;
    class iterator {
    public:
        iterator(TreeNode<T>* root) {
            fillStack(root);
        }

        TreeNode<T>* operator*() const {
            return traversalStack.top();
        }

        TreeNode<T>* operator++() {
            TreeNode<T>* node = traversalStack.top();
            traversalStack.pop();
            fillStack(node->_right);
            return node;
        }

        bool operator!=(const iterator& other) const {
            return !traversalStack.empty() || !other.traversalStack.empty();
        }

    private:
        std::stack<TreeNode<T>*> traversalStack;

        void fillStack(TreeNode<T>* node) {
            while (node) {
                traversalStack.push(node);
                node = node->_left;
            }
        }
    };
public:
    BinaryTree() {  }
    BinaryTree(T data){
        _root = new TreeNode<T>(data);
    }
    TreeNode<T> *GetRoot() {
        return _root;
    }

    TreeNode<T>* Insert(T data){
        if(_root == nullptr){
            _root = new TreeNode<T>(data);
            return _root;
        }
        else{
//            return _Insert(_root,data);
            TreeNode<T> *node = new TreeNode<T>(data);
            _root = insert(_root->_parent,_root,node);
            return node;
        }
    }



    /*******************************************************************************
     * 从给定的root出发,删除参数2中指定的节点
    *******************************************************************************/
    void Delete(TreeNode<T> *delete_node) {
        if (_root == nullptr) {
            return ;
        }
        _Delete(_root,delete_node);
    }
    TreeNode<T>* Search(T data){
        return _Search(_root,data);
    }
    int GetDeep(){
        return _GetDeep(_root);
    }
    int GetWidth() {
        if(_root == nullptr) 
            return 0;
        int max = 0; //树的最大宽度 
        std::queue<TreeNode<T> *> que;
        que.push(_root);
        while(!que.empty()){
            int width = que.size(); //本层宽度 
            for(int i = 0;i < width;i++){
                TreeNode<T>* tmp = que.front();
                que.pop();
                if(tmp->_left) que.push(tmp->_left);
                if(tmp->_right) que.push(tmp->_right);
            }
            max = max > width ? max : width; //宽度更新 
        }
        return max;
    }

    void Destroy(){
        _Destroy(_root);
        _root = nullptr;
    }
    ~BinaryTree(){
        Destroy();
    }
    bool Empty() {
        return _root == nullptr;
    }
    auto begin() {
        return iterator(_root);

    }
    auto end() {
        return iterator(nullptr);
    }

};



inline int MAX(int a,int b){
    return a > b ? a : b;
}
template<typename T>
int _GetDeep(TreeNode<T> *root){
    if(root == nullptr)
        return 0;
    return MAX(_GetDeep(root->_left), _GetDeep(root->_right)) + 1;
}

/* 带头节点一起销毁 */
template<typename T>
void _Destroy(TreeNode<T> *root){

    if(root == nullptr){
        return;
    }
    _Destroy(root->_left);
    _Destroy(root->_right);
    return;
}
template<typename T>
TreeNode<T>* _Search(TreeNode<T> *root,T data){
    if(root == nullptr)
        return nullptr;
    if(root->_val == data){
        return root;
    }
    else if(root->_val > data){
        return _Search(root->_left,data);
    }
    else {
        return _Search(root->_right,data);
    }
}
template <typename T>
TreeNode<T> *_Delete(TreeNode<T> *root,TreeNode<T> *delete_node) {
    if (root == nullptr) {
        return nullptr;
    }

    if (root->_val == delete_node->_val) {
        if (root->_left == nullptr) {
            TreeNode<T> *new_root = root->_right;
            if (new_root != nullptr) {
                new_root->_parent = root->_parent;
                if (new_root->_parent != nullptr) {
                    new_root->_parent->_modify_flag = true;
                }
            }
            delete root;
            return new_root;
        }
        else if (root->_right == nullptr) {
            TreeNode<T> *new_root = root->_left;
            if (new_root != nullptr) {
                new_root->_parent = root->_parent;
                if (new_root->_parent != nullptr) {
                    new_root->_parent->_modify_flag = true;
                }
            }
            delete root;
            return new_root;
        }
        else {
            // 找到右边的最小值
            TreeNode<T> *min_right = root->_right;
            while (min_right->_left) {
                min_right = min_right->_left;
            }
            // 将最小值赋值给root,并去右子树删除该最小值
            root->_val = min_right->_val;
            root->_modify_flag = true;
            root->_right = _Delete(root->_right, min_right);
        }
    }
    else if (root->_val->GetVal() > delete_node->_val->GetVal()) {
        root->_left = _Delete(root->_left, delete_node);
    }
    else {
        root->_right = _Delete(root->_right, delete_node);
    }
    return root;
}



}
#endif
