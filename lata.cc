#include "aux.h"
#include "lata.h"


Lata::Lata(){
   Cilindro * ci =  new Cilindro(30,30,1,1);
   cilindro = new ObjRevolucion(ci->p, ci->n_instancias, ci->t_sup, ci->t_inf);

   textura = new Textura("lata.jpg");
   cilindro->setTextura(textura);

    Tupla4f tupla={0.0,0.75,0.75,0.75};
   Material * material =  new Material(tupla, tupla, tupla, 120.0);
   cilindro->setMaterial(material);
   cilindro->setColor(1.0,0,0);

}

void Lata::draw(){
   glPushMatrix();
      glScalef(30,100,30);
      cilindro->draw('D');
   glPopMatrix();
}
  
