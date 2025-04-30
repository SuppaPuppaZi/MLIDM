#include <iostream>
#include <vector>
#include <string>
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
    
    cout << "\nМатрица:\n" << endl;

         
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


bool checkReflexive(vector<vector<int>>& matrix, int n) {

    for (int x = 0; x < n; ++x) {
        if (matrix[x][x] != 1) {
            return false;
        }
    }
    return true;
}


bool checkSymmetric(vector<vector<int>>& matrix, int n) {

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (matrix[x][y] != matrix[y][x]) {
                return false;
            }
        }
    }
    return true;
}


bool checkAntisymmetric(vector<vector<int>>& matrix, int n) {

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if ( matrix[x][y] == 1 && matrix[y][x] == 1 && x != y) {
                    return false;     
            }
        }
    }
    return true;
    
}


bool checkTransitive(vector<vector<int>>& matrix, int n) {

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (matrix[x][y] == 1) {
                for (int z = 0; z < n; ++z) {
                    if (matrix[y][z] == 1 && matrix[x][z] != 1) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


int main() {

    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите размерность матрицы(n): ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));

    inputMatrix(matrix, n);
    outputMatrix(matrix, n);

    cout << "Свойства введенного отношения: " << endl;

    cout << "Рефлексивность: " << (checkReflexive(matrix, n) ? "Да" : "Нет") << endl;
    cout << "Симметричность: " << (checkSymmetric(matrix, n) ? "Да" : "Нет") << endl;
    cout << "Кососимметричность: " << (checkAntisymmetric(matrix, n) ? "Да" : "Нет") << endl;
    cout << "Транзитивность: " << (checkTransitive(matrix, n) ? "Да" : "Нет") << endl;

    return 0;
}

