#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;


struct Element {
    char num; 
    char letter;
    char evenNum1;
    char evenNum2; 
};


bool vallidation(string input) {

    if (input.length() == 4 
        &&
        (
            input[0] >= '0' && input[0] <= '9'
        )
        &&
        (
            (input[1] >= 'a' && input[1] <= 'z') ||
            (input[1] >= 'а' && input[1] <= 'я') ||
            (input[1] >= 'A' && input[1] <= 'Z') ||
            (input[1] >= 'А' && input[1] <= 'Я')
        )
        &&
        (
            (input[2] >= '0' && input[2] <= '9') && (input[2] - '0') % 2 == 0
            )
        &&
        (
            input[3] >= '0' && input[3] <= '9') && (input[3] - '0') % 2 == 0
        )
    {
        return true;
    }

    else {
        return false;
    }
}


void inputArray(vector<Element>& arr, int size) {

    Element elem;

    cout << "(c - цифра/ b - буква / i - четная цифра)" << endl;

    for (int i = 0; i < size; ++i) {
        cout << "Элемент " << i << ": ";
        string input;
        cin >> input;

        if (vallidation(input) == true) {
            elem.num = input[0];
            elem.letter = input[1];
            elem.evenNum1 = input[2];
            elem.evenNum2 = input[3];
            arr.push_back(elem);
        }
        else {
            cout << "Ошибка ввода" << endl;
            i--;
        }
    }
}


void printArray(const vector<Element>& arr) {

    if (arr.size() == 0) {
        cout << "Пустое множество" << endl;
    }
    else {
        for (int i = 0; i < arr.size(); ++i) {
            cout << "Элемент #" 
            << i 
            << ": " 
            << arr[i].num 
            << arr[i].letter 
            << arr[i].evenNum1 
            << arr[i].evenNum2 
            << endl;
        }
    }

}


void removeNonUnique(vector<Element>& arr) {

    vector<Element> uniqueElements;

    for (int i = 0; i < arr.size(); ++i) {
        bool isUnique = true;

        for (int j = 0; j < uniqueElements.size(); ++j) {
            if (arr[i].num == uniqueElements[j].num &&
                arr[i].letter == uniqueElements[j].letter &&
                arr[i].evenNum1 == uniqueElements[j].evenNum1 &&
                arr[i].evenNum2 == uniqueElements[j].evenNum2) {
                isUnique = false;
                break;
            }
        }

        if (isUnique == true) {
            uniqueElements.push_back(arr[i]);
        }
    }

    arr.clear();
    for (size_t i = 0; i < uniqueElements.size(); ++i) {
        arr.push_back(uniqueElements[i]);
    }
}


void unionArrays(vector<Element>& result, vector<Element>& arr1, vector<Element>& arr2) {

    for (int i = 0; i < arr1.size(); ++i)
        result.push_back(arr1[i]);
    for (int i = 0; i < arr2.size(); ++i)
        result.push_back(arr2[i]);
    removeNonUnique(result);
}


void interArrays(vector<Element>& result, vector<Element>& arr1, vector<Element>& arr2) {

    for (int i = 0; i < arr1.size(); ++i) {
        for (int j = 0; j < arr2.size(); ++j) {
            if (arr1[i].num == arr2[j].num &&
                arr1[i].letter == arr2[j].letter &&
                arr1[i].evenNum1 == arr2[j].evenNum1 &&
                arr1[i].evenNum2 == arr2[j].evenNum2
                ) 
            {
                result.push_back(arr1[i]);
            }
            
        }
    }

}


void complArrays(vector<Element>& result, vector<Element>& arr1, vector<Element>& arr2) {

    for (int i = 0; i < arr1.size(); ++i) {
        bool found_same = false;
        for (int j = 0; j < arr2.size(); ++j) {
            if (arr1[i].num == arr2[j].num &&
                arr1[i].letter == arr2[j].letter &&
                arr1[i].evenNum1 == arr2[j].evenNum1 &&
                arr1[i].evenNum2 == arr2[j].evenNum2
                ) 
            
            {
                found_same = true;
                break;
            }
        }

        if (found_same == false) {
            result.push_back(arr1[i]);
        }
    }
}


void symDifArrays(vector<Element>& result, vector<Element>& arr1, vector<Element>& arr2) {

    vector<Element> complA_B;
    vector<Element> complB_A;

    complArrays(complA_B, arr1, arr2);
    complArrays(complB_A, arr2, arr1);

    unionArrays(result, complA_B, complB_A);
}


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int size_a, size_b;
    int choice = 0;

    vector<Element> a;
    vector<Element> b;
    vector<Element> unionArr;
    vector<Element> interArr;
    vector<Element> complA_B;
    vector<Element> complB_A;
    vector<Element> symDif;

    cout << "Введите размер множества A: ";
    cin >> size_a;

    inputArray(a, size_a);
    removeNonUnique(a);
    cout << endl;

    cout << "Введите размер множества B: ";
    cin >> size_b;
    inputArray(b, size_b);
    removeNonUnique(b);
    cout << endl;

    while (true) {

        cout << "Выберите операцию: \n"
             << "1 - Объединение\n"
             << "2 - Пересечение\n"
             << "3 - Дополнение А/B B/A\n"
             << "4 - Симметрическая разность\n"
             << "5 - Вывод множества A\n"
             << "6 - Вывод множества B\n"
             << "Выбор: ";
        cin >> choice;

        switch (choice) {

        case 1: 
            unionArrays(unionArr, a, b);
            cout << "Элементы объедененного множества: " << endl;
            printArray(unionArr);
            cout << endl;
            break;

        case 2:
            interArrays(interArr, a, b);
            cout << "Элементы пересеченного множества: " << endl;
            printArray(interArr);
            cout << endl;
            break;

        case 3:
            complArrays(complA_B, a, b);
            cout << "Дополнение A\\B: " << endl;
            printArray(complA_B);
            cout << endl;

            complArrays(complB_A, b, a);
            cout << "Дополнение B\\A: " << endl;
            printArray(complB_A);
            cout << endl;
            break;

        case 4:
            symDifArrays(symDif, a, b);
            cout << "Симметрическая разность множеств А и B: " << endl;
            printArray(symDif);
            cout << endl;
            break;

        case 5:
            cout << "Вывод элементов множества А: " << endl;
            printArray(a);
            cout << endl;
            break;
            
        case 6:
            cout << "Вывод элементов множества B: " << endl;
            printArray(b);
            cout << endl;
            break;

        default:
            cout << "Ошибка ввода" << endl;

        }
    }

    return 0;

}