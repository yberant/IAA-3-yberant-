//CRUCE: 
//el torneo S1 copia el orden de juegos para el equipo team del torneo S2, haciendo los swaps necesarios 
void copyTeamOrder(vector<vector<int>> & S1, vector<vector<int>> S2, int team){
    vector<int> teamColumn;
    for(int i=0;i<2*(n-1);i++) teamColumn.push_back(S1[i][team-1]);
    //cout<<"columna: ";printVector(teamColumn);
    vector<int> hashVector=hashVectorPSR(teamColumn);//arreglo hash que indica en que ronda juega el equipo team contra cada equipo, en S1
    //cout<<"hashvector: ";printVector(hashVector);
    for(int i=0;i<2*(n-1);i++){
       // cout<<"i: "<<i<<endl;
        if(S1[i][team-1]==S2[i][team-1])continue;
        //cout<<"en s1 juega contra"<<S1[i][team-1]<<", en s2 juega contra "<<S2[i][team-1]<<endl;
        int roundToChange=findByHash(hashVector,S2[i][team-1]);//busco en que ronda se juega contra el equipo que juega contra team en S2, en la ronda r

        //cout<<"ronda a cambiar: "<<roundToChange<<endl;

        //actualiza el hashvector
        int index1=teamToIndex(S1[i][team-1]);//indice indica en que ronda se juega contra s1[i][team-1]
        int index2=teamToIndex(S2[i][team-1]);
        //cout<<"index1: "<<index1<<", index2: "<<index2<<endl;

        hashVector[index1]=roundToChange;
        hashVector[index2]=i;

        //realiza cambio de fila en equipo con partialSwapRounds
        swapRounds(S1,team,i);

        //cout<<"hasvector: ";printVector(hashVector);

    } 
}


//cruza dos soluciones aplicando copyTeamOrder. Int es un binario aleatorio
void crossSolutions(Solution S1, Solution S2, Solution & newS1, Solution & newS2){
    vector<vector<int>> newTournament1=S1.schedule;
    vector<vector<int>> newTournament2=S2.schedule;
    //int Best=false;

    int rand1, rand2;
        
    copyTeamOrder(newTournament1,S2.schedule,S2.bestTeam);
    copyTeamOrder(newTournament2,S1.schedule,S1.bestTeam);

    //aparte de crear dos nuevas soluciones, también revisa si alguna es la mejor encontrada hasta el momento
    Solution ns1=Solution(newTournament1);
    Solution ns2=Solution(newTournament2);

    //guarda los hijos en ns1 y ns2
    newS1=ns1;
    newS2=ns2;
}

void crossing(vector<Solution> & solutions){

    random_shuffle(solutions.begin(),solutions.end());
    vector<Solution> offspring;
    int otherIndex=-1;
    int pair=0;
    for(int i=0;i<solutions.size();i++){//cruzo pares aleatorios de soluciones
        double random=(rand()%10000)/10000.0;
        if(random<pcross){
            //cout<<"!"<<endl;
            pair++;
            if(pair>=2){
                pair=0;
                Solution ns1;
                Solution ns2;
                crossSolutions(solutions[otherIndex],solutions[i],ns1,ns2);//cruza 2 soluciones, almacendandolas en ns1 y ns2
                
                offspring.push_back(ns1);
                offspring.push_back(ns2);
            }
            else{
                otherIndex=i;
            }
        }
    }
    //soluciones "originales" e hijas se unen, para pertenecer a la sig. generación. Algunas serán mutadas
    solutions.insert(solutions.end(),offspring.begin(),offspring.end());
    
}

//MUTACIÓN
//revuelve los ordenes de equipos de una solución, separando a los equipos en pares aleaorios y aplicando swapTeams
Solution shuffleTeamOrder(Solution solution){
    vector<int> teamNumbers;
    vector<vector<int>> tournament=solution.schedule;
    for(int i=0;i<n;i++){
        teamNumbers.push_back(i+1);
    }
        
    //revuelve equipos (ej(N=4): [1,2,3,4]-> [3,1,4,2])
    random_shuffle(teamNumbers.begin(),teamNumbers.end());
    for(int i=0;i<n;i+=2){//junto los equipos en parejas aleatorias, y cambio los ordenes de juego de esos equipos
        swapTeams(tournament,teamNumbers[i],teamNumbers[i+1]);
        //siguiendo con el ejemplo anterior, se haría un swapteams(3,1) y swapteams(4,2)
    }
    Solution newS(tournament);//aparte de crear una nueva solución, también revisa si es la mejor encontrada hasta el momento
    return newS;

}


void mutation(vector<Solution> & Solutions){
    
    for(int s=0;s<Solutions.size();s++){
        double randMutation=(rand()%100000)/100000.0;
        if(randMutation<pmut){
            //cout<<"mut!"<<endl;
            Solution mutedSolution=shuffleTeamOrder(Solutions[s]);
            Solutions[s]=mutedSolution;
            
        }
    }
    
}
