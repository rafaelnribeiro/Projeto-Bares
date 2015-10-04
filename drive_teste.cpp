#include "QueueLL.h"
#include <iostream>

using namespace std;

int main (void) {

    QueueLL<int> obj;
    int x1 = 5;
    obj.insert(x1);
    /*obj.insert(18);
    obj.insert(65);
    obj.insert(135);
    obj.insert(444);
    */
    cout << obj << "\n";

    return 0;

}
