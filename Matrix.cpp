#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> multiplyMatrix(vector<vector<int>>& a, vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    vector<vector<int>> c(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            for (int k = 0; k < a[0].size(); k++) 
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

vector <int> multiplyMatrixByVector(vector<vector<int>>& a, vector<int>& b) {
    int n = a.size();
    int m = b.size();
    vector<int> c(n, 0);
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            c[i] += a[i][j] * b[j];
    return c;
}