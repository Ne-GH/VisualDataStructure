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
    TreeNode *parent_ = nullptr;

    TreeNode *left_ = nullptr;
    TreeNode *right_ = nullptr;
    bool modify_flag_ = false;
    int height_ = 0;
    T val_ = 0;
    TreeNode() {  }
    TreeNode(T val) {
        val_ = val;
        height_ = 1;
    }
    friend std::ostream & operator << (std::ostream &out,TreeNode node){
        out << node.val_;
        return out;
    }
    friend std::ostream & operator << (std::ostream &out,TreeNode *pnode){
        out << pnode->val_;
        return out;
    }
    ~TreeNode() {
        parent_ = nullptr;
        left_ = right_ = nullptr;
        modify_flag_ = false;
//        if (val_ != nullptr) {
//            delete val_;
//        }
        val_ = nullptr;
    }

};


template<typename T>
TreeNode<T> *Build(int left,int right,std::vector<T>& vec){
    int mid = (left + right) >> 1;
    TreeNode<T> *root = new TreeNode<T>(vec[mid]);
    if(left <= mid - 1){
        root->left_ = Build(left,mid - 1,vec);
    }
    if(mid + 1 <= right){
        root->right_ = Build(mid + 1,right,vec);
    }
    return root;
}


template <typename T>
auto GetVal(T node) {
    if constexpr (std::is_same_v<T,TreeNode<GraphicsItem *> *>) {
        return node->val_->GetVal();

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
    auto tmp = root->right_;
    root->right_ = tmp->left_;
    if (tmp->left_) {
        tmp->left_->parent_ = root;
    }
    tmp->left_ = root;
    tmp->parent_ = root->parent_;
    root->parent_ = tmp;
    root->height_ = GetDeep_(root);
    tmp->height_ = GetDeep_(tmp);
    return tmp;
}

template<typename T>
TreeNode<T> *RotateRight(TreeNode<T>* root) {
    auto tmp = root->left_;
    root->left_ = tmp->right_;
    if (tmp->right_) {
        tmp->right_->parent_ = root;
    }
    tmp->right_ = root;
    tmp->parent_ = root->parent_;
    root->parent_ = tmp;
    root->height_ = GetDeep_(root);
    tmp->height_ = GetDeep_(tmp);
    return tmp;
}

template<typename T>
TreeNode<T> *RotateLeftRight(TreeNode<T>* root) {
    root->left_ = RotateLeft(root->left_);
    return RotateRight(root);
}

template<typename T>
TreeNode<T> *RotateRightLeft(TreeNode<T>* root) {
    root->left_ = RotateRight(root->left_);
    return RotateLeft(root);
}


template<typename T>
TreeNode<T>* insert(TreeNode<T> *parent,TreeNode<T> *root,TreeNode<T> *data) {
    if (root == nullptr) {
        data->parent_ = parent;
//        if (parent) {
//            parent->modify_flag_ = true;
//        }
        return data;
    }
    // 插入到左子树
    if (GetVal(data) < GetVal(root)) {
        root->left_ = insert(root,root->left_,data);
        root->height_ = GetDeep_(root);
        if (GetDeep_(root->left_) - GetDeep_(root->right_) == 2) {
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
        root->right_ = insert(root,root->right_,data);
        root->height_ = GetDeep_(root);

        if (GetDeep_(root->left_) - GetDeep_(root->right_) == -2) {
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
    TreeNode<T> *root_ = nullptr;
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
            fillStack(node->right_);
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
                node = node->left_;
            }
        }
    };
public:
    BinaryTree() {  }
    BinaryTree(T data){
        root_ = new TreeNode<T>(data);
    }
    TreeNode<T> *GetRoot() {
        return root_;
    }

    TreeNode<T>* Insert(T data){
        if(root_ == nullptr){
            root_ = new TreeNode<T>(data);
            return root_;
        }
        else{
//            return _Insert(root_,data);
            TreeNode<T> *node = new TreeNode<T>(data);
            root_ = insert(root_->parent_,root_,node);
            return node;
        }
    }



    /*******************************************************************************
     * 从给定的root出发,删除参数2中指定的节点
    *******************************************************************************/
    void Delete(TreeNode<T> *delete_node) {
        if (root_ == nullptr) {
            return ;
        }
        Delete_(root_,delete_node);
    }
    TreeNode<T>* Search(T data){
        return _Search(root_,data);
    }
    int GetDeep(){
        return GetDeep_(root_);
    }
    int GetWidth() {
        if(root_ == nullptr) 
            return 0;
        int max = 0; //树的最大宽度 
        std::queue<TreeNode<T> *> que;
        que.push(root_);
        while(!que.empty()){
            int width = que.size(); //本层宽度 
            for(int i = 0;i < width;i++){
                TreeNode<T>* tmp = que.front();
                que.pop();
                if(tmp->left_) que.push(tmp->left_);
                if(tmp->right_) que.push(tmp->right_);
            }
            max = max > width ? max : width; //宽度更新 
        }
        return max;
    }

    void Destroy(){
        Destroy_(root_);
        root_ = nullptr;
    }
    ~BinaryTree(){
        Destroy();
    }
    bool Empty() {
        return root_ == nullptr;
    }
    auto begin() {
        return iterator(root_);

    }
    auto end() {
        return iterator(nullptr);
    }

};



inline int MAX(int a,int b){
    return a > b ? a : b;
}
template<typename T>
int GetDeep_(TreeNode<T> *root){
    if(root == nullptr)
        return 0;
    return MAX(GetDeep_(root->left_), GetDeep_(root->right_)) + 1;
}

/* 带头节点一起销毁 */
template<typename T>
void Destroy_(TreeNode<T> *root){

    if(root == nullptr){
        return;
    }
    Destroy_(root->left_);
    Destroy_(root->right_);
    return;
}
template<typename T>
TreeNode<T>* _Search(TreeNode<T> *root,T data){
    if(root == nullptr)
        return nullptr;
    if(root->val_ == data){
        return root;
    }
    else if(root->val_ > data){
        return _Search(root->left_,data);
    }
    else {
        return _Search(root->right_,data);
    }
}
template <typename T>
TreeNode<T> *Delete_(TreeNode<T> *root,TreeNode<T> *delete_node) {
    if (root == nullptr) {
        return nullptr;
    }

    if (root->val_ == delete_node->val_) {
        if (root->left_ == nullptr) {
            TreeNode<T> *newroot_ = root->right_;
            if (newroot_ != nullptr) {
                newroot_->parent_ = root->parent_;
                if (newroot_->parent_ != nullptr) {
                    newroot_->parent_->modify_flag_ = true;
                }
            }
            delete root;
            return newroot_;
        }
        else if (root->right_ == nullptr) {
            TreeNode<T> *newroot_ = root->left_;
            if (newroot_ != nullptr) {
                newroot_->parent_ = root->parent_;
                if (newroot_->parent_ != nullptr) {
                    newroot_->parent_->modify_flag_ = true;
                }
            }
            delete root;
            return newroot_;
        }
        else {
            // 找到右边的最小值
            TreeNode<T> *minright_ = root->right_;
            while (minright_->left_) {
                minright_ = minright_->left_;
            }
            // 将最小值赋值给root,并去右子树删除该最小值
            root->val_ = minright_->val_;
            root->modify_flag_ = true;
            root->right_ = Delete_(root->right_, minright_);
        }
    }
    else if (root->val_->GetVal() > delete_node->val_->GetVal()) {
        root->left_ = Delete_(root->left_, delete_node);
    }
    else {
        root->right_ = Delete_(root->right_, delete_node);
    }
    return root;
}



}
#endif
