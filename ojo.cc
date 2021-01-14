#include "aux.h"
#include "ojo.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "malla.h"


Ojo::Ojo(){
    Esfera * e= new Esfera(30,30,1);
    esfera = new ObjRevolucion(e->p, e->n_instancias, e->t_sup, e->t_inf);
    textura = new Textura("ojos.jpg");
    esfera->setTextura(textura);
    
    esfera->setColor(0.0,0.0,0.0);

    Tupla4f tupla={0.0,0.75,0.75,0.75};
    Material * material =  new Material(tupla, tupla, tupla, 120.0);
    esfera->setMaterial(material);
    
}

void Ojo::draw(){
    glPushMatrix();
      glScalef(5,5,0.1);
      esfera->draw('I');
    glPopMatrix();
}
  
