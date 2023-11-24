#include <iostream>
#include <vector>
#define inf 999999
#define N 4
using namespace std;
 
class aresta{
public:
    int v1,v2,peso;
};
 
class vertice{
public:
    int valor, dist, pred;
    bool visit;
};
 
class grafo{
public:
    vector<vertice> vertices;
    vector<aresta> arestas;
};
 
int i = 0;
 
grafo criaGrafo(int m[][N]){
    grafo G;    
    aresta A;
    vertice V;
    for(int i = 0; i < N; i++){
        V.valor = i;
        for(int j = 0; j < N; j++){
            if(m[i][j]){
                A.v1 = i;
                A.v2 = j;
                A.peso = m[i][j];
                G.arestas.push_back(A);
            }
        }
        G.vertices.push_back(V);
    }
    return G;
}
 
vertice GetMin(vector<vertice> &Q, grafo G){
    vertice vMin;
    vMin.dist = inf;
    int posMinQ;
    for(int i=0; i<Q.size(); i++){
        Q.at(i).dist = G.vertices.at(Q.at(i).valor).dist;
        if(Q.at(i).dist < vMin.dist){
            vMin = Q.at(i);
            posMinQ = i;
        }
    }
    Q.erase(Q.begin() + posMinQ);
    return vMin;
}

vector<aresta> getAr(vector<aresta> A, vertice V){
    vector<aresta> auxv2;
    for(int i=0; i<A.size(); i++){
        if(A.at(i).v1 == V.valor){
            auxv2.push_back(A.at(i));
        }
    }
    return auxv2;
}

void DJIKSTRA(grafo G, int s){
    for(int i = 0; i < G.vertices.size(); i++){
        G.vertices.at(i).dist = inf;
        G.vertices.at(i).visit = false;
    }
    G.vertices.at(s).dist = 0;
    G.vertices.at(s).pred = G.vertices.at(s).valor;
    
    vector<vertice> aux;
    for(int i = 0; i < G.vertices.size(); i++){
        aux.push_back(G.vertices.at(i));
    }

    while(!aux.empty()){
        vertice vAux = GetMin(aux, G);
        G.vertices.at(vAux.valor).visit = true;
        vector<aresta> ArAux = getAr(G.arestas, vAux);

        for(int i = 0; i < ArAux.size(); i++){
            if(G.vertices.at(ArAux.at(i).v2).visit == false && G.vertices.at(ArAux.at(i).v1).dist != inf && G.vertices.at(ArAux.at(i).v1).dist + ArAux.at(i).peso < G.vertices.at(ArAux.at(i).v2).dist){
                G.vertices.at(ArAux.at(i).v2).dist = G.vertices.at(ArAux.at(i).v1).dist + ArAux.at(i).peso;
                G.vertices.at(ArAux.at(i).v2).pred = G.vertices.at(ArAux.at(i).v1).valor;
            }
        }
    }
    //impressão
    cout << "Djikastra: " << endl;
    cout << "SSSP: (vertice, pred, dist)" << endl;
    cout << "Vertice inicial = " << s << endl;
    for(int i = 0; i < G.vertices.size(); i++){
        if(G.vertices.at(i).pred == inf){
            G.vertices.at(i).pred = 0;
        }
        if(i == 0){
            cout << "{ ";
        }
        cout << "(" << G.vertices.at(i).valor << ", " << G.vertices.at(i).pred << ", " << G.vertices.at(i).dist << ") ";
        if(i == (G.vertices.size())-1){
            cout << "}" << endl;
        }
    }
}
 
// int matriz[][N]={{0,10,0,0,5},
//                  {0,0,1,0,2},
//                  {0,0,0,4,0},
//                  {7,0,6,0,0},
//                  {0,3,9,2,0}};
 
int matriz[][N]={{0,3,7,5},
                 {0,0,3,1},
                 {0,0,0,0},
                 {0,0,1,0}};

int main(){
    grafo G = criaGrafo(matriz);
    DJIKSTRA(G, 0);
    return 0;
}