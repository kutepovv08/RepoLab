#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <climits>
#include <chrono>  

using namespace std;

int costMatrix[20][20];
int totalCities;
int startCity;

struct TspResult {
    int totalCost;
    int path[21];
    double durationMs;
    long long stepsCount;
};

bool Deikstra(int P[], int n) {
    int i = n - 2;
    while (i >= 0 && P[i] >= P[i + 1]) {
        i--;
    }

    if (i < 0) return false;

    int j = n - 1;
    while (P[i] >= P[j]) {
        j--;
    }

    int temp = P[i];
    P[i] = P[j];
    P[j] = temp;

    int left = i + 1;
    int right = n - 1;
    while (left < right) {
        int t = P[left];
        P[left] = P[right];
        P[right] = t;
        left++;
        right--;
    }

    return true;
}

void generateRandomCosts(int minCost, int maxCost) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minCost, maxCost);

    for (int i = 0; i < totalCities; i++) {
        for (int j = 0; j < totalCities; j++) {
            if (i == j) {
                costMatrix[i][j] = 0;
            }
            else {
                costMatrix[i][j] = dist(gen);
            }
        }
    }
}

// ТОЧНЫЙ АЛГОРИТМ (Полный перебор)
TspResult runExactSearch(int mode) {
    auto startTime = std::chrono::high_resolution_clock::now();

    int cities[20];
    int count = 0;

    for (int i = 0; i < totalCities; i++) {
        if (i != startCity) {
            cities[count] = i;
            count++;
        }
    }

    // сорт пузырьком
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (cities[j] > cities[j + 1]) {
                int t = cities[j];
                cities[j] = cities[j + 1];
                cities[j + 1] = t;
            }
        }
    }

    TspResult result;
    result.totalCost = (mode == 0) ? INT_MAX : -1;
    result.stepsCount = 0;

    int bestSubPath[20];

    do {
        result.stepsCount++;

        int currentCost = 0;
        int lastCity = startCity;

        for (int i = 0; i < count; i++) {
            int nextCity = cities[i];
            currentCost += costMatrix[lastCity][nextCity];
            lastCity = nextCity;
        }
        currentCost += costMatrix[lastCity][startCity];

        if (mode == 0) {
            if (currentCost < result.totalCost) {
                result.totalCost = currentCost;
                for (int i = 0; i < count; i++) bestSubPath[i] = cities[i];
            }
        }
        else {
            if (currentCost > result.totalCost) {
                result.totalCost = currentCost;
                for (int i = 0; i < count; i++) bestSubPath[i] = cities[i];
            }
        }

    } while (Deikstra(cities, count));

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = endTime - startTime;
    result.durationMs = elapsed.count();

    result.path[0] = startCity;
    for (int i = 0; i < count; i++) {
        result.path[i + 1] = bestSubPath[i];
    }
    result.path[count + 1] = startCity;

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Точный перебор реализован и готов к тестам." << endl;
    return 0;
}