#include<iostream>
#include <iomanip>
#include "ArrayStack.h"
#include <cstdint>
using namespace std;

/* *Note 0x14 is 20 in decimal
+--------+------------+----------+---------+
| Offset | Member     | Type     | Size    |
+--------+------------+----------+---------+
| 0x00   | vtable ptr | void*    | 8 bytes |
| 0x08   | mArray     | int*     | 8 bytes |
| 0x10   | MAX_SIZE   | int      | 4 bytes |
| 0x14   | top        | int      | 4 bytes |
+--------+------------+----------+---------+
*/

int main (){
    ArrayStack stack;
    // unsafely dreference pointer access to private data in ArrayStack
    uintptr_t* arrayPtr = reinterpret_cast<uintptr_t*>(&stack);
    //extracting the array since we know its address is at index 1
    int* mArray = reinterpret_cast<int*>(arrayPtr[1]);
    // getting MAX_SIZE assuming its at offset 20 from stack object
    int top = *reinterpret_cast<int*>(reinterpret_cast<char*>(&stack) + 20);
    int count = top + 1;
    cout << "Max count size before adding items:" << dec << count << endl;
    for (int i = 0; i < 17;i++){
        stack.push(i);
    }
    // getting updated value of top at offset 20
    top = *reinterpret_cast<int*>(reinterpret_cast<char*>(&stack) + 20);
    count = top + 1;
    cout << "Max count size before adding items:" << dec << count << endl;
    cout << "Outputting stack elements in order: " << endl;
    cout << "Stack address is " << hex << arrayPtr[1] << dec << endl;
    for(int i = 0; i <count;++i){
        cout << mArray[i] << dec << endl;
    }
    cout << "Outputting LIFO stack" << endl;
    while (!stack.isEmpty()){
        cout << stack.pop() << dec << endl;
    }
}