#include "aux.h"
#include "malla.h"
#include "elefante.h"
#include "esfera.h"
#include<cmath>

/*-----------------------------------------CONSTRUCTOR--------------------------------------------*/

Elefante::Elefante()
{
   Esfera * e = new Esfera(30,30,1);
   Semiesfera * s = new Semiesfera(30,30,1);
   Cono * co = new Cono(30,30,1,1);
   Cilindro * ci =  new Cilindro(30,30,1,1);

   esfera = new ObjRevolucion(e->p, e->n_instancias, e->t_sup, e->t_inf);
   semiesfera = new ObjRevolucion(s->p, s->n_instancias, s->t_sup, s->t_inf);
   cono = new ObjRevolucion(co->p, co->n_instancias, co->t_sup, co->t_inf);
   cilindro = new ObjRevolucion(ci->p, ci->n_instancias, ci->t_sup, ci->t_inf);

   esfera->setColor(0.75,0.75,0.75);
   semiesfera->setColor(0.75,0.75,0.75);
   cono->setColor(0.75,0.75,0.750);
   cilindro->setColor(0.75,0.75,0.75);

   giroPatas=0;
   giroTrompaX=0;
   giroTrompaZ=0;
   giroCabezaX=0;
   giroCabezaY=0;
   giroTrompaPequeniaX=0;
   giroTrompaPequeniaZ=0;
   agacha=false;

   cabezaXmax=30;
   cabezaYmax=60;
   trompaXMax=50;
   trompaZMax=50;
   patasMax=60;
   trompitaXMax=50;
   trompitaYMax=50;

   Tupla4f tupla={0.0,0.75,0.75,0.75};
   Material * material =  new Material(tupla, tupla, tupla, 120.0);
   esfera->setMaterial(material);
   semiesfera->setMaterial(material);
   cono->setMaterial(material);
   cilindro->setMaterial(material);

}
 

/*-------------------------------------------MÉTODO DRAW-----------------------------------------------*/

void Elefante::draw(){
   //Grados de libertad
   //cabeza();
   //cuerpo();
  
      
   agacharse();
   
  // glTranslatef(0,-100,0);
   glPushMatrix();
     
      glPushMatrix();
         glTranslatef(0,0,200);
         glTranslatef(0,87.5,0);
         glScalef(1.5,1.5,1.5);
         //Grados de libertad de la cabeza
         cabeza();
      glPopMatrix();

      glPushMatrix();
         glRotatef(90,0,1,0);
         cuerpo();
      glPopMatrix();


   glPopMatrix();
   

}

/*-----------------------------------------PARTES DEL ELEFANTE--------------------------------------------*/

/*-----------------------------------------------CABEZA---------------------------------------------------*/

void Elefante::cuerno(){
   glPushMatrix();
      glTranslatef(0,-50,0);
      glRotatef(180,0,0,1);
      glScalef(5,5,5);
      semiesfera->setColor(0.9,0.9,0.9);
      semiesfera->draw('I');
   glPopMatrix();
   glPushMatrix();
      glScalef(5,100,5);
      cilindro->setColor(0.9,0.9,0.9);
      cilindro->draw('I');
   glPopMatrix();
}

void Elefante::trompa(){

   glPushMatrix();
      glPushMatrix();
         glTranslatef(0,54,0);
         glScalef(20,50,20);
         semiesfera->draw('I');
      glPopMatrix();
     

      glPushMatrix();
         glTranslatef(0,47,0);
         modificaGiroTrompaX();
         modificaGiroTrompaZ();
         glTranslatef(0,-47,0);
          glPushMatrix();
            glTranslatef(0,47,0);
            glScalef(20,20,20);
            esfera->draw('I');
         glPopMatrix();
         glPushMatrix();
            glScalef(20,80,20);
            cilindro->draw('I');
         glPopMatrix();
         
         glPushMatrix();
            glTranslatef(0,-47,0);
            modificaGiroTrompaPequeniaX();
            modificaGiroTrompaPequeniaZ();
            glTranslatef(0,47,0);
            glPushMatrix();
               glTranslatef(0,-47,0);
               glScalef(20,20,20);
               esfera->draw('I');
            glPopMatrix();
            
            glPushMatrix();   
               glTranslatef(0,-54,0);
               glRotatef(180,0,0,1);
               glScalef(20,50,20),
               semiesfera->draw('I');
            glPopMatrix();
         glPopMatrix();
      glPopMatrix();
   glPopMatrix();
}

void Elefante::ojo(){
   glPushMatrix();
      glScalef(5,5,0.1);
      esfera->setColor(0.0,0.0,0.0);
      esfera->draw('I');
   glPopMatrix();
}
void Elefante::oreja(){
   glPushMatrix();
      glPushMatrix();
         glRotatef(180,0,0,1);
         glScalef(30,70,1);
         semiesfera->setColor(1,0.9,0.9);
         semiesfera->draw('I');
      glPopMatrix();
      glPushMatrix();
         glScalef(30,30,1);
         semiesfera->setColor(1,0.9,0.9);
         semiesfera->draw('I');
      glPopMatrix();
   glPopMatrix();
}

