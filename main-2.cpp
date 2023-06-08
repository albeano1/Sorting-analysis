#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

int dataComparisons = 0;
int loopControlComparisons = 0;
int dataAssignments = 0;
int loopControlAssignments = 0;
int otherOperations = 0;
int totalOperations = 0;

void resetCounters() {
    dataComparisons = 0;
    loopControlComparisons = 0;
    dataAssignments = 0;
    loopControlAssignments = 0;
    otherOperations = 0;
    totalOperations = 0;
}

void selectionSort(vector<int> &vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            dataComparisons++;
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }
        dataAssignments++;
        swap(vec[i], vec[minIndex]);
        otherOperations++;
    }
}

void earlyExitBubbleSort(vector<int> &vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        bool sorted = true;
        for (int j = 0; j < n - i - 1; j++) {
            dataComparisons++;
            loopControlComparisons++;
            if (vec[j] > vec[j + 1]) {
                sorted = false;
                dataAssignments++;
                swap(vec[j], vec[j + 1]);
                otherOperations++;
            }
        }
        loopControlAssignments++;
        if (sorted) break;
    }
}

void insertionSort(vector<int> &vec) {
    int n = vec.size();
    for (int i = 1; i < n; i++) {
        int key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            dataComparisons++;
            loopControlComparisons++;
            dataAssignments++;
            vec[j + 1] = vec[j];
            j--;
        }
        dataAssignments++;
        vec[j + 1] = key;
        otherOperations++;
    }
}

vector<int> generateRandomVector(int size) {
    vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = rand();
    }
    return vec;
}

void randomizeVector(vector<int> &vec) {
for (int i = 0; i < vec.size(); i++) {
vec[i] = rand() % vec.size();
}
}

double measureSortingTime(void (*sortFunction)(vector<int> &), vector<int> vec) {
    clock_t startTime = clock();
    resetCounters();
    sortFunction(vec);
    clock_t endTime = clock();
    double elapsedTime = double(endTime - startTime) / CLOCKS_PER_SEC;
    totalOperations = dataComparisons + loopControlComparisons + dataAssignments + loopControlAssignments + otherOperations;
    return elapsedTime;
}

int main() {
    int sizes[] = {500, 1000, 5000, 10000};
    vector<vector<int> > vectors;
    vectors.push_back(vector<int>(sizes[0]));
    vectors.push_back(vector<int>(sizes[1]));
    vectors.push_back(vector<int>(sizes[2]));
    vectors.push_back(vector<int>(sizes[3]));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            vectors[i][j] = j;
        }
    }

    cout << "Sorting Already Sorted Vectors" << endl;
    cout << "Selection Sort:" << endl;
    cout << "Size\tTime\tData Comp\tControl Comp\tData Assign\tControl Assign\tOther\tTotal" << endl;
    for (int i = 0; i < 4; i++) {
        double time = measureSortingTime(selectionSort, vectors[i]);
        cout << sizes[i] << "\t" << time << "\t" << dataComparisons << "\t" << loopControlComparisons << "\t" << dataAssignments << "\t" << loopControlAssignments << "\t" << otherOperations << "\t" << totalOperations << endl;
    }

    cout << "Early Exit Bubble Sort:" << endl;
    cout << "Size\tTime\tData Comp\tControl Comp\tData Assign\tControl Assign\tOther\tTotal" << endl;
    for (int i = 0; i < 4; i++) {
        double time = measureSortingTime(earlyExitBubbleSort, vectors[i]);
        cout << sizes[i] << "\t" << time << "\t" << dataComparisons << "\t" << loopControlComparisons << "\t" << dataAssignments << "\t" << loopControlAssignments << "\t" << otherOperations << "\t" << totalOperations << endl;
    }

    cout << "Insertion Sort:" << endl;
    cout << "Size\tTime\tData Comp\tControl Comp\tData Assign\tControl Assign\tOther\tTotal" << endl;
    for (int i = 0; i < 4; i++) {
        double time = measureSortingTime(insertionSort, vectors[i]);
        cout << sizes[i] << "\t" << time << "\t" << dataComparisons << "\t" << loopControlComparisons << "\t" << dataAssignments << "\t" << loopControlAssignments << "\t" << otherOperations << "\t" << totalOperations << endl;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            vectors[i][j] = sizes[i] - j - 1;
    }
}
cout << "Descending order:" << endl;
cout << "Size\tTime\tData Comp\tControl Comp\tData Assign\tControl Assign\tOther\tTotal" << endl;
for (int i = 0; i < 4; i++) {
    double time = measureSortingTime(insertionSort, vectors[i]);
    cout << sizes[i] << "\t" << time << "\t" << dataComparisons << "\t" << loopControlComparisons << "\t" << dataAssignments << "\t" << loopControlAssignments << "\t" << otherOperations << "\t" << totalOperations << endl;
}

for (int i = 0; i < 4; i++) {
    randomizeVector(vectors[i]);
}

cout << "Random data:" << endl;
cout << "Size\tTime\tData Comp\tControl Comp\tData Assign\tControl Assign\tOther\tTotal" << endl;
for (int i = 0; i < 4; i++) {
    double time = measureSortingTime(insertionSort, vectors[i]);
    cout << sizes[i] << "\t" << time << "\t" << dataComparisons << "\t" << loopControlComparisons << "\t" << dataAssignments << "\t" << loopControlAssignments << "\t" << otherOperations << "\t" << totalOperations << endl;
}

return 0;
}