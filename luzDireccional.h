// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzDireccional.h
// 
//
// #############################################################################

#ifndef LUZ_DIRECCIONAL_H
#define LUZ_DIRECCIONAL_H

#include "aux.h"
#include "luz.h"



class LuzDireccional : public Luz
{

   

   protected:
      float alpha;
      float beta;
      Tupla4f posicion;

   public:
      LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGl, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
      
      //Inicializar la fuente de luz
      LuzDireccional(const Tupla2f &orientacion);

      //Cambiar ángulo
      void variarAnguloAlpha(float incremento);
      void variarAnguloBeta(float incremento);
      void cambiarAngulo();

	
} ;


#endif
