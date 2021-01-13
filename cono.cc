#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"
#include <math.h>

using namespace std;

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
 

    n_instancias = num_instancias_perf;
    t_sup = true;
    t_inf=true;
    //El número de trozos en los que se divide el perfil es num_vert_perfil-1


    //Suponemos el cono centrado en el origen
    float h= altura/2;

    float r = radio;

    //Primero introducimos el primer vertice que corresponde con la base
    
    p.clear();
    Tupla3f aux;
    //aux = {r, -h, r}; //Primer vértice

    //sabiendo la altura y el radio, podemos calcular la generatriz del cono con el teorema de pitágoras:
    float g = sqrt(pow(altura,2) + pow(r,2));


    //Con la generatris, podemos calcular el ángulo alfa y beta (ángulos opuestos a r y h respectivamente);
    float alfa = asin((r*sin(90)/g));
    float beta = 180-alfa-90;
    float h_auxiliar;
    float x;

    //Utilizamos el teorema del seno para calcular el resto de lados
    for(int i=0; i<num_vert_perfil; i++){
        float h2 = -h + ((altura*i)/(num_vert_perfil-1));
   
            x = h + h2;
            h_auxiliar = altura-x;
       
       
       r= (h_auxiliar*sin(alfa))/sin(beta);

       aux[0]=r;
       aux[1]=h2;
       aux[2]=r;

       p.push_back(aux);

    }

    Tupla4f tupla={0.0,0.0,1.0,0.0};
    material =  new Material(tupla, tupla, tupla, 120.0);

  
 
}

