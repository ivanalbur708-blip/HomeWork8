#include <iostream>
using namespace std;

int* AllocateArray(int size)
{
    return new int[size];
}

void InitializeArray(int* array, int size)
{
    for (int i = 0; i < size; i++)
        cin >> array[i];
}

void PrintArray(const int* array, int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << ' ';
    cout << '\n';
}

void DeleteArray(int* array)
{
    delete[] array;
}

int* AppendElement(int* array, int& size, int value)
{
    int* result = new int[size + 1];
    for (int i = 0; i < size; i++)
        result[i] = array[i];
    result[size] = value;
    DeleteArray(array);
    size++;
    return result;
}

int* InsertElement(int* array, int& size, int index, int value)
{
    if (index < 0 || index > size)
        return array;

    int* result = new int[size + 1];
    for (int i = 0; i < index; i++)
        result[i] = array[i];
    result[index] = value;
    for (int i = index; i < size; i++)
        result[i + 1] = array[i];

    DeleteArray(array);
    size++;
    return result;
}

int* RemoveElement(int* array, int& size, int index)
{
    if (index < 0 || index >= size)
        return array;

    int* result = new int[size - 1];
    for (int i = 0; i < index; i++)
        result[i] = array[i];
    for (int i = index + 1; i < size; i++)
        result[i - 1] = array[i];

    DeleteArray(array);
    size--;
    return result;
}

bool IsPrime(int number)
{
    if (number < 2)
        return false;
    for (int divisor = 2; divisor <= number / divisor; divisor++)
        if (number % divisor == 0)
            return false;
    return true;
}

int* RemovePrimes(const int* array, int size, int& newSize)
{
    newSize = 0;
    for (int i = 0; i < size; i++)
        if (!IsPrime(array[i]))
            newSize++;

    int* result = new int[newSize];
    int index = 0;
    for (int i = 0; i < size; i++)
        if (!IsPrime(array[i]))
            result[index++] = array[i];

    return result;
}

void SplitBySign(const int* array, int size,
    int* positive, int& positiveSize,
    int* negative, int& negativeSize,
    int* zeros, int& zeroSize)
{
    positiveSize = 0;
    negativeSize = 0;
    zeroSize = 0;

    for (int i = 0; i < size; i++)
    {
        if (array[i] > 0) positive[positiveSize++] = array[i];
        else if (array[i] < 0) negative[negativeSize++] = array[i];
        else zeros[zeroSize++] = array[i];
    }
}

int main()
{
    // Task 1
    int size;
    cout << "Enter dynamic array size: ";
    cin >> size;
    if (!cin || size < 0) return 1;

    int* array = AllocateArray(size);
    cout << "Enter " << size << " elements: ";
    InitializeArray(array, size);

    cout << "Initial array: ";
    PrintArray(array, size);

    int value, index;
    cout << "Value to append: ";
    cin >> value;
    array = AppendElement(array, size, value);
    cout << "After append: ";
    PrintArray(array, size);

    cout << "Index (0.." << size << ") and value to insert: ";
    cin >> index >> value;
    if (index < 0 || index > size)
        cout << "Invalid insertion index\n";
    else
        array = InsertElement(array, size, index, value);
    cout << "After insertion: ";
    PrintArray(array, size);

    cout << "Index (0.." << size - 1 << ") to remove: ";
    cin >> index;
    if (index < 0 || index >= size)
        cout << "Invalid removal index\n";
    else
        array = RemoveElement(array, size, index);
    cout << "After removal: ";
    PrintArray(array, size);

    // Task 2
    int withoutPrimesSize;
    int* withoutPrimes = RemovePrimes(array, size, withoutPrimesSize);
    cout << "Array without prime numbers: ";
    PrintArray(withoutPrimes, withoutPrimesSize);

    // Task 3
    const int staticArray[] = { 5, -2, 0, 7, -8, 0, 11, -4, 3, 0 };
    const int staticSize = sizeof(staticArray) / sizeof(staticArray[0]);

    int* positive = new int[staticSize];
    int* negative = new int[staticSize];
    int* zeros = new int[staticSize];
    int positiveSize, negativeSize, zeroSize;

    SplitBySign(staticArray, staticSize,
        positive, positiveSize,
        negative, negativeSize,
        zeros, zeroSize);

    cout << "Positive: ";
    PrintArray(positive, positiveSize);
    cout << "Negative: ";
    PrintArray(negative, negativeSize);
    cout << "Zero: ";
    PrintArray(zeros, zeroSize);

    DeleteArray(array);
    array = nullptr;
    DeleteArray(withoutPrimes);
    withoutPrimes = nullptr;
    DeleteArray(positive);
    DeleteArray(negative);
    DeleteArray(zeros);
    return 0;
}
