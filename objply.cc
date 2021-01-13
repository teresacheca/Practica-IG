#include "objply.h"
#include "ply_reader.h"
#include "malla.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );

   Tupla3f aux;

   //Color negro para las figuras
  /* aux[0]=0;
   aux[1]=0;
   aux[2]=0;*/
   color.clear();
   color.resize(v.size());
  /* for(int i=0; i<v.size(); i++){
      color[i]=aux;
   }*/
  
   
   Tupla4f tupla={0.0,0.0,1.0,0.0};
    material =  new Material(tupla, tupla, tupla, 120.0);
}


