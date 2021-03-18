#include <iostream>
#include <string>

using namespace std;

int main()
{
    string name;

    cout << "name input: ";
    cin >> name;

    string message = "hi , " + name  + " sir.";
    cout << message << endl;
}