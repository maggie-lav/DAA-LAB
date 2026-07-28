#include <iostream>
#include <chrono>

// Function for Iterative Factorial
// Time Complexity: O(n)
// Space Complexity: O(1)
unsigned long long computeFactorialLoop(int num) {
    unsigned long long product = 1;
    for (int counter = 1; counter <= num; ++counter) {
        product *= counter;
    }
    return product;
}

// Function for Recursive Factorial
// Time Complexity: O(n)
// Space Complexity: O(n) due to call stack
unsigned long long computeFactorialRecur(int num) {
    if (num <= 1) return 1;
    return num * computeFactorialRecur(num - 1);
}

int main() {
    int value;
    std::cout << "Enter a non-negative integer (e.g., 20): ";
    if (!(std::cin >> value) || value < 0) {
        std::cerr << "Invalid input! Please enter a non-negative integer." << std::endl;
        return 1;
    }

    // Measure Iterative Implementation
    auto loopStart = std::chrono::high_resolution_clock::now();
    unsigned long long loopResult = computeFactorialLoop(value);
    auto loopEnd = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> loopDuration = loopEnd - loopStart;

    // Measure Recursive Implementation
    auto recurStart = std::chrono::high_resolution_clock::now();
    unsigned long long recurResult = computeFactorialRecur(value);
    auto recurEnd = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> recurDuration = recurEnd - recurStart;

    // Output Results
    std::cout << "\n--- Results for " << value << "! ---" << std::endl;
    std::cout << "Iterative Result : " << loopResult << std::endl;
    std::cout << "Iterative Time   : " << loopDuration.count() << " ns" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Recursive Result : " << recurResult << std::endl;
    std::cout << "Recursive Time   : " << recurDuration.count() << " ns" << std::endl;

    return 0;
}