void Elefante::cabeza(){
   glPushMatrix();

      modificaGiroCabezaY();
      modificaGiroCabezaX();
      //CUERNOS
      glPushMatrix();
         glTranslatef(0,-70,0);
         glPushMatrix();
         glScalef(0.75,0.75,0.75);
            glTranslatef(-sin(45)*25,0,sin(45)*25);
            cuerno();
         glPopMatrix();
         glPushMatrix();      
            glScalef(0.75,0.75,0.75);
            glTranslatef(sin(45)*25,0,sin(45)*25);
            cuerno();
         glPopMatrix();
      glPopMatrix();

      //CABEZA
      glPushMatrix();
         glScalef(50,50,50);
         esfera->setColor(0.75,0.75,0.75);
         esfera->draw('I');
      glPopMatrix();

      //TROMPA
      glPushMatrix();
         glScalef(0.5,0.5,0.5);
         glTranslatef(0,-50,20);
         glTranslatef(0,-50,sin((90*M_PI/180))*70);    
         trompa();
      glPopMatrix();

      //OJOS
      glPushMatrix();
         glTranslatef(-cos(60)*25, -sin(60)*25, -cos(60)*50);
         ojo();
      glPopMatrix();
      glPushMatrix();
         glTranslatef(cos(60)*25, -sin(60)*25, -cos(60)*50);
         ojo();
      glPopMatrix();
      
      //OREJAS
      glPushMatrix();
         glPushMatrix();
            glTranslatef(60,10,0);
            oreja();
         glPopMatrix();
         glPushMatrix();
            glTranslatef(-60,10,0);
            oreja();
         glPopMatrix();
      glPopMatrix();

   glPopMatrix();


}

/*--------------------------------------------CUERPO-----------------------------------------------------*/

void Elefante::cola(){
   glPushMatrix();
      glRotatef(45,0,0,1);
      glTranslatef(0,-100,0);
      glPushMatrix();
         glScalef(5,40,5);
         cilindro->setColor(0.75,0.75,0.75);
         cilindro->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,20,0);
         glScalef(5,5,5);
         semiesfera->setColor(0.75,0.75,0.75);
         semiesfera->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,-25,0);
         glScalef(5,5,5);
         esfera->setColor(0.0,0.0,0.0);
         esfera->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,-32,0);
         glRotatef(180,0,0,1);
         glScalef(5,10,5);
         cono->setColor(0.0,0.0,0.0);
         cono->draw('I');
      glPopMatrix();
   glPopMatrix();

}

void Elefante::tronco(){
   glPushMatrix();
      glScalef(200,100,100);
      esfera->setColor(0.6,0.6,0.6);
      esfera->draw('I');
   glPopMatrix();
}


void Elefante::pata(){
   glPushMatrix();
      glPushMatrix();
         glScalef(20,50,20);
         cilindro->setColor(0.75,0.75,0.75);
         cilindro->draw('I');
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,25,0);
         glScalef(20,20,20);
         semiesfera->setColor(0.75,0.75,0.75);
         semiesfera->draw('I');
      glPopMatrix();
   glPopMatrix();
}

void Elefante::cuerpo(){
   glPushMatrix();
      //TRONCO
      glPushMatrix();
         tronco();
      glPopMatrix();
      //COLA
      glPushMatrix();
         //grados de libertad
         glTranslatef(sin((45*M_PI/180))*180, cos((45*M_PI/180))*120,0);
         cola();
      glPopMatrix();
      //PATAS
     
      glPushMatrix();
         glTranslatef(0,-25,0);
         glTranslatef(0,-sin((45*M_PI/180))*100,0);
         
            
         
         //IZQUIERDA
         glPushMatrix();
            glTranslatef(0,0, cos((45*M_PI/180))*100);
            glPushMatrix();   
               //pata izquierda delantera
               glTranslatef(-sin((45*M_PI/180))*100,0,0);
               giroPatasIzquierdas();
               if(agacha){
                  glRotatef(-90,0,0,1);
               }                
               pata();
            glPopMatrix();
            glPushMatrix();
               //Pata izquierda trasera
               glTranslatef(sin((45*M_PI/180))*100,0,0);
               giroPatasIzquierdas();
               if(agacha){
                  glRotatef(-90,0,0,1);
               }   
               pata();
            glPopMatrix();
         glPopMatrix();
         //DERECHA
         glPushMatrix();
            glTranslatef(0,0, -cos((45*M_PI/180))*100);
            glPushMatrix();
               //Pata derecha delantera   
               glTranslatef(-sin((45*M_PI/180))*100,0,0);
               giroPatasDerechas();
               if(agacha){
                  glRotatef(-90,0,0,1);
               }   
               pata();
            glPopMatrix();
            glPushMatrix();
               //Pata derecha trasera
               glTranslatef(sin((45*M_PI/180))*100,0,0);
               giroPatasDerechas();
               if(agacha){
                  glRotatef(-90,0,0,1);
               }   
               pata();
            glPopMatrix();
         glPopMatrix();
      glPopMatrix();
         
   glPopMatrix();
}

