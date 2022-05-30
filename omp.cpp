#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;

typedef long long ll;

int f(int k, int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i * 5 % n;
    }
    nth_element(arr, arr + k, arr + n);
    int ans = arr[k];
    delete[] arr;
    return ans;
}

int main(int argc, char** argv)
{
    int ProcNum = 12;//, ProcRank;


    int n = 40000;

    int* arr = new int[n];
    ll begin;
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
    begin = clock();
    int part = n / ProcNum;

    int* bufNumbers = new int[part];
    int* ans = new int[n];
#pragma omp parallel for
    for (int i = 0; i < ProcNum; i++) {
        for (int j = i * part; j < (i + 1) * part; j++) {
            ans[j] = f(j, n);
        }
    }
    for (int i = 0; i < n; i++) {
        //cout << ans[i] << " ";
    }
    auto end = clock();
    auto time = (end - begin) * 1.0 / CLOCKS_PER_SEC;
    cout << "Time: " << time << "s\n";

}