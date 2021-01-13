#include "aux.h"
#include "luzDireccional.h"
#include "luz.h"
#include <cmath>

using namespace std;
// *****************************************************************************
//
// Clase LuzDireccional
//
// *****************************************************************************


 LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGl, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
  
    alpha = direccion[0];
    beta = direccion[1];
   
    
     Tupla4f d;
    posicion[0]=direccion[0];
    posicion[1]=direccion[1];
    posicion[2]=1.0;
    posicion[3]=0.0;           //0 porque es una luz direccional
   
    setPosicion(posicion);
    setColorAmbiente(colorAmbiente);
    setColorEspecular(colorEspecular);
    setColorDifuso(colorDifuso);
    setId(idLuzOpenGl);

    cambiarAngulo();
    
}

LuzDireccional::LuzDireccional(const Tupla2f &orientacion){}


void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha += incremento;
    cambiarAngulo();
}

void LuzDireccional::variarAnguloBeta(float incremento){
    beta += incremento;
    cambiarAngulo();
}

void LuzDireccional::cambiarAngulo(){

    //REVISAR MÉTODO

    //Pasamos alpha y beta a radianes
    float r_alpha, r_beta;
    r_alpha = (alpha*M_PI)/180;
    r_beta  = (beta*M_PI)/180;

    //Cambiamos la posicion
    //de Alpha
    posicion[1] = cos(r_alpha)*posicion[1] - sin(r_alpha)*posicion[2];
    posicion[2] = sin(r_alpha)*posicion[1] + cos(r_alpha)*posicion[2];

    //de Beta
    posicion[0] = cos(r_beta)*posicion[0] + sin(r_beta)*posicion[2];
    posicion[2] = cos(r_beta)*posicion[2] - sin(r_beta)*posicion[0];
   

}

  
	