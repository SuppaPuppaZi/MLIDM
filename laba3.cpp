#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Relation {
    char elem1;
    char elem2;
};


void inputArray(vector<char>& arr, int size) {


    for (int i = 0; i < size; ++i) {
        char chr;
        cout << "Введите элемент: ";
        cin >> chr;

        arr.push_back(chr);
    }
}


void removeNonUnique(vector<char>& arr) {

    vector<char> uniqueElements;

    for (int i = 0; i < arr.size(); ++i) {
        bool isUnique = true;

        for (int j = 0; j < uniqueElements.size(); ++j) {
            if (arr[i] == uniqueElements[j]){
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


bool relationVallidation(Relation rel, vector<char>a, vector<char>b) {

    bool inA = (find(a.begin(), a.end(), rel.elem1) != a.end());
    bool inB = (find(b.begin(), b.end(), rel.elem2) != b.end());

    if (inA == true && inB == true) {
        return true;
    }
    
    if (inA == false || inB == false) {
        cout << "Ошибка ввода" << endl;
        return false;
    }

    return false;
}


void inputRelation(vector<Relation>& relation, int par_count, vector<char>a, vector<char>b) {

    Relation rel;
    cout << "Пара элементов = (Элемент из первого множества / Элемент из второго множества)" << endl;
    for (int i = 0; i < par_count; ++i) {
        cout << "Введите пару элементов: ";
        cin >> rel.elem1 >> rel.elem2;
        if ((relationVallidation(rel, a, b)) == true) {
            relation.push_back(rel);
        }
        else {
            --i;
        }
        
    }
    
}


void isFunction(vector<Relation> relation, vector<char>a) {
    
    bool isFunc = true;
    int cnt = 0;

    for (int i = 0; i < relation.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            if (relation[i].elem1 == a[j]) {
                cnt++;
                break;
            }
        }
    }
    
    if (cnt != a.size()) {
        isFunc = false;
    }
    else {
        for (int i = 0; i < relation.size(); ++i) {
                for (int j = i + 1; j < relation.size(); ++j) {
                    if (relation[i].elem1 == relation[j].elem1) {
                        isFunc = false;
                        break;
                    }
                }
                if (isFunc == false) {
                break;
                }
            }
    }


    if (isFunc == true) {
        cout << "Отношение является функцией" << endl;
    }
    else {
        cout << "Отношение не является функцией" << endl;
    }
}




int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int size_a, size_b;
    int par_count = 0;
    int choice = 0;

    vector<char> a;
    vector<char> b;
    vector<Relation> relation;

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

    cout << "Введите кол-во пар: ";
    cin >> par_count;
    inputRelation(relation, par_count, a, b);
    cout << endl;

    isFunction(relation, a);

    return 0;

}