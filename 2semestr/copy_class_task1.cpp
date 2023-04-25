#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include<vector>
using namespace std::chrono;
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
            return insert_leaf(head->left, val);
        else if (val > head->data)
            return insert_leaf(head->right, val);
        else if (head->data == val)
        {
            
            if (head->right == NULL)
            {
                head->right = new Leaf;
                head->right->data = val;
                head->right->left = head->right->right = NULL;
                return true;
            }
            if (head->left != NULL && head->right != NULL)
                return false;
        }

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
            std::cout << (isLeft ? "ÃÄÄ" : "ÀÄÄ");

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
    Leaf* erase_leaf(Leaf* head, int val) {
        if (!head) return head;
        else if (val < head->data) head->left = erase_leaf(head->left, val);
        else if (val > head->data) head->right = erase_leaf(head->right, val);
        else {
            if (!head->left && !head->right) {
                delete head;
                head = NULL;
            }
            else if (!head->left) {
                Leaf* tmp = head;
                head = head->right;
                delete tmp;
            }
            else if (!head->right) {
                Leaf* tmp = head;
                head = head->left;
                delete tmp;
            }
            else {
                Leaf* tmp = minimum(head->right);
                head->data = tmp->data;
                head->right = erase_leaf(head->right, tmp->data);
            }
        }
        return head;
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
    if (!contains(x)) return false;
    root = erase_leaf(root, x);
    return true;
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
    cout << "2. Ñalculate the average time" << endl;
    cout << "3. Make a task according to the option" << endl;
    cout << "choice: ";
}
bool find_elem(std::vector<int>& vec, int elem)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == elem)
            return true;
    }
    return false;
}
size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}
void fill_tree(int n, int cycles)
{
    double result = 0;
    for (int i = 0; i < cycles; i++)
    {
        Tree test;
        auto start = high_resolution_clock::now();
        for (int j = 0; j < n; j++)
        {
            test.insert(lcg());
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        result += duration.count();
    }
    cout << "filling of binary tree: with " << n << " values and " << cycles << " cycles - " << result / cycles << " microseconds" << endl;
}

void contains_tree(int n, int cycles)
{
    Tree test;
    for (int i = 0; i < n; i++)
    {
        test.insert(lcg());
    }
    long double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        auto start = high_resolution_clock::now();
        test.contains(lcg());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "searching in binary tree: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}

void insert_tree(int n, int cycles)
{
    Tree test;
    for (int i = 0; i < n; i++)
    {
        test.insert(lcg());
    }
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        Tree tmp = test;
        auto start = high_resolution_clock::now();
        tmp.insert(lcg());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "addition in binary tree: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}
void erase_tree(int n, int cycles)
{
    Tree test;
    for (int i = 0; i < n; i++)
    {
        test.insert(lcg());
    }
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        Tree tmp = test;
        auto start = high_resolution_clock::now();
        tmp.erase(lcg());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "deleting in binary tree: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}
void fill_vector(int n, int cycles)
{
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        std::vector<int> test(n);
        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; i++)
        {
            test.push_back(lcg());
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        result += duration.count();
    }
    cout << "filling of vector: with " << n << " values and " << cycles << " cycles - " << result / cycles << " microseconds" << endl;
}

void contains_vector(int n, int cycles)
{
    std::vector<int> test(n);
    for (int i = 0; i < n; i++)
    {
        test.push_back(lcg());
    }
    long double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        auto start = high_resolution_clock::now();
        std::find(test.begin(), test.end(), lcg());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "searching in vector: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}

void insert_vector(int n, int cycles)
{
    std::vector<int> test(n);
    for (int i = 0; i < n; i++)
    {
        test.push_back(lcg());
    }
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        std::vector<int> tmp = test;
        auto start = high_resolution_clock::now();
        tmp.push_back(lcg());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "addition in vector: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
}

void erase_vector(int n, int cycles)
{
    std::vector<int> test(n);
    for (int i = 0; i < n; i++)
    {
        test.push_back(lcg());
    }
    double result = 0;
    for (int j = 0; j < cycles; j++)
    {
        std::vector<int> tmp = test;
        auto start = high_resolution_clock::now();
        tmp.erase(std::remove(tmp.begin(), tmp.end(), lcg()), tmp.end());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        result += duration.count();
    }
    cout << "deleting in vector: with " << n << " values and " << cycles << " cycles - " << result / cycles << " nanoseconds" << endl;
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
                    cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
                    choi = _getch();
                    if (choi == 8) flag2 = true;
                }
            }
        }
        if (choice == 2)
        {
            fill_tree(1000, 100);
            fill_tree(10000, 100);
            fill_tree(100000, 100);
            cout << endl;
            fill_vector(1000, 100);
            fill_vector(10000, 100);
            fill_vector(100000, 100);
            cout << endl;
            cout << endl;
            contains_tree(1000, 1000);
            contains_tree(10000, 1000);
            contains_tree(100000, 1000);
            cout << endl;
            contains_vector(1000, 1000);
            contains_vector(10000, 1000);
            contains_vector(100000, 1000);
            cout << endl;
            cout << endl;
            insert_tree(1000, 1000);
            insert_tree(10000, 1000);
            insert_tree(100000, 1000);
            cout << endl;
            insert_vector(1000, 1000);
            insert_vector(10000, 1000);
            insert_vector(100000, 1000);
            cout << endl;
            cout << endl;
            erase_tree(1000, 1000);
            erase_tree(10000, 1000);
            erase_tree(100000, 1000);
            cout << endl;
            erase_vector(1000, 1000);
            erase_vector(10000, 1000);
            erase_vector(100000, 1000);
            cout << endl << endl;
            cout << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;

        }
        if (choice == 3)
        {
            std::vector<int> myVector = { 1, -3, 2, 7, 11, 63, 99, 2, 0,0, 7, 1, -2, 99, 88, 73, -42, -2, -2, -3, 19, 0 };
            std::vector<int> new_vector;
            cout << "vector: ";
            for (int i = 0; i < 22; i++)
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
        else if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
        {
            cout << "invalid character entered!!!!!!!    try again" << endl;
            cout << endl << endl << "Press 'Backspace' if want to back" << endl << endl;
            choi = _getch();
            if (choi == 8) flag1 = true;
        }
    }
}