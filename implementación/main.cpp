#include<stdlib.h>
#include<ctime>
#include<cmath>
#include<cstddef>
#include<iterator>
#include<algorithm> 
#include<fstream>
#include<chrono>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<fstream>
#include <sstream>
#include"tda.h"
#include"initial.h"
#include"basic.h"
#include"cost.h"
#include"permutations.h"
#include"transformation.h"




int ReadNumbers( const string & s, vector<int> & v) {
    istringstream is( s );
    double n;
    while( is >> n ) {
        v.push_back( n );
    }
    return v.size();
}

//fuente: https://www.quora.com/How-do-I-read-a-matrix-from-a-file-in-C++
vector<vector<double>> distanceMatrix(string arch){

    ifstream File; 
    vector<vector<double>> d;

    std::string line;
    vector<int> v;

    File.open(arch);
    if (File.is_open()){
        int i=0;
        getline(File, line);
        n =ReadNumbers(line, v);
        cout << "N:" << n << endl;
        for ( i=1;i<32767;i++){
            if (!getline(File, line)) break;//TODO: OJO CON EL COMPILADOR ACÁ!!!!!!!!!
            ReadNumbers( line, v );
            
        }
        File.close();
    }
    else{
        cout << "file open failed";
    }
    for (int i=0;i<n;i++){
        vector<double> row;
        for (double j=0;j<n;j++){
            row.push_back(v[i*n+j]);
            //cout<<v[i*n+j]<<"\t"
        }
        //cout << endl;
        d.push_back(row);
    }
    return d;
}


int main(int argc ,char* argv[]){

    // ./main semilla archivo tamañoPoblación, numeroSeleccionados, numeroGeneraciones, probCruzamiento, probMutación, alpha, W (default)

    srand(atoi(argv[1]));
    cout<<"seed: "<<argv[1]<<endl;

    string f=string(argv[2]);
    string arch="instancias/"+string(argv[2]);
    D=distanceMatrix(arch);
    w=2500;
    //auto start = chrono::high_resolution_clock::now();
    
    
    vector<Solution> poblation;
    poblationSize=atoi(argv[3]);cout<<"poblationSize: "<<poblationSize<<endl;
    float selectedPortion=atof(argv[4]);
    selectedIndividuals=int(selectedPortion*poblationSize);cout<<"selected Individuals: "<<selectedIndividuals<<endl;
    
    maxGenerations=atoi(argv[5]);cout<<"maxGenerations: "<<maxGenerations<<endl;

    pcross=atof(argv[6]);cout<<"pcross: "<<pcross<<endl;
    pmut=atof(argv[7]);cout<<"pmut: "<<pmut<<endl;
    

    float alpha=atof(argv[8]);
    cout<<"alpha: "<<alpha<<endl;
    
    cout<<"argc: "<<argc<<endl;
    if(argc<=9) w=9000;
    else w=atof(argv[9]);
    cout<<"w: "<<w<<endl;
    

    auto start = chrono::high_resolution_clock::now();
    
    
    //elitismo
    for(int generation=0;generation<maxGenerations;generation++){
        GEN=generation;
        //if(generation%50==0) cout<<"generación: "<<generation<<endl;
        //lleno a la población (en la generación 0 parte vacío, en el resto de generaciones tiene algunos otros)
        while(poblation.size()<poblationSize){
            Solution newS=randomSolution();
            poblation.push_back(newS);
        }

        sort(poblation.begin(),poblation.end(),[](const Solution & s1, const Solution &s2)->bool{
            return s1.cost<s2.cost;
            //return (s1.conflicts<s2.conflicts || (s1.conflicts==s2.conflicts && s1.dist<s2.dist));
        });
        //cout<<"mejores conflictos: "<<poblation[0].conflicts<<endl;

        vector<Solution> elitismSolutions;


        //Selección
        for(int s=0;s<selectedIndividuals;s++){
            int N=poblation.size();
            double randomX=(rand()%100000)/100000.0;
            //cout<<"randomX: "<<randomX<<" index selected: "<<round(N-pow((pow(N,3)*(1-pow(randomX,3))),1.0/3))<<endl;
            int selectedIndex=round(N-pow((pow(N,alpha)*(1-pow(randomX,alpha))),1.0/alpha));
            //cout<<selectedIndex<<endl;
            elitismSolutions.push_back(poblation[selectedIndex]);
            poblation.erase(poblation.begin()+selectedIndex);
        }
        //cout<<"esize before: "<<elitismSolutions.size()<<endl;

        crossing(elitismSolutions);
        //cout<<"esize after: "<<elitismSolutions.size()<<endl;

        mutation(elitismSolutions);
        

        poblation=elitismSolutions;


    }

    auto stop = chrono::high_resolution_clock::now(); 

    if(factibleFound){
        cout<<"mejor solución encontrada:"<<endl;
        bestSolution.printSolutionInfo();
        //bestSolution.printSolutionMatrix();
    }
    else cout<<"no se encontró una mejor solución :(";

    auto duration=chrono::duration_cast<chrono::microseconds>(stop-start);
    cout<<"tiempo de ejecucion:"<<duration.count()/1000000.0<<" segundos"<<endl;
    

    
    return 0;
}


