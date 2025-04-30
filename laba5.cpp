#include <iostream>
#include <vector>
#include <locale>

using namespace std;


void inputMatrix(vector<vector<int>>& matrix, int n) {

    string elem;

    cout << "Введите элементы (0 или 1)" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            while (true) {
                cin >> elem;
                if (elem == "0" || elem == "1") {
                    matrix[i][j] = elem == "0" ? 0 : 1;
                    break;
                }
                else {
                    cout << "Ошибка ввода." << endl;
                }
            }

        }
    }

}


void outputMatrix(vector<vector<int>>& matrix, int n) {

    cout << "\nМатрица достижимости:\n" << endl;

    for (int j = 0; j < n; ++j) {
        cout << j + 1 << " ";
    }
    cout << endl;
    for (int j = 0; j < n; ++j) {
        cout << "—" << " ";
    }
    cout << endl;


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "| " << i + 1 << endl;
    }

    cout << endl;
}


void changeToReachabilityMatrix(vector<vector<int>>& matrix, int n) {

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
            }
        }
    }
}

int main() {

    setlocale(LC_ALL, "Russian");
    

    int n;
    cout << "Введите размерность матрицы(n): ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));

    inputMatrix(matrix, n);
    changeToReachabilityMatrix(matrix, n);
    outputMatrix(matrix, n);

    return 0;
}