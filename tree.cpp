#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    int color; // 0 - red 1 - black
    TreeNode *right;
    TreeNode *left;
    TreeNode *parent;

    TreeNode(int val, int color) : val(val), color(color) {}
};


class Tree {

public:
    TreeNode *root;
    TreeNode *empty_leaf;

    Tree(int val) {
        empty_leaf = new TreeNode(0, 1);
        empty_leaf->left = NULL;
        empty_leaf->right = NULL;
        root = new TreeNode(val, 1);
        root->left = empty_leaf;
        root->right = empty_leaf;
        root->parent = empty_leaf;
    }

    TreeNode *get_root() {
        return root;
    }

    void right_rotation(TreeNode *node) {
        TreeNode *temp = node->left;
        node->left = temp->right;

        if (empty_leaf != temp->right) {
            temp->right->parent = node;
        }

        temp->parent = node->parent;

        if (node->parent == empty_leaf) {
            this->root = temp;
        } else if (node == node->parent->right) {
            node->parent->right = temp;
        } else {
            node->parent->left = temp;
        }

        temp->right = node;
        node->parent = temp;
    }

    void left_rotation(TreeNode *node) {
        TreeNode *temp = node->right;
        node->right = temp->left;

        if (empty_leaf != temp->left) {
            temp->left->parent = node;
        }

        temp->parent = node->parent;

        if (node->parent == empty_leaf) {
            this->root = temp;
        } else if (node == node->parent->left) {
            node->parent->left = temp;
        } else {
            node->parent->right = temp;
        }

        temp->left = node;
        node->parent = temp;
    }

    void insert_fixer(TreeNode *inserted) {
        while(inserted->parent->color == 0){
            if (inserted->parent == inserted->parent->parent->left){
                TreeNode* uncle = inserted->parent->parent->right;
                if (uncle->color == 0){
                    inserted->parent->color = 1;
                    uncle->color = 1;
                    inserted->parent->parent->color = 0;
                    inserted = inserted->parent->parent;
                }
                else{
                    if(inserted == inserted->parent->right){
                        inserted = inserted->parent;
                        left_rotation(inserted);
                    }
                    inserted->parent->color = 1;
                    inserted->parent->parent->color = 0;
                    right_rotation(inserted->parent->parent);
                }
            }
            else{
                TreeNode* uncle = inserted->parent->parent->left;
                if (uncle->color == 0){
                    inserted->parent->color = 1;
                    uncle->color = 1;
                    inserted->parent->parent->color = 0;
                    inserted = inserted->parent->parent;
                }
                else{
                    if(inserted == inserted->parent->left){
                        inserted = inserted->parent;
                        right_rotation(inserted);
                    }
                    inserted->parent->color = 1;
                    inserted->parent->parent->color = 0;
                    left_rotation(inserted->parent->parent);
                }
            }

        }
        this->root->color = 1;
    }

    void insert(TreeNode *root, int to_insert) {
        TreeNode *node_to_insert = new TreeNode(to_insert, 0);
        node_to_insert->left = empty_leaf;
        node_to_insert->right = empty_leaf;
        node_to_insert->parent = NULL;

        if (root->left == empty_leaf && root->right == empty_leaf) {
            if (to_insert > root->val) {
                root->right = node_to_insert;
                node_to_insert->parent = root;
                insert_fixer(node_to_insert);
                return;
            } else {
                root->left = node_to_insert;
                node_to_insert->parent = root;
                insert_fixer(node_to_insert);
                return;
            }
        }

        if (root->val < to_insert) {
            if (root->right == empty_leaf) {
                root->right = node_to_insert;
                node_to_insert->parent = root;
                insert_fixer(node_to_insert);
                return;
            } else {
                insert(root->right, to_insert);
                return;
            }
        }

        if (root->val > to_insert) {
            if (root->left == NULL) {
                root->left = node_to_insert;
                node_to_insert->parent = root;
                insert_fixer(node_to_insert);
                return;
            } else {
                insert(root->left, to_insert);
                return;
            }
        }
    }

    bool finder(int to_find){
        return finder_under(this->getRoot(), to_find);
    }


    bool finder_under(TreeNode* tree, int to_find){
        if (tree == empty_leaf){return false;}

        if (tree->val == to_find){return true;}

        if (finder_under(tree->left, to_find) || finder_under(tree->right, to_find)){return true;}

        return false;
    }

    //вспомогательное говно
    TreeNode *getRoot() {
        return this->root;
    }
    string getString(TreeNode *tree) {
        std::string leftInorder = tree->left != nullptr ? getString(tree->left) : "";
        std::string rightInorder = tree->right != nullptr ? getString(tree->right) : "";
        if (leftInorder.length() > 0) {
            leftInorder = "(" + leftInorder + ") ";
        }
        if (rightInorder.length() > 0) {
            rightInorder = " (" + rightInorder + ")";
        }
        return leftInorder + std::to_string(tree->val) + rightInorder;
    }
};

TreeNode *buildTree() {
    int numberOfNums;
    int currentNumber;

    cin >> numberOfNums;
    cin >> currentNumber;

    Tree tree(currentNumber);
    TreeNode *root = tree.get_root();

    for (int i = 1; i < numberOfNums; i++) {
        cin >> currentNumber;
        tree.insert(root, currentNumber);
    }

    cout << tree.getString(tree.getRoot()) << endl;
//    cout << tree.finder(2) << endl;
//    cout << tree.finder(222) << endl;
//    cout << tree.finder(1) << endl;
    return root;
}

int main() {
    TreeNode *root = buildTree();
    return 0;
}