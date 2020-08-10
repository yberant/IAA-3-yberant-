void swapRounds(vector<vector<int>> & S, int k, int l){
    if(k==l)return;
    vector<int> auxRound=S[k];
    S[k]=S[l];
    S[l]=auxRound;
}

void swapTeams(vector<vector<int>> & S, int i, int j){//i,j entre 1 y n
    if(i==j)return;
    for(int round=0;round<2*(n-1);round++){
        int rivalI=S[round][i-1];
        int rivalJ=S[round][j-1];
        if(abs(rivalI)==j || abs(rivalJ)==i) continue;
            
        //cout<<"round "<<round<<": ";
        //cout<<rivalI<<","<<rivalJ<<endl;
        if(rivalI>0){//rival de I está jugando de visita
            insertGame(S,j,abs(rivalI),round);
        } else insertGame(S,abs(rivalI),j,round);//rival de I está jugando de local
        if(rivalJ>0){//rival de J está jugando de visita
            insertGame(S,i,abs(rivalJ),round);
        } else insertGame(S,abs(rivalJ),i,round);//rival de J está jugando de local
        
    }
    
    /*int rivalJ=S[round][j];
            int rivalI=S[round][i];
            if(rivalI>0){//rival de I está jugando de visita
                insertGame(S,j,abs(rivalI),round);
            } else insertGame(S,abs(rivalI),j,round);//rival de I está jugando de local
            if(rivalJ>0){//rival de J está jugando de visita
                insertGame(S,i,abs(rivalJ),round);
            } else insertGame(S,abs(rivalJ),i,round);//rival de J está jugando de local*/
}


//función "llave"
int teamToIndex(int t){
    if(t>0) return t-1;
    else return(-t+n-1);
}


int findByHash(vector<int> hashVector, int rival){
    int index=teamToIndex(rival);
    return hashVector[index];
}

vector<int> hashVectorPSR(vector<int> column){
    vector<int> hashVector;
    hashVector.resize(2*n);
    for(int c=0;c<2*n;c++){
        hashVector[c]=-1;
    }
    for(int r=0;r<column.size();r++){

        int index=teamToIndex(column[r]);
        hashVector[index]=r;
    }
    
    return hashVector;
}
