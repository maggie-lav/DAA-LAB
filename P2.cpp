#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Linear Search Function
int searchLinear(vector<int> list, int target)
{
    for (int idx = 0; idx < list.size(); idx++)
    {
        if (list[idx] == target)
            return idx;
    }
    return -1;
}

// Binary Search Function
int searchBinary(vector<int> list, int target)
{
    int left = 0;
    int right = list.size() - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        if (list[middle] == target)
            return middle;
        else if (list[middle] < target)
            left = middle + 1;
        else
            right = middle - 1;
    }

    return -1;
}

int main()
{
    int totalItems = 100000;
    vector<int> numbers(totalItems);

    // Creating a sorted array
    for (int idx = 0; idx < totalItems; idx++)
        numbers[idx] = idx + 1;

    int searchValue;
    cout << "Enter element to search: ";
    cin >> searchValue;

    int position;

    // Linear Search Timing
    auto begin1 = high_resolution_clock::now();
    position = searchLinear(numbers, searchValue);
    auto end1 = high_resolution_clock::now();

    cout << "\nLinear Search\n";
    if (position != -1)
        cout << "Element found at index " << position << endl;
    else
        cout << "Element not found\n";

    cout << "Time Taken : "
         << duration_cast<microseconds>(end1 - begin1).count()
         << " microseconds\n";

    // Binary Search Timing
    auto begin2 = high_resolution_clock::now();
    position = searchBinary(numbers, searchValue);
    auto end2 = high_resolution_clock::now();

    cout << "\nBinary Search\n";
    if (position != -1)
        cout << "Element found at index " << position << endl;
    else
        cout << "Element not found\n";

    cout << "Time Taken : "
         << duration_cast<microseconds>(end2 - begin2).count()
         << " microseconds\n";

    return 0;
}