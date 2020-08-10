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
#include <cstdlib>

using namespace::std;

int n;
double w;
vector<vector<double>> D;
const double EPSILON=2.7182818;
bool factibleFound=false;
int GEN;

int poblationSize;
int selectedIndividuals;
int maxGenerations;

double pcross;
double pmut;

class Solution{
    public:
        vector<vector<int>> schedule;
        double dist;
        int conflicts;
        double cost;
        int bestTeam;
        Solution(vector<vector<int>> S);
        Solution(){};
        Solution(double d){dist=d;}
        void checkIfBestSolution();
        void printSolutionMatrix();
        void printSolutionInfo();
};

Solution bestSolution(INFINITY);


void printMatrix(vector<vector<int>> M);
void printVector(vector<int> v);
void swapElements(vector<vector<int>> &M, int x1, int y1,int x2,int y2);
void insertGame(vector<vector<int>> & S, int Ti, int Tj, int r);
vector<int> rotateVector(vector<int> teams, int permutation);
vector<vector<int>> DoubleRoundRobin();

double teamScheduleDistance(vector<vector<int>> S, int j);
double distance(int i, int j);
int teamAtMostConflicts(vector<vector<int>> S, vector<int> & conflictedRows, vector<int> & conlfictedColumns, int team);
int teamNoRepeatConflicts(vector<vector<int>> S, vector<int> & conflictedRows, vector<int> & conlfictedColumns, int team);
int teamTotalConflicts(vector<vector<int>> S, int team);

void add(vector<int> & arr, int value);
void addValues(vector<int> & arr, vector<int> & values);
void resetVector(vector<int> & v);
int TeamConflicts(vector<vector<int>> S, int team);
double routeCost(double distance, int conflicts);


void swapRounds(vector<vector<int>> & S, int i, int j);
void swapTeams(vector<vector<int>> & S, int i, int j);


int teamToIndex(int t);
int findByHash(vector<int> hashVector, int rival);
vector<int> hashVectorPSR(vector<int> column);


int greedyFix(vector<vector<int>> & S);
bool updateBest(vector<vector<int>> candidateS,vector<vector<int>> & bestS,int & bestConflicts, double & bestDistance);







