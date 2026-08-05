#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

//------------------ MAX HEAP ------------------//
void heapifyDescending(vector<int> &data, int size, int root)
{
    int biggest = root;
    int leftChild = 2 * root + 1;
    int rightChild = 2 * root + 2;

    if (leftChild < size && data[leftChild] > data[biggest])
        biggest = leftChild;

    if (rightChild < size && data[rightChild] > data[biggest])
        biggest = rightChild;

    if (biggest != root)
    {
        swap(data[root], data[biggest]);
        heapifyDescending(data, size, biggest);
    }
}

void sortUsingMaxHeap(vector<int> &data)
{
    int size = data.size();

    // Build Max Heap
    for (int idx = size / 2 - 1; idx >= 0; idx--)
        heapifyDescending(data, size, idx);

    // Heap Sort
    for (int idx = size - 1; idx > 0; idx--)
    {
        swap(data[0], data[idx]);
        heapifyDescending(data, idx, 0);
    }
}

//------------------ MIN HEAP ------------------//
void heapifyAscending(vector<int> &data, int size, int root)
{
    int tiniest = root;
    int leftChild = 2 * root + 1;
    int rightChild = 2 * root + 2;

    if (leftChild < size && data[leftChild] < data[tiniest])
        tiniest = leftChild;

    if (rightChild < size && data[rightChild] < data[tiniest])
        tiniest = rightChild;

    if (tiniest != root)
    {
        swap(data[root], data[tiniest]);
        heapifyAscending(data, size, tiniest);
    }
}

void sortUsingMinHeap(vector<int> &data)
{
    int size = data.size();

    // Build Min Heap
    for (int idx = size / 2 - 1; idx >= 0; idx--)
        heapifyAscending(data, size, idx);

    // Heap Sort
    for (int idx = size - 1; idx > 0; idx--)
    {
        swap(data[0], data[idx]);
        heapifyAscending(data, idx, 0);
    }

    // Reverse to get ascending order
    reverse(data.begin(), data.end());
}

//------------------ MAIN ------------------//
int main()
{
    int totalElements;

    cout << "Enter total number of elements: ";
    cin >> totalElements;

    vector<int> baseArray(totalElements);

    srand(static_cast<unsigned int>(time(0)));

    for (int idx = 0; idx < totalElements; idx++)
        baseArray[idx] = rand() % 50000;

    vector<int> arrayForMaxHeap = baseArray;
    vector<int> arrayForMinHeap = baseArray;

    //---------------- MAX HEAP SORT ----------------//
    auto maxSortBegin = high_resolution_clock::now();

    sortUsingMaxHeap(arrayForMaxHeap);

    auto maxSortFinish = high_resolution_clock::now();

    //---------------- MIN HEAP SORT ----------------//
    auto minSortBegin = high_resolution_clock::now();

    sortUsingMinHeap(arrayForMinHeap);

    auto minSortFinish = high_resolution_clock::now();

    //---------------- DISPLAY TIME ----------------//

    auto maxInNano = duration_cast<nanoseconds>(maxSortFinish - maxSortBegin);
    auto maxInMicro = duration_cast<microseconds>(maxSortFinish - maxSortBegin);
    auto maxInMilli = duration_cast<milliseconds>(maxSortFinish - maxSortBegin);
    duration<double> maxInSec = maxSortFinish - maxSortBegin;

    auto minInNano = duration_cast<nanoseconds>(minSortFinish - minSortBegin);
    auto minInMicro = duration_cast<microseconds>(minSortFinish - minSortBegin);
    auto minInMilli = duration_cast<milliseconds>(minSortFinish - minSortBegin);
    duration<double> minInSec = minSortFinish - minSortBegin;

    cout << "\n========== MAX HEAP SORT ==========\n";
    cout << "Nanoseconds  : " << maxInNano.count() << " ns\n";
    cout << "Microseconds : " << maxInMicro.count() << " us\n";

    cout << "\n========== MIN HEAP SORT ==========\n";
    cout << "Nanoseconds  : " << minInNano.count() << " ns\n";
    cout << "Microseconds : " << minInMicro.count() << " us\n";

    return 0;
}
