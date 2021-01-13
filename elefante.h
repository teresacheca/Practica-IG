// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: tetraedro.h

//
// #############################################################################

#ifndef ELEFANTE_H_INCLUDED
#define ELEFANTE_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "semiesfera.h"
#include "cilindro.h"
#include "cono.h"
#include "textura.h"

// *****************************************************************************
//
// clases elefante
//
// *****************************************************************************

// *****************************************************************************
// Tetraedro con centro en el origen 

class Elefante: public Malla3D
{
   public:
      Elefante();
      void draw();
      void cuerno();
      void trompa();
      void ojo();
      void oreja();
      void cola();
      void pata();
      void cuerpo();
      void tronco();
      void cabeza();
    
      Malla3D dibujaCuerno();
      ObjRevolucion * esfera;
      ObjRevolucion * semiesfera;
      ObjRevolucion * cono;
      ObjRevolucion * cilindro;

      float giroCabezaX;
      float giroCabezaY;
      float giroTrompaX;
      float giroTrompaZ;
      float giroPatas;
      float giroTrompaPequeniaX;
      float giroTrompaPequeniaZ;
      bool agacha;

      float cabezaXmax;
      float cabezaYmax;
      float trompaXMax;
      float trompaZMax;
      float patasMax;
      float trompitaXMax;
      float trompitaYMax;

      Textura * piel;
      Textura * marfil;
      Textura * ojos;
      Textura * orejas;

     

      void modificaGiroTrompaX();
      void modificaGiroTrompaZ();
      void modificaGiroCabezaX();
      void modificaGiroCabezaY();
      void modificaGiroPatas();
      void modificaGiroTrompaPequeniaX();
      void modificaGiroTrompaPequeniaZ();
      void giroPatasDerechas();   
      void giroPatasIzquierdas();
      void agacharse();
  

     void setGiroPatas(float valor);
     void setGiroTrompaX(float valor);
     void setGiroTrompaZ(float valor);
     void setGiroCabezaX(float valor);
     void setGiroCabezaY(float valor);
     void setGiroTrompaPequeniaX(float valor);
     void setGiroTrompaPequeniaZ(float valor);
     void setAgacharse(bool valor);
     bool getAgacharse();

     float getGiroPatas();
     float getGiroTrompaX();
     float getGiroTrompaZ();
     float getGiroCabezaX();
     float getGiroCabezaY();
     float getGiroTrompaPequeniaX();
     float getGiroTrompaPequeniaZ();

     float getPatasMax();
     float getTrompaXMax();
     float getTrompaZMax();
     float getCabezaXMax();
     float getCabezaYMax();
     float getTrompaPequeniaXMax();
     float getTrompaPequeniaZMax();

} ;




#endif
