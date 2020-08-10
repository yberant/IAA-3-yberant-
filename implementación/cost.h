double distance(int i, int j){//recibe numeros de equipos, no indices (hay que restar)
    /*cout<<"locacion actual:"<<i<<endl;
    cout<<"me muevo a:"<<j<<endl;
    cout<<"recorro una distancia de:"<< D[i-1][j-1]<<endl;*/
    return D[i-1][j-1];
}

double teamScheduleDistance(vector<vector<int>> S, int j){
    double dist=0;
    int actual=j;
    int next=j;
    for(int i=0;i<2*(n-1);i++){
        int t=S[i][j-1];
        //cout<<endl<<"siguiente rival: "<<t<<endl;
        if(t<0){//juego de visita
            next=abs(t);
        }
        else{//juego como local
            next=j;
        }
        dist+=distance(actual,next);
        //cout<<"distancia actual recorrida por el equipo "<<j<<": "<<dist<<endl;
        actual=next;
    }
    next=j;
    dist+=distance(actual,j);
    //cout<<"distancia final recorrida por el equipo "<<j<<": "<<dist<<endl;
    return dist;
}




//actualiza rondas y equipos que están en conflicto  por la restriccion atMost
int teamAtMostConflicts(vector<vector<int>> S, int team){
    int cost=0;
    
    int consecutive=0;
    int sign;
    if (S[0][team-1]>0) sign=1;//juego de local
    else sign=-1;//juego de visita
    for(int i=0;i<2*(n-1);i++){
        //cout<<"S["<<i<<"]["<<j<<"]: "<<S[i][j]<<endl;
        if(S[i][team-1]*sign>0) consecutive++;//está jugando del mismo rol que en el juego anterior
        else{
            consecutive=1;
            sign=-sign;
        }
        if(consecutive>3){//u=3
            cost++;
        }
            //cout<<"consecutive: "<<consecutive<<", sign: "<<sign<<" cost: "<<cost<<endl;
    }
    //cout<<"costo: "<<cost<<endl;
    return cost;
}

//actualiza rondas y equipos que están en conflicto  por la restriccion noRepeat
int teamNoRepeatConflicts(vector<vector<int>> S, int team){
    double cost=0;
    int actual=0;
    int next=0;
    for(int i=0;i<2*(n-1);i++){
        next=S[i][team-1];
        if(abs(actual)==abs(next)) cost++;
        actual=next;

    }
    
    return cost;//se divide por dos porque se estaría contando en los dos equipos en donde ocurre cada conflicto
}

int teamTotalConflicts(vector<vector<int>> S, int team){
    int CT=teamNoRepeatConflicts(S, team);
    int CR=teamAtMostConflicts(S, team);
    return CT+CR;
}


double routeCost(double distance, int conflicts){
    if(conflicts==0){
        return distance;
    }
    else{
        int c=(double)conflicts;
        //cout<<"c: "<<c<<endl;
        double f=1+(sqrt(c)*log(c))/2;//ver anagnostooulos para mas info
        //scout<<distance<<", "<<w*f<<", "<<c<<endl;
        return sqrt(pow(distance,2)+pow(w*f,2));//ojo que esta es la versión de Nourollahi de la función objetivo
    }
}