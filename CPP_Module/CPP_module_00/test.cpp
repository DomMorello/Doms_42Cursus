#include <iostream>
#include <string>

using namespace std;

class Parent {
public:
	Parent() {
		cout << "P Constructor" << endl;
	}
	virtual ~Parent() {
		cout << "P Destructor" << endl;
	}
};

class Child : public Parent {
public:
	Child() {
		cout << "C Constructor" << endl;
	}
	~Child () {
		cout << "C Desstructor" << endl;
	}
};

int main() {
	Child *c = new Child;
	Parent *p = c;

	delete p;
	return 0;
}