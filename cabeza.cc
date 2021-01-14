#include "aux.h"
#include "cabeza.h"


Cabeza::Cabeza(){
    Esfera * e = new Esfera(30,30,1);

    esfera = new ObjRevolucion(e->p, e->n_instancias, e->t_sup, e->t_inf);

    trompa = new Trompa();
    ojo = new Ojo();
    cuerno = new Cuerno();
    oreja = new Oreja();


    Tupla4f tupla={0.0,0.75,0.75,0.75};
    Material * material =  new Material(tupla, tupla, tupla, 120.0);
    esfera->setMaterial(material);

    textura= new Textura("elefante.jpg");
    esfera->setColor(0.75,0.75,0.75);
    esfera->setTextura(textura);
}

void Cabeza::draw(){
   glPushMatrix();

      glPushMatrix();
         glTranslatef(0,-70,0);
         glPushMatrix();
         glScalef(0.75,0.75,0.75);
            glTranslatef(-sin(45)*25,0,sin(45)*25);
            cuerno->draw();
         glPopMatrix();
         glPushMatrix();      
            glScalef(0.75,0.75,0.75);
            glTranslatef(sin(45)*25,0,sin(45)*25);
            cuerno->draw();
         glPopMatrix();
      glPopMatrix();

      //CABEZA
      glPushMatrix();
         glScalef(50,50,50);
         esfera->draw('I');
      glPopMatrix();

      //TROMPA
      glPushMatrix();
         glScalef(0.5,0.5,0.5);
         glTranslatef(0,-50,20);
         glTranslatef(0,-50,sin((90*M_PI/180))*70);
         trompa->draw();
      glPopMatrix();

      //OJOS
      glPushMatrix();
         glTranslatef(-cos(60)*25, -sin(60)*25, -cos(60)*50);
         ojo->draw();
      glPopMatrix();
      glPushMatrix();
         glTranslatef(cos(60)*25, -sin(60)*25, -cos(60)*50);
         ojo->draw();
      glPopMatrix();
      
      //OREJAS
      glPushMatrix();
         glPushMatrix();
            glTranslatef(60,10,0);
            oreja->draw();
         glPopMatrix();
         glPushMatrix();
            glTranslatef(-60,10,0);
            oreja->draw();
         glPopMatrix();
      glPopMatrix();

   glPopMatrix();
}
	
void Cabeza::modificaGiroTrompaZ(){
     trompa->modificaGiroTrompaZ();
  }

   void Cabeza::modificaGiroTrompaX(){
     trompa->modificaGiroTrompaX();
   }

   void Cabeza::setGiroTrompaX(float valor){
      trompa->setGiroTrompaX(valor);
     }
     void Cabeza::setGiroTrompaZ(float valor){
        trompa->setGiroTrompaZ(valor);
     }

     void Cabeza::modificaGiroTrompaPequeniaZ(){
     trompa->modificaGiroTrompaPequeniaZ();
  }

   void Cabeza::modificaGiroTrompaPequeniaX(){
     trompa->modificaGiroTrompaPequeniaX();
   }

   void Cabeza::setGiroTrompaPequeniaX(float valor){
      trompa->setGiroTrompaPequeniaX(valor);
     }
     void Cabeza::setGiroTrompaPequeniaZ(float valor){
        trompa->setGiroTrompaPequeniaZ(valor);
     }

float Cabeza::getGiroTrompaX(){
   trompa->getGiroTrompaX();
}

float Cabeza::getGiroTrompaZ(){
   trompa->getGiroTrompaZ();
}

float Cabeza::getGiroTrompaPequeniaX(){
   trompa->getGiroTrompaPequeniaX();
}
float Cabeza::getGiroTrompaPequeniaZ(){
   trompa->getGiroTrompaPequeniaZ();
}


