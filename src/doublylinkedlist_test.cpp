#include <iosteam>
#include "doublylinkedlist.h"

using namespace std;

int main () {
    LinkedList my_list;

    int n = 3;

    printf("Test 1");

    my_list.push_back(1);
    assert(my_list.contains(1));
    assert(my_list.size() == 1);

    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);

    assert(my_list.contains(2));
    assert(my_list.contains(3));
    assert(my_list.contains(4));
    assert(!my_list.contains(10));
    assert(!my_list.contains(99));
    assert(!my_list.contains(-1));
    assert(my_list.size() == 4);

    my_list.remove_key(3);

    assert(!my_list.contains(3));
    assert(my_list.size() == 3);

    my_list.remove_key(1);

    assert(!my_list.contains(1));
    assert(my_list.size() == 2);

    my_list.push_back(5);
    my_list.push_back(6);
    my_list.push_back(7);

    assert(my_list.contains(5));
    assert(my_list.contains(6));
    assert(my_list.contains(7));
    assert(my_list.size() == 5);

    my_list.push_front(1);

    assert(my_list.contains(1));
    assert(my_list.size() == 6);

    my_list.remove_key(1);
    my_list.remove_key(5);
    my_list.remove_key(6);
    my_list.remove_key(7);

    assert(my_list.contains(2));
    assert(my_list.contains(4));
    assert(!my_list.contains(1));
    assert(!my_list.contains(5));
    assert(!my_list.contains(6));
    assert(!my_list.contains(7));
    assert(my_list.size() == 2);

    my_list.remove_key(2);

    assert(my_list.size() == 1);

    my_list.remove_key(4);

    assert(my_list.size() == 0);

    my_list.push_back(1);

    assert(my_list.size() == 1);

    cout << "TEST 1 PASSED";

    return 0;
}