#include "aux.h"
#include "suelo.h"

Suelo::Suelo(){
     
   cubo = new Cubo();
   textura = new Textura("suelo.jpg");
   cubo->setTextura(textura);

   Tupla4f tupla={0.0,0.75,0.75,0.75};
   Material * material =  new Material(tupla, tupla, tupla, 120.0);
   cubo->setMaterial(material);
   cubo->setColor(0.0,1.0,0.0);

}

void Suelo::draw(){
   glPushMatrix();
      glScalef(1000, 0.1,1000);
      cubo->draw('D', cubo->getCaras().size());
   glPopMatrix();
}
