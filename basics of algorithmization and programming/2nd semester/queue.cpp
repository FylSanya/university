#include <iostream>
#include <ctime>
 
using namespace std;
 
struct queue {
    int info;
    queue* next, * prev;
};
 
void create(queue**, queue**);
void addBegin(queue*, int);
void addEnd(queue*, int);
void del(queue*);
void viewBegin(queue*);
void viewEnd(queue*);
void delQueue(queue*);
int min(queue*, int size);
int choice();
int max(queue* b, int size);
void delete_min_max(queue* b, int min, int max, int size);
 
void main() {
    setlocale(LC_ALL, "Russian");
    int n;
    queue* begin = nullptr;
    queue* end = nullptr;
    int minimum, maximum;
   
    create(&begin, &end);
 
    int size;
    cout << "Размер очереди: ";
    cin >> size;
 
    srand(time(0));
   
    bool exit = true;
    while (exit) {
        int menu;
        cout << "\nДля создания очереди нажмите 1 \nДля его просмотра нажмите 2 \nДля нахождения минимального элемента нажмите 3 \nДля очистки памяти нажмите 4 \n";
        cin >> menu;
        switch (menu) {
        case 1: //создание очереди
            for (int i = 0; i < size; i++) {
                n = rand() % 101 - 50;
                addBegin(begin, n);
            }
            break;
        case 2: //просмотр
            switch (choice()) {
            case 1:
                viewBegin(begin);
                break;
            case 2:
                viewEnd(end);
                break;
            default:
                cout << "эээ ежжи не та цифра";
                break;
            }
            break;
        case 3: // поиск минимального и максимального + удаление элементов между ними
            minimum = min(begin, size);
            maximum = max(begin, size);
            delete_min_max(begin, minimum, maximum, size);
            break;
        case 4: // очистка памяти
            delQueue(begin);
            break;
        case 5: //exit
            exit = false;
            break;
        default:
            cout << "эээ ежжи не та цифра";
            break;
        }
    }
}
 
void create(queue **b, queue **e) { // список у нас каркасный, то бишь бегин и энд никогда не меняются
    *b = new queue;
    (*b)->prev = nullptr;
    *e = new queue;
    (*e)->next = nullptr;
    (*b)->next = *e;
    (*e)->prev = *b;
}
 
void addBegin(queue *b, int inf){
    queue* n = new queue;
    n->info = inf;
    n->prev = b;
    n->next = b->next;
    (b->next)->prev = n;
    b->next = n;
}
 
void addEnd(queue *e, int inf) {
    queue* n = new queue;
    n->info = inf;
    n->next = e;
    n->prev = e->prev;
    (e->prev)->next = n;
    e->prev = n;
}
 
void del(queue *el) {
    (el->prev)->next = el->next;
    (el->next)->prev = el->prev;
    delete(el);
}
 
void viewBegin(queue* b) {
    queue* n = new queue;
    n = b;
    n = n->next;
    while (n->next != nullptr) {
        cout << n->info << " ";
        n = n->next;
    }
}
 
void viewEnd(queue* e) {
    queue* n = new queue;
    n = e;
    n = n->prev;
    while (n->prev != nullptr) {
        cout << n->info << " ";
        n = n->prev;
    }
}
 
int choice() {
    int answer;
    cout << "С начала (1) или с конца (2)?\n";
    cin >> answer;
    return answer;
}
 
void delQueue(queue* b) {
    queue* n = new queue;
    while (b != nullptr) {
        n = b;
        b->info = 0;
        b = b->next;
        delete(n);
    }
}
 
 
int min(queue* b, int size) {
    int i_temp;
    queue* temp = b;
    queue* tempDel = nullptr;
    temp = temp->next;
    int minimum = temp->info;
    for (int i = 0; i < size; i++) {
        if (temp->info <= minimum) {
            minimum = temp->info;
            tempDel = temp;
            i_temp = i;
        }
        if (temp->next != nullptr) temp = temp->next;
    }
    cout << minimum << "\n";
 
    return i_temp;
}
 
int max(queue* b, int size) {
    int i_temp;
    queue* temp = b;
    queue* tempDel = nullptr;
    temp = temp->next;
    int maximum = temp->info;
    for (int i = 0; i < size; i++) {
        if (temp->info >= maximum) {
            maximum = temp->info;
            tempDel = temp;
            i_temp = i;
        }
        if (temp->next != nullptr) temp = temp->next;
    }
    cout << maximum << "\n";
 
    return i_temp;
}
 
 
void delete_min_max(queue* b, int min, int max, int size) {
    queue* temp = b->next; // темп = первый элемент в списке
    queue* del_temp = temp; // вторая темпуха для удаления
    for (int i = 0; i <= size; i++) { // проходимся по списку
        if (i == min || i == max) { // если находим мин или мак, то удаляем элементы между
            for (i; i < max -1 || i < min - 1; i++) { // -1 чтобы не захватывало лишнего
                del_temp = temp;
                temp = temp->next;
                del(del_temp);
            }
        }
        temp = temp->next;
    }
}
