#include <iostream>

using namespace std;

struct stack {
	int inf;
	stack* next;
};

stack* add(stack*, int);
void view(stack*);
void delst(stack*);


void main(){
	int n, number;
	stack* topall=nullptr;
	stack* topnegative = nullptr;

	cout << "Size of stack:\n";
	cin >> n;

	cout << "Enter numbers:\n";
	for (int i=0; i < n; i++) {
		cin >> number;
		topall = add(topall, number);
	}

	topall = add(topall, 0);
	stack* temp = topall;
	while (topall->next != nullptr)
	{
		if (topall->next->inf < 0)
		{
			topnegative = add(topnegative, topall->next->inf);

			stack* tmp = topall->next;
			topall->next = tmp->next;
			delete(tmp);
		}
		else topall = topall->next;
	}

	topall = temp;
	topall = topall->next;
	delete temp;

	view(topall);
	view(topnegative);

	delst(topall);
	delst(topnegative);
}


stack* add(stack* top, int info) { //добавить в стэк элемент
	stack* p = new stack;
	p->next = top;
	p->inf = info;
	return p;
}


void view(stack* top) { // просмотерть стэк
	while (top != NULL) {
		cout << top->inf << ' ';
		top = top->next;
	}
	cout << endl;
}


void delst(stack* top) { // удалить стэк
	stack* temp;
	while (top != NULL) {
		temp = top;
		top = top->next;
		delete temp;
	}
}
