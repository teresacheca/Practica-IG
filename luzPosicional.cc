#include "aux.h"
#include "luz.h"
#include "luzPosicional.h"

using namespace std;
// *****************************************************************************
//
// Clase LuzPosicional
//
// *****************************************************************************

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGl, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    Tupla4f p;
    p[0]=posicion[0];
    p[1]=posicion[1];
    p[2]=posicion[2];
    p[3]=1.0;           //1 porque es una luz posicional
    
    setPosicion(p);
    setColorAmbiente(colorAmbiente);
    setColorEspecular(colorEspecular);
    setColorDifuso(colorDifuso);
    setId(idLuzOpenGl);
    
}

LuzPosicional::LuzPosicional(const Tupla3f & posicion){
  
}

void LuzPosicional::mover(Tupla3f p){
    
    Tupla4f pos;
    pos[0]=p[0];
    pos[1]=p[1];
    pos[2]=p[2];
    pos[3]=1.0;

    setPosicion(pos);
    cout << "Posicion " << pos << endl;
    
}


	
	