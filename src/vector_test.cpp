#include "vector.h"

#include <iostream>
#include <cassert>

using namespace std;

int main () {
    // Tests
    Vector<int> v1;
    assert(v1.size() == 0);
    v1.push_back(1);
    assert(v1.size() == 1);
    v1.clear();
    assert(v1.size() == 0);
    v1.push_back(10);
    Vector<int> v2(v1);
    assert(v2[0] == 10);
    assert(v1.size() == 1);
    v2.clear();
    assert(v2.size() == 0);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    assert(v1.capacity() == 8);
    assert(v1.size() == 5);
    v1.shrink_to_fit();
    assert(v1.capacity() == v1.size());
    
    cout << "TEST PASSED";
    return 0;

}
