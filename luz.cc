#include "aux.h"
#include "luz.h"

using namespace std;
// *****************************************************************************
//
// Clase Luz
//
// *****************************************************************************

void Luz::activar(){
    glEnable(id);
    id = getId();
    posicion = getPosicion();

   // gl_FragColor = (color);
    glLightfv(id, GL_AMBIENT , colorAmbiente);
    glLightfv(id, GL_DIFFUSE , colorDifuso);
    glLightfv(id, GL_SPECULAR , colorEspecular);

    glLightfv(id, GL_POSITION, posicion);

}


void Luz::setPosicion(Tupla4f p){
    posicion = p;
}

void Luz::setColorAmbiente(Tupla4f cA){
    colorAmbiente = cA;
}

void Luz::setId(GLenum i){
    id = i;
}

void Luz::setColorEspecular(Tupla4f cE){
    colorEspecular=cE;
}

void Luz::setColorDifuso(Tupla4f cD){
    colorDifuso = cD;
}

Tupla4f Luz::getPosicion(){
    return posicion;
}

Tupla4f Luz::getColorAmbiente(){
    return colorAmbiente;
}

GLenum Luz::getId(){
    return id;
}

Tupla4f Luz::getColorEspecular(){
    return colorEspecular;
}

Tupla4f Luz::getColorDifuso(){
    return colorDifuso;
}

