#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

class Sort {
public:
    virtual void merge(vector<int> &arr, int l, int m, int p) = 0;
    virtual void sort(vector<int> &arr, int l, int p) = 0;
    virtual void printArray(vector<int> &arr) = 0;
};

class MergeSort : public Sort {
   // Merge dvou posloupnosti (Leva + Prava)
    // Prvni posloupnost arr[l..m]
    // Druha posloupnost arr[m+1..p]
public:

    void merge(vector<int> &arr, int l, int m, int p) {
        int n1 = m - l + 1;
        int n2 = p - m;

        // Docas. posloupnosti
        vector<int> L(n1), P(n2);

        // Posli data do temp sloupcu L[] a P[]
        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            P[j] = arr[m + 1 + j];

        // Merge posloupnosti zpatky do arr[l..p]

        // Prvni index prvfni posl
        int i = 0;

        // Prvni index druhe posl
        int j = 0;

        // Prvni index mergle posl
        int k = l;

        while (i < n1 && j < n2) {
            if (L[i] <= P[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = P[j];
                j++;
            }
            k++;
        }

        // Zkopiruj zbytek L[], pokud E
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        // Zkopiruj zbytek P[], pokud E
        while (j < n2) {
            arr[k] = P[j];
            j++;
            k++;
        }
    }


    // l= levy idx, p=pravy idx pod-posloupnosti arr k serazeni

    void sort(vector<int> &arr, int l, int p) {
        if (l >= p) {
            return; //vraci rekurzivne
        }
        int m = (l + p - 1) / 2;
        sort(arr, l, m);
        sort(arr, m + 1, p);
        merge(arr, l, m, p);
    }



    // Var Funkce
    // Output zprava


    void printArray(vector<int>& A) {
        for (int i = 0; i < A.size(); i++)
            cout << A.at(i) << " ";
    }

};

vector<int> readData(string filename) {
    std::fstream myfile(filename, std::ios_base::in);

    vector<int> numbers;
    int a;
    while (myfile >> a) {
        numbers.push_back(a);
    }



    //getchar();

    return numbers;
}

// Hlavni program

int main() {
    int iterations = 10; //iterations to get average from
    string inputFile = "20k.txt";

    vector<int> numbers = readData(inputFile);
    double totalDuration = 0;
    int arr_size = numbers.size();

    MergeSort m;
    cout << "Given array is \n";
    m.printArray(numbers);

    cout << "\n\n\n\n";
    vector<int> tmp_array;
    for (int i = 0; i < iterations; i++) {
        //copy original array to a new one to have the same array every time
        tmp_array = numbers;

        //measuring part
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        m.sort(tmp_array, 0, numbers.size() - 1);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        totalDuration += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    }
    cout << "\nSorted array is \n";
    m.printArray(tmp_array);
    cout << "\n\n\n\n";

    cout << "avg time from " << iterations << " runs is: " << totalDuration / iterations << "[ms]" << std::endl;
    return 0;
}

