#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool** initarray(int n) {
    int dim = n;
    bool **arr = new bool *[dim];
    int i, j;
    for (i = 0; i < dim; i++) {
        arr[i] = new bool[dim];
    }
    return arr;
}
int whereis(int arr[],int len,int i){
    for(int j=0;j<len;j++){
        if(arr[j]==i)
            return j;
    }
    return -1;
}
bool bpm(bool ** bpGraph, int u,
         bool seen[], int matchR[],int N)
{
    for (int v = 0; v < N; v++)
    {
        if (bpGraph[u][v] && !seen[v])
        {
            seen[v] = true;
            if (matchR[v] < 0 || bpm(bpGraph, matchR[v],seen, matchR,N))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}
int * maxBPM(bool** bpGraph,int  matchR[],int N)
{
    int result = 0;
    for (int u = 0; u < N; u++)
    {
        bool seen[N];
        memset(seen, 0, sizeof(seen));
        if (bpm(bpGraph, u, seen, matchR,N))
            result++;
    }
    return matchR;
}
int main() {
    int i, j, dim;
    cin >> dim;
    int crr[dim];
    for (int l = 0; l <dim ; ++l) {
        crr[l]=l;
    }
    bool **arr = initarray(dim);
    for (i = 0; i < dim; i++) {
        bool val;
        for (j = 0; j < dim; j++) {
            cin >> val;
            arr[i][j] = val;
        }
    }
    vector<bool> visited(dim, false);
    cout << "\n ";
    int matchR[dim];
    memset(matchR, -1, sizeof(matchR));
    int matchL[dim];
    memset(matchL, -1, sizeof(matchL));
    maxBPM(arr,matchR,dim);
    for(int i=0;i<dim;i++){
        if(matchR[i]>-1)
            matchL[matchR[i]]=i;

    }



    if(whereis(matchL,dim,-1)!=-1){
        cout<<-1;
        return 0;
    }
    int x[dim],y[dim];
    for (int i=0 ;i < dim; i++) x[i]=i,y[i]=i;

    for (int col=0 ;col < dim; col++) {
        int row = matchR[col];
        if(x[row] != col)
            cout << 'R' << ' ' << x[row] + 1 << ' ' << col + 1 << endl;
        int t = y[col];
        swap(y[x[row]], y[col]);
        swap(x[t], x[row]);
    }


    return 0;
}