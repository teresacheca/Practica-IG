#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
 
    n_instancias=num_instancias_perf;
    t_sup=false;
    t_inf=false;

    p.clear();

    Tupla3f aux;

    aux = {0, -radio, 0}; //primer vertice
    
    std::vector<Tupla3f> p2;


    float alfa= M_PI/(num_vert_perfil);

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

 /*   float a, b, x, y, z;
    ct.clear();
    ct.resize(p.size());
   Tupla2f coordenada;
   for(int i=0; i<p.size(); i++){
       std::cout << i << " " << p[i] << "\n";
      aux = p[i];
      x=aux[0];
      y=aux[1];
      z=aux[2];
      a=atan2(z,x);
      b=atan2(y, sqrt(pow(x,2)+pow(z,2)));
      coordenada[0]=(0.5+(a/2*M_PI));
      coordenada[1]=(0.5+(b/M_PI));
      ct.push_back(coordenada);
   }
*/
 
}

