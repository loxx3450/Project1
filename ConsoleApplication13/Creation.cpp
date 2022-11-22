
int** CreateArr(const int count) {
    int** arr = new int* [count + 2];

    for (int i{}; i < count + 2; i++) {

        arr[i] = new int[count + 2]{ 0 };
    }

    return arr;
}

