#include "aux.h"
#include "objrevolucion.h"
#include "trompa.h"


Trompa::Trompa(){
    Esfera * e = new Esfera(30,30,1);
    Semiesfera * s = new Semiesfera(30,30,1);
    Cilindro * ci =  new Cilindro(30,30,1,1);

    esfera = new ObjRevolucion(e->p, e->n_instancias, e->t_sup, e->t_inf);
    semiesfera = new ObjRevolucion(s->p, s->n_instancias, s->t_sup, s->t_inf);
    cilindro = new ObjRevolucion(ci->p, ci->n_instancias, ci->t_sup, ci->t_inf);

    esfera->setColor(0.6,0.6,0.6);
    semiesfera->setColor(0.75,0.75,0.75);
    cilindro->setColor(0.75,0.75,0.75);

    textura= new Textura("elefante.jpg");
    esfera->setTextura(textura);
    cilindro->setTextura(textura);
    semiesfera->setTextura(textura);

    Tupla4f tupla={0.0,0.75,0.75,0.75};
    Material * material =  new Material(tupla, tupla, tupla, 120.0);
    esfera->setMaterial(material);
    semiesfera->setMaterial(material);
    cilindro->setMaterial(material);

    trompita = new Trompita();

    
}
void Trompa::draw(){
     glPushMatrix();
        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glTranslatef(0,54,0);
                glScalef(20,50,20);
                semiesfera->draw('I');
            glPopMatrix();
            glTranslatef(0,47,0);
            modificaGiroTrompaX();
            modificaGiroTrompaZ();
            glTranslatef(0,-47,0);
            glPushMatrix();
                
                glPushMatrix();
                    glTranslatef(0,47,0);
                    glScalef(20,20,20);
                    esfera->draw('I');
                glPopMatrix();
            glPushMatrix();
                glScalef(20,80,20);
                cilindro->draw('I');
            glPopMatrix();
            glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-50,0);
            trompita->draw();
        glPopMatrix();
    glPopMatrix();

}

void Trompa::modificaGiroTrompaZ(){
      float giro= giroTrompaZ;
      if(giro <= 50 && giro>=-50){
         glRotatef(giro,0,0,1);
         
      }else{
         giroTrompaZ=0;
      }
  }

   void Trompa::modificaGiroTrompaX(){
      float giro= giroTrompaX;
      if(giro <= 50 && giro>=-50){
         glRotatef(giro,1,0,0);
      }else{
         giroTrompaX=0;
      }
   }

   void Trompa::setGiroTrompaX(float valor){
        giroTrompaX+=valor;
     }
     void Trompa::setGiroTrompaZ(float valor){
        giroTrompaZ+=valor;
     }

   void Trompa::modificaGiroTrompaPequeniaZ(){
     trompita->modificaGiroTrompaPequeniaZ();
  }

   void Trompa::modificaGiroTrompaPequeniaX(){
     trompita->modificaGiroTrompaPequeniaX();
   }

void Trompa::setGiroTrompaPequeniaX(float valor){
        trompita->setGiroTrompaPequeniaX(valor);
     }
      void Trompa::setGiroTrompaPequeniaZ(float valor){
        trompita->setGiroTrompaPequeniaZ(valor);
     }
  

  float Trompa::getGiroTrompaX(){
   return giroTrompaX;
}

float Trompa::getGiroTrompaZ(){
   return giroTrompaZ;
}

float Trompa::getGiroTrompaPequeniaX(){
   trompita->getGiroTrompaPequeniaX();
}
float Trompa::getGiroTrompaPequeniaZ(){
   trompita->getGiroTrompaPequeniaZ();
}

 