#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
 
   
// inicializar la tabla de vértices
 
 //Cubo de lado 100

float l=50;

 v =  {  { -l, -l, +l },   // vértice 0
      { +l, -l, +l },      // vértice 1
      { +l, +l, +l },      // vértice 2
      { -l, +l, +l },      // vértice 3
      { -l, -l, -l },      // vértice 4
      { +l, -l, -l },      // vértice 5
      { +l, +l, -l },      // vértice 6
      { -l, +l, -l }       // vértice 7
  };

  // inicializar la tabla de caras o triángulos:
  // (es importante en cada cara ordenar los vértices en sentido contrario
  //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   

  f = { { 0, 1, 3 }, { 3, 1, 2 },   //cara delantera
  { 1, 5, 2 }, { 2, 5, 6 },         //cara derecha
  { 5, 4, 6 }, { 6, 4, 7 },         //cara trasera
  { 4, 0, 7 }, { 7, 0, 3 },         //cara izquierda
  { 3, 2, 7 }, { 7, 2, 6 },         //cara de arriba
  { 4, 5, 0 }, { 0, 5, 1}} ;       //cara de abajo
  

  //color cian: 
  float r, g, b;
  r=0.2;
  g=0.9;
  b=0.95;
 
  color= {
      {r,g,b},  {r,g,b},
      {r,g,b},  {r,g,b},
      {r,g,b},  {r,g,b}, 
      {r,g,b},  {r,g,b}

   };

    setColor(r,g,b);
    Tupla4f tupla={0.0,0.0,1.0,0.0};
    material =  new Material(tupla, tupla, tupla, 120.0);

    ct.resize(v.size());
    ct = {
      {0.0,1.0}, {0.5,1.0}, 
      {0.5,0.0}, {0.0,0.0},
       {0.5,1.0},  {1.0,1.0},
        {1.0,0.0},  {0.5,0.0}
    };
}

