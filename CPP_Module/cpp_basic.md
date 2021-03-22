# CPP Basics
## 범위 기반 for문
```c++
int arr[10] = {3,1,4,1,5,9,2,6,5,3};
for (int n : arr) {
    // int n = arr[3]; --> 이런 식으로 n은 변수일 뿐이다.
    cout << n << endl;
    // n++;
}
```
> 위 코드에서 n의 값을 주석과 같이(n++) 변경을 해줘도 출력되는 값은 배열의 요소들이 전부 출력이 된다. 왜냐하면 반복문 안에서 n 은 내부적으로 `int n = arr[3]` 과 같이 단순히 변수로서 역할을 하기만 하기 때문이다. 즉, 출력 이후에 n의 값을 변경해봤자 변화가 없다. 하지만 `for int &n : arr` 으로 조건을 바꿔준다면 위와 같이 `n++`을 해줬을 때 레퍼런스 변수를 사용했기 때문에 `int n = &arr[3]`과 같이 작동해서 함수의 원래 값이 변경되게 된다.
---
## Reference Variable
> 참조형은 선언과 동시에 반드시 초기화해야 한다. <br>
null 값을 저장할 수 있는 포인터와 다르게, null 참조 같은 것은 없다.<br>
초기화된 후에는 다른 변수를 참조하도록 변경할 수 없다.<br>
> 1. non-const 값 참조형
> 2. const 값 참조형
> 3. r-value 참조형

- 자료형& 별명 = 기존 변수명
```c++
int value = 5;
int& ref = value;   //refernce to variable value
```
& 는 여기서 주소를 의미하는 것이 아니고 참조를 의미한다. <br>
```c++
value = 6;
ref = 7;    //value changes to 7

std::cout << value; // prints 7
ref++;
std::cout << value; // prints 8
```
참조형에 주소 연산자 (&)를 사용하면 참조되는 값의 주소가 반환된다.<br>
```c++
cout << &value; // prints 0012FF7C
cout << &ref; // prints 0012FF7C
```
### Reference: https://boycoding.tistory.com/207

---
## 상수형 매개변수와 상수형 메서드
- 상수형 메서드
> 해당 메서드 안에서 자신이 속한 클래스의 다른 맴버변수를 건드릴 수 없게 한다.
```c++
class Accout {
public:
	int getMoney() const {
		money++;	//컴파일 에러-->상수형 메서드이기 때문에 맴버변수를 변경할 수 없음.
		return money;
	}
private:
	int money;
};
```
- 상수형 매개변수
```c++
class Accout {
public:
	void Deposit(const int d) {
		d = money;	//컴파일 에러 --> 매개변수가 상수화됐기 때문에
					//값을 변경할 수 없다. 
		money += d;
		cout << d << " is added to the accout" << endl;
	}
private: money;
};
```
---
## 가상 소멸자
상속을 받는 경우에 일반적으로 부모 클래스 객체를 생성하고 삭제하고 자식 클래스 객체를 생성하고 삭제하는 경우에는 virtual 키워드를 추가하지 않아도 문제가 없다. 
```c++
class Parent {
public:
	Parent() {
		cout << "P Constructor" << endl;
	}
	~Parent() {
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
	Parent p;
	Child c;
}
```
위 코드같은 경우 상속을 했어도 생성을 각각 부모 클래스 객체, 자식 클래스 객체를 생성했기 때문에
`P Constructor
(P Constructor
C Constructor)
(C Desstructor
P Destructor)
P Destructor`
순으로 출력이 된다.<br>

하지만 다형성 이용을 위해서 부모 클래스의 포인터로부터 자식 클래스를 호출할 때 가상함수로 정의되지 않은 자식 클래스의 오버라이딩된 함수를 호출하면 부모 클래스의 맴버 함수가 호출된다. 이와 마찬가지로 소멸자도 자식 클래스에서 오버라이딩된 함수라고 볼 수 있다. 그래서 만약에 부모 포인터로 객체를 삭제하게 되면 부모 클래스의 소멸자가 호출돼서 자식 클래스의 객체는 소멸자가 호출되지 않는 문제가 발생한다.<br>
따라서 부모 클래스의 소멸자를 가상 함수로 선언하지 않으면 이 경우 자식 클래스의 소멸자는 결코 호출되지 않는다. 가상 함수 키워드 virtual이 사용되었다면 이것은 자식 클래스에서 재정의될 수 있음을 명시하기 때문에 포인터의 종류에 상관없이 항상 자식 클래스의 메서드가 호출된다. 즉, 자식 클래스의 소멸자가 호출되고 나서 부모 클래스의 소멸자가 호출된다.<br>
이러한 이우로 상속 관계가 있고 소멸자에서 리소스를 해제해야 하는 경우 반드시 소멸자를 가상 함수로 선언해야 한다.

```c++
// Class 선언은 위 코드 스니펫과 같음.

int main() {
	Child *c = new Child;
	Parent *p = c;	//부모 클래스의 포인터로 자식 클래스 객체를 가리킴

	delete p;	//부모 클래스의 포인터를 이용해서 자식 클래스 객체를 삭제함
	return 0;
}
```
위 코드에서 가상 소멸자를 사용하지 않으면
`P Constructor
C Constructor
P Destructor` 순으로 출력되며 자식 클래스의 객체는 삭제되지 않는 문제가 발생한다. 그러므로 부모 클래스의 소멸자에 `virtual` 키워드를 추가해줘서 자식 클래스의 소멸자가 실행되도록 해줘야 한다. 
```c++
class Parent {
public:
	Parent() {
		cout << "P Constructor" << endl;
	}
	virtual ~Parent() {	//virtual 키워드 추가
		cout << "P Destructor" << endl;
	}
};
```
위와 같이 수정하고 main문을 다시 실행하면 
`P Constructor
C Constructor
C Desstructor
P Destructor`와 같이 정상적으로 자식 클래스 객체 소멸자가 호출된 이후에 부모 클래스의 소멸자가 호출된다. 
### Reference (http://hyacinth.byus.net/moniwiki/wiki.php/C%2B%2B/%EC%86%8C%EB%A9%B8%EC%9E%90%EC%97%90%20virtual%EC%9D%84%20%EC%93%B0%EB%8A%94%20%EC%9D%B4%EC%9C%A0)
---
## static 변수의 초기화
> static 변수는 클래스 내에서는 선언만 하고 값을 초기화할 수 없다. static 변수는 클래스로부터 생성되는 모든 객체들이 공유하는 메모리이므로 프로그램이 실행되면서 끝까지 메모리공간에 존재하게 된다. 그런데 class 내부에 초기화를 하면 객체들이 생성될때마다 덮어씌어질것이므로 반드시 전연에서 초기화를 해야 한다. 그런데 이 때 hpp 헤더파일의 전역에서는 초기화가 불가능하다. 헤더파일을 include 하는 모든 cpp파일에서 그러면 초기화된 값이 덮어씌어질 것이기 때문이다. 그래서 반드시 static 변수의 초기화를 cpp파일의 전역에서 진행돼야 한다.
---