/*-----------------------------------------GRADOS DE LIBERTAD--------------------------------------------*/
  void Elefante::modificaGiroTrompaZ(){
      float giro= giroTrompaZ;
      if(giro <= 50 && giro>=-50){
         glRotatef(giro,0,0,1);
         
      }else{
         giroTrompaZ=0;
      }
  }

   void Elefante::modificaGiroTrompaX(){
      float giro= giroTrompaX;
      if(giro <= 50 && giro>=-50){
         glRotatef(giro,1,0,0);
      }else{
         giroTrompaX=0;
      }
     
   }

   void Elefante::modificaGiroCabezaX(){
      float giro= giroCabezaX;
      if(giro <= 20 && giro>=-45){
         glRotatef(giro,1,0,0);
      }else{
         giroCabezaX=0;
      }
      
   }

    void Elefante::modificaGiroCabezaY(){
      float giro= giroCabezaY;
      if(giro <= 60 && giro>=-60){
         glRotatef(giro,0,1,0);
      }else{
         giroCabezaY=0;
      }
     
   }


   void Elefante::giroPatasDerechas(){
      float giro = giroPatas;
       if(giro <= 60 && giro>=-60){
         glRotatef(giro,0,0,1);
      }else{
         giroPatas=0;
      }
   }

   void Elefante::giroPatasIzquierdas(){
      float giro = -giroPatas;
       if(giro <= 60 && giro>=-60){
         glRotatef(giro,0,0,1);
      }else{
         giroPatas=0;
      }
   }

 void Elefante::modificaGiroTrompaPequeniaX(){
        float giro= giroTrompaPequeniaX;
      if(giro <= 50 && giro>=-50){
         glRotatef(giro,1,0,0);
      }else{
         giroTrompaPequeniaX=0;
      }
    
 }
   void Elefante::modificaGiroTrompaPequeniaZ(){
        float giro= giroTrompaPequeniaZ;
      if(giro <= 50 && giro>=-50){
         glRotatef(giro,0,0,1);
      }else{
         giroTrompaPequeniaZ=0;
      }
    
 }

 void Elefante::setAgacharse(bool valor){
    agacha=valor;
 }
 bool Elefante::getAgacharse(){
    return agacha;
 }

 void Elefante::agacharse(){
    if(agacha){
         glTranslatef(0,-25,0);
    }else{
         glTranslatef(0,25,0);
    }
    
 }

 /*-----------------------------------------MODIFICADORES DE VARIABLES--------------------------------------------*/

     void Elefante::setGiroPatas(float valor){
         giroPatas+=valor;
        
     }
     void Elefante::setGiroTrompaX(float valor){
        giroTrompaX+=valor;
     }
     void Elefante::setGiroTrompaZ(float valor){
        giroTrompaZ+=valor;
     }
     void Elefante::setGiroCabezaX(float valor){
        giroCabezaX+=valor;
     }
     void Elefante::setGiroCabezaY(float valor){
        giroCabezaY+=valor;
     }

      void Elefante::setGiroTrompaPequeniaX(float valor){
        giroTrompaPequeniaX+=valor;
     }
      void Elefante::setGiroTrompaPequeniaZ(float valor){
        giroTrompaPequeniaZ+=valor;
     }



/*-----------------------------------------CONSULTORES DE VARIABLES--------------------------------------------*/

   float Elefante::getGiroPatas(){
      return giroPatas;
   }
   float Elefante::getGiroTrompaX(){
      return giroTrompaX;
   }
   float Elefante::getGiroTrompaZ(){
      return giroTrompaZ;
   }
   float Elefante::getGiroCabezaX(){
      return giroCabezaX;
   }
   float Elefante::getGiroCabezaY(){
      return giroCabezaY;
   }
   float Elefante::getGiroTrompaPequeniaX(){
      return giroTrompaPequeniaX;
   }
   float Elefante::getGiroTrompaPequeniaZ(){
      return giroTrompaPequeniaZ;
   }
  

   float Elefante::getPatasMax(){
      return patasMax;
   }
   float Elefante::getTrompaXMax(){
      return trompaXMax;
   }
   float Elefante::getTrompaZMax(){
      return trompaZMax;
   }
   float Elefante::getCabezaXMax(){
      return cabezaXmax;
   }
   float Elefante::getCabezaYMax(){
      return cabezaYmax;
   }
   float Elefante::getTrompaPequeniaXMax(){
      return trompitaXMax;
   }
   float Elefante::getTrompaPequeniaZMax(){
      return trompitaYMax;
   }

