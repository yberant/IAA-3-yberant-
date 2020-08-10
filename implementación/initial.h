vector<int> rotateVector(vector<int> teams, int permutation){
    

    rotate(teams.begin()+1,teams.begin()+1+permutation,teams.end());
    reverse(teams.begin()+n/2,teams.end());

    

    return teams;
}

//generación de solución inicial no factible
vector<vector<int>> DoubleRoundRobin(){
    vector<int> teams;
    vector<int> permutes;
    vector<vector<int>> S;
    S.resize(2*(n-1));

    for(int i=0;i<2*(n-1);i++){
        S[i].resize(n);
        
    }
    for(int i=1;i<=n;i++){
        teams.push_back(i);        
    }
    for(int i=0;i<2*(n-1);i++){
        permutes.push_back(i);
    }


    random_shuffle(teams.begin(),teams.end());
    random_shuffle(permutes.begin(),permutes.end());
    //cout<<"second half :";printVector(secondHalf);
    //cout<<"permutes: ";printVector(permutes);
    //cout<<"teams: ";printVector(teams);

    for(int i=0;i<2*(n-1);i++){
        //cout<<"i: "<<i<<endl;
        int p=permutes[i];
        int inverse=0;
        if(p>=n-1){
            p=p-(n-1);
            inverse=1;
        }
        vector<int> v=rotateVector(teams,p);
        
        //cout<<"p: "<<p<<", inverse: "<<inverse<<", v: ";printVector(v);
        //cout<<"permute: "<<permutes[i]<<endl;
        //cout<<"v: ";printVector(v);
        if(!inverse){
            for(int j=0;j<n/2;j++){
                insertGame(S,v[j],v[j+n/2],i);
            }
        }
        else{
            for(int j=0;j<n/2;j++){
                insertGame(S,v[j+n/2],v[j],i);
            }
        }       
    }
    return S;

}

//cada vez que se crea una solución, pasa por acá (también revisa si es la mejor solución encontrada hasta el momento)
Solution::Solution(vector<vector<int>> S){
    schedule=S;
    dist=0;
    conflicts=0;
    cost=0;
    bestTeam=0;
    double bestCost=INFINITY;
    //cout<<"analizando matriz:"<<endl;printSolutionMatrix();
    //cout<<"creando:"<<endl;
    for(int i=1;i<=n;i++){
        //cout<<"equipo "<<i<<endl;
        double teamDist=teamScheduleDistance(S,i);
        int teamConflicts=teamTotalConflicts(S,i); 
        //cout<<"conflictos: "<<teamConflicts<<endl;
        double teamCost=routeCost(teamDist,teamConflicts);
        if(teamCost<bestCost){
            bestCost=teamCost;
            bestTeam=i;
        }
        this->conflicts+=teamConflicts;
        this->dist+=teamDist;
        this->cost+=teamCost;
/*         cout<<"costo de equipo: "<<teamCost<<", costo actual: "<<this->cost<<endl;
 */        /* if(this->conflicts==0){
            cout<<"sin conflictos"<<endl;
            printSolutionMatrix();
        }  */
        
    }
    //cout<<"costototal: "<<cost<<", num conflictos: "<<conflicts<<endl;
    this->checkIfBestSolution();
}

void Solution::checkIfBestSolution(){
    if (this->conflicts==0&&this->dist<bestSolution.dist){
        bestSolution=*this;
        factibleFound=true;
        cout<<"("<<GEN<<", "<<bestSolution.dist<<"), ";
        //this->printSolutionMatrix();
    }
}

//genera una solución inicial
Solution randomSolution(){
    vector<vector<int>> S=DoubleRoundRobin();
    Solution sol(S);
    return sol;
}