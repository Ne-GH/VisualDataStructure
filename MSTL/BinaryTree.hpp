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
    void Delete(TreeNode<T>* root,TreeNode<T> *delete_node) {
        if (root == nullptr)
            return ;
        auto parent = root->GetParent();
        bool is_root = false;
        bool is_left = false;
        bool is_right = false;
        // 没有父节点,意味着当前删除的是根节点
        if (parent == nullptr) {
            is_root = true;
        }
        else {
            auto parent_val = parent->_val.GetVal();
            auto cur_val = root->_val.GetVal();
            if (cur_val < parent)
                is_left = true;
            else
                is_right = true;
        }

        // 当前节点是需要被删除的节点
        if (root == delete_node) {
            // 左右子树均存在
            if (root->_left && root->_right) {
                auto right_down_nodw = GetRightDownNode(root->_left);
                right_down_nodw->_right = root->_right;
                root->_right->_parent = right_down_nodw;

                if (parent && is_left) {
                    parent->_left = root->_left;
                    root->_left->_parent = parent;
                }
                else if (parent && is_right) {
                    parent->_right = root->_left;
                    root->_left->_parent = parent;
                }
            }
            // 只有左子树
            else if (root->_left) {
                if (parent && is_left) {
                    parent->_left = root->_left;
                    root->_left->_parent = parent;
                }
                else if (parent && is_right) {
                    parent->_right = root->_left;
                    root->_left->_parent = parent;

                }
            }
            // 只有右子树
            else if (root->_right){
                if (parent && is_left) {
                    parent->_left = root->_right;
                    root->_right->_parent = parent;
                }
                else if (parent && is_right) {
                    parent->_right = root->_right;
                    root->_right->_parent = parent;
                }

            }
            // 叶子节点
            else {
                if (parent && is_left) {
                    parent->_left = nullptr;
                }
                else if (parent && is_right) {
                    parent->_right = nullptr;
                }
            }


        }
        if (root->_left) {
            Delete(root->_left,delete_node);
        }
        if (root->_right) {
            Delete(root->_right,delete_node);
        }

    }
    void Delete(T data){
        if(_root->_val == data){
            TreeNode<T> *tmproot = new TreeNode<T>;
            tmproot->_left = _root;
            _Delete(tmproot,data);
            _root = tmproot->_left;
            delete tmproot;
            return;
        }
        else{
            _Delete(_root,data);
            return;
        }
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

    void Draw(){
        _output(_root);
    }


    TreeNode<T> *Root(){
        return _root;
    }

    friend std::ostream & operator << (std::ostream &out,BinaryTree * bt){
        out << bt->_val;
        return out;
    }

    /* 使用额外的数组进行平衡 */
    void BalanceBinaryTree(){
        std::vector<T> vec;
        GetInorder(vec,_root);

        TreeNode<T> *root = Build(0,vec.size()-1,vec);
        this->Destroy();
        _root = new TreeNode<T>;
        _root = root;
        return;
    }

};



template<typename T>
TreeNode<T>* _Insert(TreeNode<T> *root,T data){
    if(root->_val->GetVal() > data->GetVal()){
        if(root->_left == nullptr){
            TreeNode<T> *node = new TreeNode<T>(data);
            root->_left = node;
            node->_left = node->_right = nullptr;
            node->_parent = root;
            std::cout << node->_val->GetVal() << " " << root->_val->GetVal() << std::endl;
            return node;
        }
        else{
            return _Insert(root->_left,data);
        }
    }
        /* root->val <= data */
    else{
        if(root->_right == nullptr){
            TreeNode<T> *node = new TreeNode<T>(data);
            root->_right = node;
            node->_left = node->_right = nullptr;
            node->_parent = root;
            std::cout << " " << node->_val->GetVal() << " " << root->_val->GetVal() << std::endl;
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
template<typename T>
void _Delete(TreeNode<T>* root,T data){
    if(root == nullptr)
        return;
    if(root->_left != nullptr && root->_left->_val == data){
        if(root->_left->_left){
            TreeNode<T> *p = root->_left->_left;
            delete root->_left;
            root->_left = p;
        }
        else if(root->_left->_right){
            TreeNode<T> *p = root->_left->_right;
            delete root->_left;
            root->_left = p;
        }
        else{
            delete root->_left;
            root->_left = nullptr;
        }

    }
    if(root->_right != nullptr && root->_right->_val == data){
        if(root->_right->_left){
            TreeNode<T> *p = root->_right->_left;
            delete root->_right;
            root->_right = p;
        }
        else if(root->_right->_right){
            TreeNode<T> *p = root->_right->_right;
            delete root->_right;
            root->_right = p;
        }
    }
    _Delete(root->_left,data);
    _Delete(root->_right,data);

}

template<typename T>
void _output_impl(TreeNode<T> *root, bool left, std::string const& indent){
    if (root->_right){
        _output_impl(root->_right, false, indent + (left ? "|     " : "      "));
    }
    std::cout << indent;
    std::cout << (left ? '\\' : '/');
    std::cout << "-----";
    std::cout << root->_val << std::endl;
    if (root->_left){
        _output_impl(root->_left, true, indent + (left ? "      " : "|     "));
    }
}
template<typename T>
void _output(TreeNode<T>* root) {
    if (root->_right) {
        _output_impl(root->_right, false, "");
    }
    std::cout << root->_val << std::endl;
    if (root->_left) {
        _output_impl(root->_left, true, "");
    }
}
}
#endif
