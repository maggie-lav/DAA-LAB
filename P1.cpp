#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

const int ARRAY_SIZE = 100;

// ---------- Utility: generate a random dataset ----------
vector<int> generateData(int size, int lowerBound = 0, int upperBound = 999) {
    vector<int> data(size);
    mt19937 rng(static_cast<unsigned>(time(nullptr)));
    uniform_int_distribution<int> dist(lowerBound, upperBound);
    for (int &value : data)
        value = dist(rng);
    return data;
}

// ---------- Bubble Sort ----------
void bubbleSort(vector<int> &data) {
    int n = data.size();
    bool swapped = true;
    int pass = 0;
    while (swapped && pass < n) {
        swapped = false;
        for (int i = 0; i < n - pass - 1; i++) {
            if (data[i] > data[i + 1]) {
                swap(data[i], data[i + 1]);
                swapped = true;
            }
        }
        pass++;
    }
}

// ---------- Selection Sort ----------
void selectionSort(vector<int> &data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        int smallestIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j] < data[smallestIndex])
                smallestIndex = j;
        }
        if (smallestIndex != i)
            swap(data[i], data[smallestIndex]);
    }
}

// ---------- Insertion Sort ----------
void insertionSort(vector<int> &data) {
    int n = data.size();
    for (int i = 1; i < n; i++) {
        int current = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > current) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = current;
    }
}

// ---------- Merge Sort ----------
void mergeHalves(vector<int> &data, int left, int mid, int right) {
    vector<int> leftPart(data.begin() + left, data.begin() + mid + 1);
    vector<int> rightPart(data.begin() + mid + 1, data.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;
    while (i < leftPart.size() && j < rightPart.size())
        data[k++] = (leftPart[i] <= rightPart[j]) ? leftPart[i++] : rightPart[j++];
    while (i < leftPart.size()) data[k++] = leftPart[i++];
    while (j < rightPart.size()) data[k++] = rightPart[j++];
}

void mergeSort(vector<int> &data, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(data, left, mid);
    mergeSort(data, mid + 1, right);
    mergeHalves(data, left, mid, right);
}

// ---------- Quick Sort (Hoare partition scheme) ----------
int hoarePartition(vector<int> &data, int low, int high) {
    int pivot = data[low + (high - low) / 2];
    int i = low - 1, j = high + 1;

    while (true) {
        do { i++; } while (data[i] < pivot);
        do { j--; } while (data[j] > pivot);
        if (i >= j) return j;
        swap(data[i], data[j]);
    }
}

void quickSort(vector<int> &data, int low, int high) {
    if (low < high) {
        int splitPoint = hoarePartition(data, low, high);
        quickSort(data, low, splitPoint);
        quickSort(data, splitPoint + 1, high);
    }
}

// ---------- Timing helper ----------
template <typename Func>
long long measureTime(Func sortFunc) {
    auto start = high_resolution_clock::now();
    sortFunc();
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    vector<int> baseData = generateData(ARRAY_SIZE);
    vector<int> working;

    cout << left << setw(15) << "Algorithm" << "Time (microseconds)" << "\n";
    cout << "--------------------------------------\n";

    working = baseData;
    long long t1 = measureTime([&]() { bubbleSort(working); });
    cout << left << setw(15) << "Bubble" << t1 << "\n";

    working = baseData;
    long long t2 = measureTime([&]() { selectionSort(working); });
    cout << left << setw(15) << "Selection" << t2 << "\n";

    working = baseData;
    long long t3 = measureTime([&]() { insertionSort(working); });
    cout << left << setw(15) << "Insertion" << t3 << "\n";

    working = baseData;
    long long t4 = measureTime([&]() { mergeSort(working, 0, working.size() - 1); });
    cout << left << setw(15) << "Merge" << t4 << "\n";

    working = baseData;
    long long t5 = measureTime([&]() { quickSort(working, 0, working.size() - 1); });
    cout << left << setw(15) << "Quick" << t5 << "\n";

    return 0;
}