#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"
using namespace std;
Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
    float espacio_vertices=altura/num_vert_perfil;
    std::vector<Tupla3f> perfil;
    Tupla3f aux;

    aux={0,(-altura/2), 0};
    perfil.push_back(aux);
    for(int i=0; i<num_vert_perfil+1; i++){
        aux={radio, ((-altura/2)+i*espacio_vertices), radio};
        perfil.push_back(aux);
    }

    aux={0, altura/2, 0};
    perfil.push_back(aux);


    const bool conTapas=true;

    n_instancias=num_instancias_perf;
    t_sup=true;
    t_inf=true;
    p.clear();
    p.resize(perfil.size());

    for(int i=0; i<perfil.size(); i++){
        p[i]=perfil[i];
    }

 
}

