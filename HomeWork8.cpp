
#include <iostream>
using namespace std;

int* CreateArray(int size)
{
    if (size <= 0) return nullptr;
    return new int[size];
}

void InitializeArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "Element " << i << ": ";
        cin >> arr[i];
    }
}

void PrintArray(const int* arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << '\n';
}

void FreeArray(int*& arr)
{
    delete[] arr;
    arr = nullptr;
}

void AppendElement(int*& arr, int& size, int value)
{
    int* newArr = new int[size + 1];

    for (int i = 0; i < size; i++)
        newArr[i] = arr[i];

    newArr[size] = value;

    delete[] arr;
    arr = newArr;
    size++;
}

void InsertElement(int*& arr, int& size, int index, int value)
{
    if (index < 0 || index > size) return;

    int* newArr = new int[size + 1];

    for (int i = 0; i < index; i++)
        newArr[i] = arr[i];

    newArr[index] = value;

    for (int i = index; i < size; i++)
        newArr[i + 1] = arr[i];

    delete[] arr;
    arr = newArr;
    size++;
}

void DeleteElement(int*& arr, int& size, int index)
{
    if (index < 0 || index >= size) return;

    int* newArr = CreateArray(size - 1);

    for (int i = 0, j = 0; i < size; i++)
    {
        if (i != index)
            newArr[j++] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    size--;
}

bool IsPrime(int number)
{
    if (number < 2) return false;

    for (int i = 2; i <= number / i; i++)
    {
        if (number % i == 0)
            return false;
    }

    return true;
}

int* RemovePrimes(const int* arr, int size, int& newSize)
{
    newSize = 0;

    for (int i = 0; i < size; i++)
    {
        if (!IsPrime(arr[i]))
            newSize++;
    }

    int* newArr = CreateArray(newSize);
    int index = 0;

    for (int i = 0; i < size; i++)
    {
        if (!IsPrime(arr[i]))
            newArr[index++] = arr[i];
    }

    return newArr;
}

void SplitArray(const int* arr, int size,
    int*& positive, int& positiveSize,
    int*& negative, int& negativeSize,
    int*& zeros, int& zeroSize)
{
    positiveSize = 0;
    negativeSize = 0;
    zeroSize = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] > 0) positiveSize++;
        else if (arr[i] < 0) negativeSize++;
        else zeroSize++;
    }

    positive = CreateArray(positiveSize);
    negative = CreateArray(negativeSize);
    zeros = CreateArray(zeroSize);

    int p = 0, n = 0, z = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] > 0)
            positive[p++] = arr[i];
        else if (arr[i] < 0)
            negative[n++] = arr[i];
        else
            zeros[z++] = arr[i];
    }
}

int main()
{
    // Task 1
    int size = 5;
    int* arr = CreateArray(size);

    InitializeArray(arr, size);
    PrintArray(arr, size);

    AppendElement(arr, size, 100);
    PrintArray(arr, size);

    InsertElement(arr, size, 2, 50);
    PrintArray(arr, size);

    DeleteElement(arr, size, 1);
    PrintArray(arr, size);

    FreeArray(arr);

    // Task 2
    int size2 = 10;
    int* arr2 = new int[size2] { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    int newSize = 0;
    int* result = RemovePrimes(arr2, size2, newSize);

    cout << "Without prime numbers: ";
    PrintArray(result, newSize);

    FreeArray(arr2);
    FreeArray(result);

    // Task 3
    const int size3 = 10;
    int arr3[size3] = { 5, -3, 0, 8, -7, 0, 2, -1, 0, 9 };

    int* positive = nullptr;
    int* negative = nullptr;
    int* zeros = nullptr;

    int positiveSize, negativeSize, zeroSize;

    SplitArray(arr3, size3,
        positive, positiveSize,
        negative, negativeSize,
        zeros, zeroSize);

    cout << "Positive: ";
    PrintArray(positive, positiveSize);

    cout << "Negative: ";
    PrintArray(negative, negativeSize);

    cout << "Zeros: ";
    PrintArray(zeros, zeroSize);

    FreeArray(positive);
    FreeArray(negative);
    FreeArray(zeros);
}
