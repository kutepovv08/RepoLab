#include <iostream>
#include <vector>
#include <random>

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

// Алгоритм Дейкстры для перестановок (строго по слайду лекции)
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

// Заполнение матрицы случайными значениями 
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

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Базовый генератор и структуры готовы." << endl;
    return 0;
}
