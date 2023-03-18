//Класс должен предоставлять, как минимум, следующие функции :
//
//конструктор копирования;
//деструктор;
//оператор присваивания;
//void print() – печать содержимого;
//bool insert(int key) – вставка элемента;
//bool contains(int key) - проверка наличия элемента;
//bool erase(int key) – удаление элемента;

//     1 блок
//1. создать дерево
//2. рассчитать  среднее время...
//3. задание по варианту
//     2.1 блок
//1. добавить узел
//2. удалить узел
//3. печать дерева
//4. найти элемент
//     2.2 блок
//расчитать время
//     2.3 блок
//создание вектора и дерева
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <conio.h>
#include <vector>

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
        if (node != nullptr)
        {
            std::cout << prefix;
            std::cout << (isLeft ? "ГДД" : "АДД");

            std::cout << node->data << std::endl;
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
            if (!head->left && !head->right) 
            {
                delete head;
                head = NULL;
                return true;
            }
            else if (!head->left) 
            {
                Leaf* leaf = head;
                head = head->right;
                delete head;
                return true;
            }
            else if (!head->right) 
            {
                Leaf* leaf = head;
                head = head->left;
                delete head;
                return true;
            }
            Leaf* leaf = minimum(head->right);
            head->data = leaf->data;
            erase_leaf(head->right, leaf->data);
            return true;
        }
    }
    void clear(Leaf*& head) 
    {
        if (!head) return;
        clear(head->left);
        clear(head->right);
        delete head;
    }
    void copy(Leaf* a, const Leaf* b) 
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
    Tree(); 
    Tree(const Tree&);
    ~Tree();
    bool insert(int);
    bool contains(int x); 
    bool erase(int x); 
    void print(); 
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
Tree::Tree(const Tree& a)
{
    copy(root, a.root);
}
bool Tree::insert(int x)
{
    return insert_leaf(root, x);
}
Tree::~Tree()
{
    clear(root);
}
void Tree::print()
{
    print_leaf("", root, false);
    cout << endl;
}
bool Tree::contains(int x)
{
    return contains_leaf(root, x);
}
bool Tree::erase(int x) {
    if (contains(x) == true) return false;
    return erase_leaf(root, x);
}
void menu1()
{
    system("cls");
    cout << "1. Create a binary search tree" << endl;
    cout << "2. Calculate the average time" << endl;
    cout << "3. Make a task according to the option" << endl;
    cout << "4. Finish the program" << endl;
    cout << "choice: ";
}
void menu2_1()
{
    system("cls");
    cout << "1. add a node" << endl;
    cout << "2. delete a node" << endl;
    cout << "3. print a binary tree " << endl;
    cout << "4. find the specified node " << endl;
    cout << "5. back main menu " << endl;
    cout << "choice: ";
}
void menu2_3()
{
    cout << "1. Create binary search tree" << endl;
    cout << "2. Сalculate the average time" << endl;
    cout << "3. Make a task according to the option" << endl;
    cout << "choice: ";
}
bool find_elem(std:: vector<int>& vec, int elem)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == elem)
            return true;
    }
    return false;
}
int main() {
    Tree head;
    int choice = 0, ch = 0, choi = 0, val = 0;

    bool flag1 = true, flag2 = true;
    while (flag1)
    {
        menu1();
        cin >> choice;
        if (choice == 1)
        {
            flag2 = true;
            while (flag2)
            {
                menu2_1();
                cin >> ch;
                if (ch == 1)
                {
                    cout << "value: ";
                    cin >> val;
                    if (head.insert(val)) cout << "value added successfully" << endl;
                    else cout << "this value is already in the tree" << endl;
                    cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
                else if (ch == 2)
                {
                    cout << "value: ";
                    cin >> val;
                    if (head.erase(val)) cout << "value deleted successfully" << endl;
                    else cout << "there is no such value in the tree" << endl;
                    cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
                else if (ch == 3)
                {
                    head.print();
                    cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
                else if (ch == 4)
                {
                    cout << "value: ";
                    cin >> val;
                    if (head.contains(val)) cout << "this element is present in the tree" << endl;
                    else cout << "this element is not present in the tree" << endl;
                    cout << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
                else if (ch == 5) 
                {
                    flag2 = false;
                }
                else
                {
                    cout << "invalid character entered!!!!!!!    try again" << endl;
                    cout << endl<< endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
            }
        }
        if (choice == 2) { cout << 1; }
        if (choice == 3) 
        {
            std::vector<int> myVector = {1, -3, 2, 7, 11, 63, 99, 2, 0, 7, 1, -2, 99, 88, 73, -42, -2, -2, -3, 19, 0};
            std::vector<int> new_vector;
            cout << "vector: ";
            for (int i = 0; i < 21; i++)
            {
                if (head.insert(myVector[i]) == false && find_elem(new_vector, myVector[i]) == false)
                {
                    new_vector.push_back(myVector[i]);
                }
                cout << myVector[i] << "; ";
            }
            cout << endl;
            cout << "new vector: ";
            for (int i = 0; i < new_vector.size(); i++)
            {
                cout << new_vector[i] << "; ";
            }
            cout << endl;
            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;

        }
        if (choice == 4) return 0;
        else if(choice != 1 && choice != 2 && choice != 3 && choice != 4)
        {
            cout << "invalid character entered!!!!!!!    try again" << endl;
            cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;
        }
    }
}
//поправить удаление, печать