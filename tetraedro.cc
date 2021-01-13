#include "aux.h"
#include "malla.h"
#include "tetraedro.h"
#include<cmath>

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices

   //Calcular el baricentro G=(v1+v2+v3+v4)/4

   //Tetraedro regular con altura de 100
   float lado=sqrt(2000);
   float altura=100;





   v={{0,(-altura/3),(altura*2)/3},      //vértice 0 cara de abajo
    {(altura*2)/3,-(altura/3), -(altura/3)},      //vértice 1 cara de abajo
    {-(altura*2)/3, -(altura/3),-(altura/3) },    //vértice 2 cara de abajo
      {0,(altura*2)/3,0}        //vértice 3 arriba
      };
    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   f={ {0,1,3},   //cara derecha
       {1,2,3},   //cara trasera
       {2,0,3},   //cara izquierda
       {0,1,2}    //cara de abajo
       };

 r=0;
 g=0;
 b=0;
  color= {
      {r,g,b},
      {r,g,b},
      {r,g,b},
      {r,g,b},     
   };

   Tupla4f tupla={0.0,0.0,1.0,0.0};
   material =  new Material(tupla, tupla, tupla, 120.0);

     ct.resize(v.size());
    ct = {
      {0.0,1.0}, {0.5,1.0}, 
      {0.5,0.0}, {0.0,0.0},
     
    };

    
}

