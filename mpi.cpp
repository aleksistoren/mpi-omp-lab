#include <iostream>
#include <ctime>
#include "mpi.h"
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS

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
    int ProcNum, ProcRank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    ll n;
    ll begin;
    if (ProcRank == 0)
    {
        cout << "Input n: ";
        cin >> n;
        begin = clock();
    }
    MPI_Bcast(&n, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    

    int* ans = new int[n];
    for (ll i = ProcRank; i <= n; i += ProcNum) {
        ans[i] = f(i, n);
        if (ProcRank != 0) {
            MPI_Send(&ans[i], 1, MPI_LONG_LONG, 0, i, MPI_COMM_WORLD);
        }
        //cout << i << " " << ProcRank << " "<<n<<endl;
    }
    if (ProcRank == 0)
    {
        ll nt;
        MPI_Status status;

        for (int procRank=1; procRank < ProcNum; procRank++)
        for (int i = procRank; i <= n; i += ProcNum) {
            //cout << procRank << endl;
            if (procRank != 0) {
                MPI_Recv(&ans[i], 1, MPI_LONG_LONG, procRank, i, MPI_COMM_WORLD, &status);
            }
        }

        auto end = clock();
        cout << "Time: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s\n";
    }

    MPI_Finalize();
}