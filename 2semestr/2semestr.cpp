//Класс должен предоставлять, как минимум, следующие функции :
//
//конструктор копирования;
//деструктор;
//оператор присваивания;
//void print() – печать содержимого;
//bool insert(int key) – вставка элемента;
//bool contains(int key) - проверка наличия элемента;
//bool erase(int key) – удаление элемента;
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
using namespace std;
struct Leaf {
    int data;
    Leaf* left;
    Leaf* right;
};
class Tree
{
private:
    Leaf* root;
    bool insert_leaf(Leaf*& head, int val)
    {
        if (!head)
        {
            head = new Leaf;
            head->data = val;
            head->left = head->right = NULL;
            return true;
        }
        else if (val < head->data)
            insert_leaf(head->left, val);
        else if (val > head->data)
            insert_leaf(head->right, val);
        else
            return false;
    }
    bool contains_leaf(const Leaf* head, int val)
    {
        if (!head)
            return false;
        else if (val < head->data)
            return contains_leaf(head->left, val);
        else if (val > head->data)
            return contains_leaf(head->right, val);
        else
            return true;
    }
    void print_leaf(const std::string& prefix, const Leaf* node, bool isLeft)
    {
        if (node)
        {
            std::cout << prefix;

            //std::cout << (isLeft ? "├──" : "└──");
            std::cout << (isLeft ? "|: " : "|: ");

            // print the value of the node
            std::cout << node->data << std::endl;

            // enter the next tree level - left and right branch
            print_leaf(prefix + (isLeft ? "|   " : "    "), node->left, true);
            print_leaf(prefix + (isLeft ? "|   " : "    "), node->right, false);
        }
    }
    Leaf* minimum(Leaf* head)
    {
        while (head->left) head = head->left;
        return head;
    }
    bool erase_leaf(Leaf* head, int val) {
        if (!head) return false;
        if (val < head->data)
            erase_leaf(head->left, val);
        else if (val > head->data)
            erase_leaf(head->right, val);
        else {
            if (!head->left) {
                Leaf* leaf = head->right;
                delete head;
                return true;
            }
            else if (!head->right) {
                Leaf* leaf = head->left;
                delete head;
                return true;
            }
            Leaf* leaf = minimum(head->right);
            head->data = leaf->data;
            erase_leaf(head->right, leaf->data);
            return true;
        }
    }
    void clear(Leaf*& head) //+
    {
        if (!head) return;
        clear(head->left);
        clear(head->right);
        delete head;
    }
    void copy(Leaf* a, const Leaf* b) //+
    {
        if (!a)
        {
            b = NULL;
            return;
        }
        a = new Leaf;
        a->data = b->data;
        copy(a->left, b->left);
        copy(a->right, b->right);
    }
public:
    Tree(); //+
    Tree(const Tree&); //+
    ~Tree();//+
    bool insert(int);//+
    bool contains(int x); //+
    bool erase(int x); //+
    void print(); //+
    Tree& operator=(const Tree& src);
};
Tree::Tree() :root(NULL) {}
Tree& Tree::operator=(const Tree& tmp)
{
    if (this == &tmp) return *this;
    if (!tmp.root) clear(root);
    copy(root, tmp.root);
    return *this;
}
Tree::Tree(const Tree& a)//+
{
    copy(root, a.root);
}
bool Tree::insert(int x) //+
{
    return insert_leaf(root, x);
}
Tree::~Tree() //+
{
    clear(root);
}
void Tree::print() //+
{
    print_leaf("", root, false);
    cout << endl;
}
bool Tree::contains(int x) //+
{
    return contains_leaf(root, x);
}
bool Tree::erase(int x) {
    if (contains(x) == true) return false;
    return erase_leaf(root, x);
}


int main() {
    Tree t;
    int choise = 0;

    t.insert(20);
    t.insert(24);
    t.insert(19);
    t.insert(21);
    t.insert(18);
    t.insert(22);
    t.print();
    return 0;
}