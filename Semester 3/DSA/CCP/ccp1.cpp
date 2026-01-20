#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;
using namespace std::chrono;
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        if (min_idx != i) swap(&arr[min_idx], &arr[i]);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
void generateRandomFile(const string& filename, int count) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error creating file: " << filename << endl;
        return;
    }
    srand(time(nullptr));
    for (int i = 0; i < count; i++) file << (rand() % 1000000) + 1 << endl;
    file.close();
    cout << "  Generated " << count << " numbers" << endl;
}

int* loadFromFile(const string& filename, int& count) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "  Error opening: " << filename << endl;
        count = 0;
        return nullptr;
    }

    count = 0;
    int temp;
    while (file >> temp) count++;

    file.clear();
    file.seekg(0);

    int* arr = new int[count];
    for (int i = 0; i < count; i++) file >> arr[i];
    file.close();
    return arr;
}

void saveToFile(const string& filename, int arr[], int n) {
    ofstream file(filename);
    for (int i = 0; i < n; i++) file << arr[i] << endl;
    file.close();
}
double measureSortTime(void (*sortFunc)(int[], int), int arr[], int n, const string& algoName) {
    int* arrCopy = new int[n];
    memcpy(arrCopy, arr, n * sizeof(int));

    auto start = high_resolution_clock::now();

    try {
        sortFunc(arrCopy, n);
    }
    catch (exception& e) {
        delete[] arrCopy;
        return -2.0;
    }
    catch (...) {
        delete[] arrCopy;
        return -3.0;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    double timeTaken = duration.count() / 1000.0;

    if (n <= 100000 && !isSorted(arrCopy, n)) {
        cerr << "  ERROR: Sorting failed!" << endl;
    }

    delete[] arrCopy;
    return timeTaken;
}
struct TestResult {
    double time;
    string status;
};

TestResult safeMeasureTime(void (*sortFunc)(int[], int), int arr[], int n, const string& algoName) {
    TestResult result;
    if ((algoName == "Quick Sort" || algoName == "Merge Sort") && n > 100000) {
        cout << "  (Risk: Stack overflow) ";
    }

    try {
        result.time = measureSortTime(sortFunc, arr, n, algoName);

        if (result.time == -2.0) {
            result.status = "EXCEPTION";
            result.time = 0.0;
        }
        else if (result.time == -3.0) {
            result.status = "UNKNOWN_ERROR";
            result.time = 0.0;
        }
        else if (result.time > 3600000) {
            result.status = "TIMEOUT";
        }
        else {
            result.status = "OK";
        }
    }
    catch (bad_alloc& e) {
        result.status = "OUT_OF_MEMORY";
        result.time = 0.0;
    }
    catch (exception& e) {
        result.status = "SYSTEM_CRASH";
        result.time = 0.0;
    }
    catch (...) {
        result.status = "UNKNOWN_CRASH";
        result.time = 0.0;
    }

    return result;
}
void createDirectory(const string& dirName) {
#ifdef _WIN32
    _mkdir(dirName.c_str());
#else
    mkdir(dirName.c_str(), 0777);
#endif
}
int main() {
    cout << "=============================================\n";
    cout << "  COMPLETE SORTING ANALYSIS\n";
    cout << "  Testing ALL 12 sizes × 6 algorithms\n";
    cout << "=============================================\n\n";

    // ALL input sizes
    const int NUM_SIZES = 12;
    int sizes[NUM_SIZES] = {
        1000, 2000, 3000, 4000, 5000,
        10000, 20000, 40000, 80000,
        160000, 250000, 500000
    };

    // Algorithms
    const char* algoNames[] = {
        "Bubble Sort", "Insertion Sort", "Selection Sort",
        "Quick Sort", "Merge Sort", "Heap Sort"
    };

    void (*algoFunctions[])(int[], int) = {
        bubbleSort, insertionSort, selectionSort,
        quickSortWrapper, mergeSortWrapper, heapSort
    };

    const int NUM_ALGOS = 6;
    string machineName = "A";
    createDirectory("data");
    createDirectory("results");
    string resultsFile = "results/sorting_results_" + machineName + ".csv";
    ofstream csv(resultsFile);
    csv << "Algorithm,InputSize,Time(ms),Status\n";

    cout << "Testing on Machine " << machineName << "\n";
    cout << "WARNING: O(n²) algorithms will take VERY LONG!\n";
    cout << "Estimated total time: 12+ HOURS\n\n";
    cout << left << setw(20) << "Algorithm"
        << right << setw(12) << "Size"
        << right << setw(15) << "Time"
        << " Status\n";
    cout << string(60, '-') << "\n";
    int totalCrashes = 0;
    int totalTests = 0;
    int testsCompleted = 0;
    for (int sizeIdx = 0; sizeIdx < NUM_SIZES; sizeIdx++) {
        int currentSize = sizes[sizeIdx];

        cout << "\n>>> Size: " << currentSize << " elements <<<\n";
        string inputFile = "data/input_" + to_string(currentSize) + ".txt";
        ifstream check(inputFile);
        if (!check.good()) {
            cout << "  Generating data... ";
            generateRandomFile(inputFile, currentSize);
        }
        else {
            cout << "  Using existing data\n";
        }
        check.close();
        int dataSize;
        int* numbers = loadFromFile(inputFile, dataSize);

        if (!numbers || dataSize != currentSize) {
            cerr << "  ERROR: Failed to load data\n";
            if (numbers) delete[] numbers;
            for (int algoIdx = 0; algoIdx < NUM_ALGOS; algoIdx++) {
                csv << algoNames[algoIdx] << "," << currentSize << ",0.000,LOAD_ERROR\n";
            }
            csv.flush();
            continue;
        }
        for (int algoIdx = 0; algoIdx < NUM_ALGOS; algoIdx++) {
            string algoName = algoNames[algoIdx];
            totalTests++;

            cout << "  " << left << setw(20) << algoName
                << right << setw(12) << currentSize;
            cout.flush();
            if ((algoName == "Bubble Sort" || algoName == "Insertion Sort" || algoName == "Selection Sort")
                && currentSize >= 100000) {
                cout << "  (May take hours) ";
                cout.flush();
            }
            TestResult result = safeMeasureTime(algoFunctions[algoIdx], numbers, currentSize, algoName);
            if (result.status != "OK") {
                totalCrashes++;
            }
            else {
                testsCompleted++;
            }
            if (result.status == "OK") {
                if (result.time < 1000) {
                    cout << right << setw(15) << fixed << setprecision(3) << result.time << "ms";
                }
                else if (result.time < 60000) {
                    cout << right << setw(15) << fixed << setprecision(1) << (result.time / 1000) << "s";
                }
                else {
                    cout << right << setw(15) << fixed << setprecision(1) << (result.time / 60000) << "min";
                }
            }
            else {
                cout << "  " << result.status;
            }
            if (currentSize <= 10000 && result.status == "OK") {
                int* sortedCopy = new int[currentSize];
                memcpy(sortedCopy, numbers, currentSize * sizeof(int));
                algoFunctions[algoIdx](sortedCopy, currentSize);

                string cleanAlgoName = algoName;
                for (char& c : cleanAlgoName) if (c == ' ') c = '_';
                string outputFile = "data/output_" + cleanAlgoName + "_" + to_string(currentSize) + ".txt";
                saveToFile(outputFile, sortedCopy, currentSize);

                delete[] sortedCopy;
                cout << " [SAVED]";
            }
            csv << algoName << "," << currentSize << ","
                << fixed << setprecision(6) << result.time << "," << result.status << "\n";
            csv.flush();
            cout << endl;
        }
        delete[] numbers;
        cout << "\n  Progress: " << (sizeIdx + 1) << "/" << NUM_SIZES << " sizes";
        cout << " | OK: " << testsCompleted << "/" << totalTests;
        cout << " | Crashes: " << totalCrashes << "\n";
        if (currentSize >= 100000 && sizeIdx < NUM_SIZES - 1) {
            int nextSize = sizes[sizeIdx + 1];
            cout << "\n   Next: " << nextSize << " elements";
            cout << "\n  Continue? (y/n): ";

            char choice;
            cin >> choice;
            if (choice == 'n' || choice == 'N') {
                cout << "  Stopped by user at size " << currentSize << "\n";
                break;
            }
        }

        cout << "\n";
    }
    csv.close();

    cout << "\n" << string(70, '=') << "\n";
    cout << "  TESTING FINISHED\n";
    cout << "  Results: " << resultsFile << "\n";
    cout << "  Tests attempted: " << totalTests << "\n";
    cout << "  Tests completed: " << testsCompleted << "\n";
    cout << "  Crashes/Errors: " << totalCrashes << "\n";

    if (totalCrashes > 0) {
        cout << "\n    Some tests crashed (expected for O(n²) on large inputs)\n";
        cout << "     This demonstrates O(n²) impracticality!\n";
    }

    cout << string(70, '=') << "\n\n";
    cout << "EXPECTED FOR ASSIGNMENT TABLES:\n";
    cout << "───────────────────────────────\n";
    cout << "• Small sizes (1k-40k): All times measured\n";
    cout << "• Medium sizes (80k-160k): O(n²) very slow\n";
    cout << "• Large sizes (250k-500k): O(n²) may crash/timeout\n";
    cout << "• O(n log n): Fast for all sizes\n";
    cout << "• Status in CSV: OK, TIMEOUT, or SYSTEM_CRASH\n";
    cout << "───────────────────────────────\n";

    cout << "\nFor Machine B:\n";
    cout << "1. Change: string machineName = \"A\"; to \"B\"\n";
    cout << "2. Recompile and run\n";
    cout << "3. Compare results_A.csv and results_B.csv\n";

    return 0;
}