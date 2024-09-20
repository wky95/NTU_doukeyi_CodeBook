struct Matrix{
    int n, m;
    vector<vector<int>> arr;
 
    Matrix(int _n, int _m){
        n = _n;
        m = _m;
        arr.resize(n, vector<int>(m));
    }
 
    Matrix operator * (const Matrix B){
        Matrix ret(n, B.m);
 
        for (int i=0 ; i<n ; i++){
            for (int j=0 ; j<B.m ; j++){
                for (int k=0 ; k<m ; k++){
                    ret.arr[i][j] += arr[i][k]*B.arr[k][j];
                    ret.arr[i][j] %= MOD;
                }
            }
        }
 
        return ret;
    }
};
