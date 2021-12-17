#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class X> void shuffle(X** myArray, int myArraySize){
    // TODO: Implement here the shuffle algorithm
    srand(time(0));
    int i, j;
    X* temp;
    for(i = myArraySize - 1; i > 0; i--){
        j = rand() % i + 1;
        temp = myArray[j];
        myArray[j] = myArray[i];
        myArray[i] = temp;
    }
}


