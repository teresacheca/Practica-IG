#include "aux.h"
#include "objrevolucion.h"
#include "semiesfera.h"

Semiesfera::Semiesfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
 
    n_instancias=num_instancias_perf;
    t_sup=false;
    t_inf=false;

    p.clear();

    Tupla3f aux;

    aux = {0, -radio, 0}; //primer vertice
    
    std::vector<Tupla3f> p2;


    float alfa= (M_PI/2)/(num_vert_perfil);

    for(int i=0; i<num_vert_perfil+1; i++){
        aux[0]=radio*sin(alfa*i);
        aux[1]=radio*cos(alfa*i);
        aux[2]=radio*sin(alfa*i);
        p2.push_back(aux);
    }
    
    //Por el planteamiento de la práctica, el vector debe ir al revés
    //O las caras saldrán en sentido contrario
    
    for(int i=p2.size()-1; i>=0; i--){
        p.push_back(p2[i]);
    }

    Tupla4f tupla={1.0,0.0,0.0,0.0};
    material =  new Material(tupla, tupla, tupla, 10.0);
 
}

