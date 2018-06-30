#include <iostream>
#include "sort/sort.hpp"

using namespace std;

void BubbleSort_Test() {
    int R[] = {10, 20, 15, 11, 30, 10};
    BubbleSort(R, 6);
    for (int i = 0; i < 6; ++ i) {
        printf("%d\n", R[i]);
    }
}

int main() {
    BubbleSort_Test();
}