/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/19 15:46
*********************************************************************/
#ifndef MSTL_BINARYTREE_HPP
#define MSTL_BINARYTREE_HPP
#include <iostream>
#include <vector>
#include "GraphicsItem.h"


namespace MSTL{


template<typename T>
class TreeNode {
public:
    TreeNode *_parent = nullptr;
    TreeNode *_left = nullptr;
    TreeNode *_right = nullptr;
    bool _modify_flag = false;
    T _val = 0;
    TreeNode() {  }
    TreeNode(T val) {
        _val = val;
    }
    bool GetModifyFlag() {
        return _modify_flag;
    }
    TreeNode *GetParent() {
        return _parent;
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

/*******************************************************************************
 * 获取root的右下角节点
*******************************************************************************/
template <typename T >
TreeNode<T> *GetRightDownNode(TreeNode<T> *root) {
    if (root == nullptr)
        return nullptr;
    if (root->_left == nullptr && root->_right == nullptr) {
        return root;
    }
    if (root->_right) {
        return GetRightDownNode(root->_right);
    }
    else {
        return GetRightDownNode(root->_left);
    }
    return nullptr;
}
/*******************************************************************************
 * mode 为 是否开启平衡二叉树
*******************************************************************************/
template<typename T,bool mode = true>
class BinaryTree {

    TreeNode<T> *_root = nullptr;
public:
    BinaryTree() {  }
    BinaryTree(T data){
        _root = new TreeNode<T>(data);
    }

    TreeNode<T>* Insert(T data){
        if(_root == nullptr){
            _root = new TreeNode<T>(data);
            return _root;
        }
        else{
            return _Insert(_root,data);
        }
//        if constexpr (mode == true) {
//            BalanceBinaryTree();
//        }
    }

    /*******************************************************************************
     * 从给定的root出发,删除参数2中指定的节点
    *******************************************************************************/
    void Delete(TreeNode<T> *delete_node) {
        if (_root == nullptr) {
            return ;
        }
        _Delete(_root,delete_node);
//        if (_root->_val == delete_node->_val) {
//            TreeNode<T> *tmp_root = new TreeNode<T>;
//            tmp_root->_left = _root;
//            _Delete(tmp_root,delete_node);
//            _root = tmp_root->_left;
//            delete tmp_root;
//            return;
//        }
//        else {
//            _Delete(_root,delete_node);
//            return;
//        }

    }
    TreeNode<T>* Search(T data){
        return _Search(_root,data);
    }
    int GetDeep(){
        return _GetDeep(_root);
    }
    void PreOrderTraversal(){
        _PreOrderTraversal(_root);
    }
    void LnOrderTraversal(){
        _LnOrderTraversal(_root);
    }
    void PostOrderTraversal(){
        _PostOrderTraversal(_root);
    }
    void Destroy(){
        _Destroy(_root);
        _root = nullptr;
    }
    ~BinaryTree(){
        Destroy();
    }




};


template<typename T>
TreeNode<T>* _Insert(TreeNode<T> *root,T data){
    // 插在左子树上
    if(data->GetVal() < root->_val->GetVal()){
        if(root->_left == nullptr){
            TreeNode<T> *node = new TreeNode<T>(data);
            root->_left = node;
            node->_left = node->_right = nullptr;
            node->_parent = root;
            return node;
        }
        else{
            return _Insert(root->_left,data);
        }
    }
    /* root->val <= data */
    // 插在右子树上
    else{
        if(root->_right == nullptr){
            TreeNode<T> *node = new TreeNode<T>(data);
            root->_right = node;
            node->_left = node->_right = nullptr;
            node->_parent = root;
            return node;
        }
        else{
            return _Insert(root->_right,data);
        }
    }

}

template<typename T>
void GetInorder(std::vector<T>&vec,TreeNode<T> *root){
    if(root->_left != nullptr){
        GetInorder(vec,root->_left);
    }
    vec.push_back(root->_val);
    if(root->_right != nullptr){
        GetInorder(vec,root->_right);
    }
}

inline int MAX(int a,int b){
    return a > b ? a : b;
}
template<typename T>
int _GetDeep(TreeNode<T> *root){
    if(root == nullptr)
        return 0;
    return MAX(_GetDeep(root->_left), _GetDeep(root->_right)) + 1;
}
template<typename T>
void _PreOrderTraversal(TreeNode<T> *root){
    if(root == nullptr)
        return;
    std::cout << root->_val << " ";
    _PreOrderTraversal(root->_left);
    _PreOrderTraversal(root->_right);
}

template<typename T>
void _LnOrderTraversal(TreeNode<T> *root){
    if(root == nullptr)
        return;

    _LnOrderTraversal(root->_left);
    std::cout << root->_val << " ";
    _LnOrderTraversal(root->_right);

}
template<typename T>
void _PostOrderTraversal(TreeNode<T> *root){
    if(root == nullptr)
        return;
    _PostOrderTraversal(root->_left);
    _PostOrderTraversal(root->_right);
    std::cout << root->_val << " ";
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
