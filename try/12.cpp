#include <iostream>
#include <string>
using namespace std;

class Girl;   // 前向声明

class Boy {
private:
    string name;
    int age;

public:
    Boy(string n, int a) {
        name = n;
        age = a;
        cout << "Boy constructing..." << endl << endl;
    }

    ~Boy() {
        cout << "Boy destructing..." << endl << endl;
    }

    void ShowBoy() {
        cout << "Boy's name:" << name << endl << endl;
        cout << "Boy's age:" << age << endl << endl;
    }

    friend class Girl;   // Girl 是 Boy 的友元类
};

class Girl {
private:
    string name;
    int age;

public:
    Girl(string n, int a) {
        name = n;
        age = a;
        cout << "Girl constructing..." << endl << endl;
    }

    ~Girl() {
        cout << "Girl destructing..." << endl;
    }

    void ShowGirl() {
        cout << "Girl's name:" << name << endl << endl;
        cout << "Girl's age:" << age << endl << endl;
    }

    void VisitBoy(Boy& b) {
        cout << "Boy's name:" << b.name << endl << endl;
        cout << "Boy's age:" << b.age << endl << endl;
    }

};

int main() {
    Girl g("wang", 19);
    Boy b("li", 20);

    b.ShowBoy();
    g.ShowGirl();
    g.VisitBoy(b);

    return 0;
}

