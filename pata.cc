#include "aux.h"
#include "pata.h"


Pata::Pata(){
   
   Semiesfera * s = new Semiesfera(30,30,1);
   Cilindro * ci =  new Cilindro(30,30,1,1);

   semiesfera = new ObjRevolucion(s->p, s->n_instancias, s->t_sup, s->t_inf);
   cilindro = new ObjRevolucion(ci->p, ci->n_instancias, ci->t_sup, ci->t_inf);

    textura = new Textura("elefante.jpg");
    semiesfera->setTextura(textura);
    cilindro->setTextura(textura);
    
    cilindro->setColor(0.75,0.75,0.75);
    semiesfera->setColor(0.75,0.75,0.75);


   Tupla4f tupla={0.0,0.75,0.75,0.75};
   Material * material =  new Material(tupla, tupla, tupla, 120.0);
   semiesfera->setMaterial(material);
   cilindro->setMaterial(material);

 
}

void Pata::draw(){
     glPushMatrix();
      glPushMatrix();
         glScalef(20,50,20);
         cilindro->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,25,0);
         glScalef(20,20,20);
         semiesfera->draw('I');
      glPopMatrix();
   glPopMatrix();
}

		