#include <iostream>
//практика доделать дома
//template<class T>
//struct Point {
//    T x = 0, y = 0;
//};
//template<class T>
//struct List {
//    Point point;
//    List* next;
//};
//template<class T>
//List<T>* task1(List<T>* head, Point<T>p, T e)
//{
//    List<T>* l = head;
//    while (head) {
//        x = head->point.x - p.x;
//        y = head->point.y - p.y;
//        if (sqrt(pow(x, 2) + pow(y, 2)) < e) {
//            l->point.x = head->point.x;
//            l->point.y = head->point.y;
//            l = l->next;
//        }
//        head = head->next;
//    }
//    return l;
//}
//template<class T>
//List<T>* task1(List<T>* head)
//{
//    T len = 0, m = 0;
//    List<T>* l = head->next;
//    List<T>* new_list = new List<T>;
//    while (head) {
//        while (l) {
//            x = head->point.x - l->point.x;
//            y = head->point.y - l->point.y;
//            m = sqrt(pow(x, 2) + pow(y, 2));
//            if ( m > len) {
//                len = m;
//                new_list->point.x = head->point.x;
//                new_list->point.y = head->point.y;
//                new_list->next->point.x = l->point.x;
//                new_list->next->point.y = l->point.y;
//            }
//            l = l->next;
//        }
//        head = head->next;
//        l = head->next;
//    }
//    return new_list;
//}
//
//
////дз: "вставка в упорядоченный список с сохранением порядка"
//template<class T>
//struct List {
//    T data;
//    List* next;
//};
//template<class T>
//List<T>* task(List<T>* head, T data) {
//    List<T>* pre = head;
//    List<T>* new_head = head;
//    head = head->next;
//    List<T>* tmp = new List<T>;
//    tmp->data = data;
//    while (pre)
//    {
//        if (data < pre->data) {
//            tmp->next = pre;
//            return tmp;
//        }
//        if (data >= pre->data && data <= head->data) {
//            pre->next = tmp;
//            tmp->next = head;     
//            return new_head;
//        }
//        if (head->next == NULL && data >= pre->data)
//        {
//            pre->next = tmp;
//            tmp->next = NULL;
//            return new_head;
//        }
//        pre = pre->next;
//        head = head->next;
//    }
//    return new_head;
//}
//


//дз: "проверьте связный список на симметричность", но уже не двусвязный
template<class T>
struct List {
    T data;
    List* next;
};
template<class T>
bool task(List<T>* head) {
    List<T>* list = head;
    List<T>* l = head;
    int n = 0;
    while (l) {
        n++;
    }
    T* mass = new T[n];
    int i = 0;
    while (list) {
        mass[i] = list->data;
        list = list->next;
        i++;
    }
    i--;
    for (int j = 0; ; j++, i--) {
        if (mass[j] != mass[i]) return false;
        if ((j + 1 == i && i - 1 == j) || j == i) return true;
    }
}

int main()
{
    std::cout << "Hello World!\n";
}

