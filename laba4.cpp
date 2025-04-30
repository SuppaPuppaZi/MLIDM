#include <iostream>
#include <vector>
#include <limits.h>
#include <locale>

using namespace std;


bool checkV(int v_begin, int v_end, int v) {

    if (v_begin < 0 || v_end < 0) {
        cout << "Ошибка ввода. Вы ввели отрицательные вершины" << endl;
        return false;
    }

    if (v_begin >= v || v_end >= v) {
        cout << "Ошибка ввода. Номер вершины должен быть от 0 до " << v - 1 << endl;
        return false;
    }

    return true;
}


void inputGraph(vector<vector<int>>& graph, int v) {

    cout << "Введите матрицу смежности (веса рёбер):\n";
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            while (true) {
                cin >> graph[i][j];
                if (graph[i][j] >= 0) {
                    break; 
                }
                else {

                }
                cout << "Ошибка ввода" << endl;
            }
        }
    }
}



bool checkSymmetric(vector<vector<int>>& graph) {

    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (graph[i][j] != graph[j][i]) {
                return false;
            }
        }
    }
    return true;
}


void outputGraph(vector<vector<int>>& graph, int v) {
    
    cout << "\n    ";
    for (int j = 0; j < v; j++) {
        cout << j << "   ";
    }
    cout << "\n   ";
    for (int j = 0; j < v; j++) {
        cout << "----";
    }
    cout << "-";

    
    for (int i = 0; i < v; i++) {
        cout << "\n" << i << " |";
        for (int j = 0; j < v; j++) {
            
            if (graph[i][j] < 10) {
                cout << " ";
            }
            cout << " " << graph[i][j] << " ";
        }
        cout << "|";
    }

    cout << "\n\n";
}


void printPath(vector<int>& path, vector<vector<int>>& graph, int v) {

    vector<int> fullPath;
    int cur = v;
    int from_v, to_v;

    while (cur != -1) {
        fullPath.push_back(cur);
        cur = path[cur];
    }

    if (fullPath.size() == 1) {
        cout << fullPath[0] << " -> " << fullPath[0] << " (стоимость: 0)" << endl;
    }

    for (int i = fullPath.size() - 2; i >= 0; i--) {
        from_v = fullPath[i + 1];
        to_v = fullPath[i];
        cout << from_v << " -> " << to_v << " (стоимость: " << graph[from_v][to_v] << ")" << endl;
    }
}


int findMinDistance(vector<int>& dist, vector<bool>& visited, int v) {

    int minDist = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < v; i++) {
        if (!visited[i] && dist[i] <= minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}


void dekstrAlgorythm(vector<vector<int>>& graph,int v, int v_begin, int v_end) {

    vector<int> dist(v, INT_MAX);
    vector<bool> visited(v, false);
    vector<int> path(v, -1);
    int curMinV;

    dist[v_begin] = 0;
    for (int i = 0; i < v; i++) {
        if (graph[v_begin][i] != 0) {
            dist[i] = graph[v_begin][i];
            path[i] = v_begin;
        }
    }


    for (int count = 0; count < v - 1; count++) {
        curMinV = findMinDistance(dist, visited, v);
        visited[curMinV] = true;

        for (int i = 0; i < v; i++) {
            if (
                !visited[i] && 
                graph[curMinV][i] != 0 && 
                dist[curMinV] != INT_MAX && 
                dist[curMinV] + graph[curMinV][i] < dist[i]
                ) 
            {
                dist[i] = dist[curMinV] + graph[curMinV][i];
                path[i] = curMinV;
            }
        }
    }

    cout << "Кратчайший путь от вершины " << v_begin << " до вершины " << v_end << ":" << endl;

    if (dist[v_end] == INT_MAX) {
        cout << "Путь не существует\n";
    }
    else {
        printPath(path, graph, v_end);
        cout << "Суммарная стоимость пути: " << dist[v_end] << endl;
    }
}


int main() {

    setlocale(LC_ALL, "Russian");

    int v, v_begin, v_end;
    cout << "Введите количество вершин: ";
    cin >> v;

    vector<vector<int>> graph(v, vector<int>(v, 0));

    inputGraph(graph, v);

    if (checkSymmetric(graph)) {
        cout << "Вы ввели неориентированный граф" << endl;
        return 0;
    }

    cout << "Введите начальную вершину: ";
    cin >> v_begin;
    cout << "Введите конечную вершину: ";
    cin >> v_end;

    if (!checkV(v_begin, v_end, v)) {
        return 1;
    }

    outputGraph(graph, v);

    dekstrAlgorythm(graph, v, v_begin, v_end);

    return 0;
}