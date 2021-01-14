#include "aux.h"
#include "objrevolucion.h"
#include "trompita.h"


Trompita::Trompita(){
    Esfera * e = new Esfera(30,30,1);
    Semiesfera * s = new Semiesfera(30,30,1);

    esfera = new ObjRevolucion(e->p, e->n_instancias, e->t_sup, e->t_inf);
    semiesfera =  new ObjRevolucion(s->p, s->n_instancias, s->t_sup, s->t_inf);

    textura= new Textura("elefante.jpg");
    esfera->setTextura(textura);
    semiesfera->setTextura(textura);

    Tupla4f tupla={0.0,0.75,0.75,0.75};
    Material * material =  new Material(tupla, tupla, tupla, 120.0);
    esfera->setMaterial(material);
    semiesfera->setMaterial(material);

    esfera->setColor(0.6,0.6,0.6);
    semiesfera->setColor(0.75,0.75,0.75);
}

void Trompita::draw(){
      glPushMatrix();
            
            glPushMatrix();
               glScalef(20,20,20);
               esfera->draw('I');
            glPopMatrix();
            
            glPushMatrix();   
            modificaGiroTrompaPequeniaX();
            modificaGiroTrompaPequeniaZ();
               glTranslatef(0,-7,0);
               glRotatef(180,0,0,1);
               glScalef(20,50,20);
               semiesfera->draw('I');
            glPopMatrix();
         glPopMatrix();
}

void Trompita::setGiroTrompaPequeniaX(float valor){
        giroTrompaPequeniaX+=valor;
     }
      void Trompita::setGiroTrompaPequeniaZ(float valor){
        giroTrompaPequeniaZ+=valor;
     }
  
	void Trompita::modificaGiroTrompaPequeniaX(){
        float giro= giroTrompaPequeniaX;
      if(giro <= 50 && giro>=-50){
         glRotatef(giro,1,0,0);
      }else{
         giroTrompaPequeniaX=0;
      }
    
 }
   void Trompita::modificaGiroTrompaPequeniaZ(){
        float giro= giroTrompaPequeniaZ;
      if(giro <= 50 && giro>=-50){
         glRotatef(giro,0,0,1);
      }else{
         giroTrompaPequeniaZ=0;
      }
    
 }

float Trompita::getGiroTrompaPequeniaX(){
   return giroTrompaPequeniaX;
}
float Trompita::getGiroTrompaPequeniaZ(){
   return giroTrompaPequeniaZ;
}