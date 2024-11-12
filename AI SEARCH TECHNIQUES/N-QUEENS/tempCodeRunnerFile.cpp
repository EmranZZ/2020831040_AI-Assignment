#include<bits/stdc++.h>
using namespace std;

const int N = 8; 

bool isSafe(vector<vector<int>> & board, int row, int col){
    
    for(int y=0; y<col; y++){
        if(board[row][y]==1) return false; 
    }
    for(int x=row, y=col ; x>=0 && y>=0 ; x--, y--){
        if(board[x][y]==1) return false;
    }
    for(int x=row, y=col ; x<N && y>=0; x++, y--){
        if(board[x][y]==1) return false;
    }
    return true;
}

bool solveNqueens(vector<vector<int>> & board, int col){
    if(col == N){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        return true;
    }

    for(int i=0; i<N; i++){
        if(isSafe(board, i, col)){
            board[i][col] == 1; 
            if(solveNqueens(board, col+1)){
                return true;
            }
            board[i][col]==0; 
        }
    }
    return false; 
}

int main(){
    vector<vector<int>> board(N, vector<int>(N,0));
    if(!solveNqueens(board, 0)){
        cout<<"Solution not found"<<endl;
    }
    return 0;
}