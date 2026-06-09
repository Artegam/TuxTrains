#include <unordered_set>
#include <string>
#include <iostream>
#include <list>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <variant>
#include <cstring>
#include <vector>

#include <iostream>

class A {
  private:
    unsigned int _val = 1;
  public:
    A () {_val=666;};
    A (unsigned int i) {_val = i;};
    void val(unsigned int i) {_val = i;};
    unsigned int val() {return _val;};
};

class B : public A {
  public:
    B(A a) { val(a.val()); };
    void display() {std::cout << "classB display" << std::endl;};
};

int main()
{
    A t(4);
    B test(t);
    //test = t;
    test.display();
    exit(0);
}
