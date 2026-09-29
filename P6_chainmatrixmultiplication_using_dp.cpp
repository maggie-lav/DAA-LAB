//  MATRIX CHAIN MULTIPLICATION USING DYNAMIC PROGRAMMING
//
//  TIME & SPACE COMPLEXITY SUMMARY
//  Method                         Time        Space       Notes
//  Matrix Chain Multiplication   O(n^3)      O(n^2)      Uses Dynamic Programming
//
//  Formula:
//  m[i][j] = min { m[i][k] + m[k+1][j]
//                  + p[i-1] * p[k] * p[j] }

#include <iostream>
#include <climits> 
#include <chrono>
 
using namespace std;


// Function for Matrix Chain Multiplication
int matrixChainMultiplication(int p[], int n)
{
    // m[i][j] stores the minimum cost
    // of multiplying matrices Ai to Aj
    int m[5][5] = {0};

    // Chain length
    for (int chainLength = 2; chainLength <= n; ++chainLength)
    {
        // Starting matrix
        for (int i = 1; i <= n - chainLength + 1; ++i)
        {
            // Ending matrix
            int j = i + chainLength - 1;

            m[i][j] = INT_MAX;

            // Try every possible value of k
            for (int k = i; k < j; ++k)
            {

                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                }
            }
        }
    }

    return m[1][n];
}


int main()
{
    // Matrix dimensions:
    //
    // A1 = 10 x 30
    // A2 = 30 x 5
    // A3 = 5 x 60
    // A4 = 60 x 20

    int p[] = {10, 30, 5, 60, 20};

    // Number of matrices
    int n = 4;


    cout << "===== MATRIX CHAIN MULTIPLICATION =====\n";

    cout << "\nMatrices:\n";
    cout << "A1 = 10 x 30\n";
    cout << "A2 = 30 x 5\n";
    cout << "A3 = 5 x 60\n";
    cout << "A4 = 60 x 20\n";

    cout << "\nDimension Array:\n";
    cout << "P = {10, 30, 5, 60, 20}\n";

   
    // CALCULATIONS USING THE FORMULA

    cout << "\n--- Calculations ---\n";

    cout << "\nFormula:\n";
    cout << "m[i][j] = min { m[i][k] + m[k+1][j]\n";
    cout << "              + p[i-1] * p[k] * p[j] }\n";


    // Chain Length = 2
    cout << "\nChain Length = 2\n";

    cout << "m[1][2] = 10 x 30 x 5 = 1500\n";
    cout << "m[2][3] = 30 x 5 x 60 = 9000\n";
    cout << "m[3][4] = 5 x 60 x 20 = 6000\n";


    // Chain Length = 3
    cout << "\nChain Length = 3\n";

    cout << "\nm[1][3]:\n";

    cout << "k = 1:\n";
    cout << "0 + 9000 + (10 x 30 x 60) = 27000\n";

    cout << "k = 2:\n";
    cout << "1500 + 0 + (10 x 5 x 60) = 4500\n";

    cout << "m[1][3] = min(27000, 4500) = 4500\n";


    cout << "\nm[2][4]:\n";

    cout << "k = 2:\n";
    cout << "0 + 6000 + (30 x 5 x 20) = 9000\n";

    cout << "k = 3:\n";
    cout << "9000 + 0 + (30 x 60 x 20) = 45000\n";

    cout << "m[2][4] = min(9000, 45000) = 9000\n";


    // Chain Length = 4
    cout << "\nChain Length = 4\n";

    cout << "\nm[1][4]:\n";

    cout << "k = 1:\n";
    cout << "0 + 9000 + (10 x 30 x 20) = 15000\n";

    cout << "k = 2:\n";
    cout << "1500 + 6000 + (10 x 5 x 20) = 8500\n";

    cout << "k = 3:\n";
    cout << "4500 + 0 + (10 x 60 x 20) = 16500\n";

    cout << "m[1][4] = min(15000, 8500, 16500) = 8500\n";


    // DISPLAY DP TABLE

    int m[5][5] = {0};

    for (int chainLength = 2; chainLength <= n; ++chainLength)
    {
        for (int i = 1; i <= n - chainLength + 1; ++i)
        {
            int j = i + chainLength - 1;

            m[i][j] = INT_MAX;

            for (int k = i; k < j; ++k)
            {
                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                }
            }
        }
    }


    cout << "\n--- DP Table ---\n\n";

    cout << "\tA1\tA2\tA3\tA4\n";

    for (int i = 1; i <= n; ++i)
    {
        cout << "A" << i << "\t";

        for (int j = 1; j <= n; ++j)
        {
            if (i > j)
                cout << "-\t";
            else
                cout << m[i][j] << "\t";
        }

        cout << endl;
    }


    // MEASURE EXECUTION TIME

    auto start = chrono::high_resolution_clock::now();

    int result = matrixChainMultiplication(p, n);

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::nano> duration = end - start;


    // RESULTS

    cout << "\n--- Results ---\n";

    cout << "Minimum number of scalar multiplications : "
         << result << endl;

    cout << "Execution Time : "
         << duration.count() << " ns" << endl;


    // COMPLEXITY

    cout << "\n--- Complexity ---\n";

    cout << "Time Complexity  : O(n^3)" << endl;
    cout << "Space Complexity : O(n^2)" << endl;


    return 0;
}
