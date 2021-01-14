#include "aux.h"
#include "elefante.h"




/*-----------------------------------------CONSTRUCTOR--------------------------------------------*/

Elefante::Elefante()
{
  


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

  

   cabeza= new Cabeza();
   cuerpo = new Cuerpo();



}
 

/*-------------------------------------------MÉTODO DRAW-----------------------------------------------*/

void Elefante::draw(){
   
  agacharse();
   
  
   glPushMatrix();
     
      glPushMatrix();
         glTranslatef(0,0,200);
         glTranslatef(0,87.5,0);
         glScalef(1.5,1.5,1.5);
         //Grados de libertad de la cabeza
         modificaGiroCabezaX();
         modificaGiroCabezaY();
         cabeza->draw();
      glPopMatrix();

      glPushMatrix();
         glRotatef(90,0,1,0);
         cuerpo->draw();
      glPopMatrix();


   glPopMatrix();
   

}


/*-----------------------------------------GRADOS DE LIBERTAD--------------------------------------------*/
  void Elefante::modificaGiroTrompaZ(){
    cabeza->modificaGiroTrompaZ();
  }

   void Elefante::modificaGiroTrompaX(){
      cabeza->modificaGiroTrompaX();
     
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
      cuerpo->giroPatasDerechas();
   }

   void Elefante::giroPatasIzquierdas(){
      cuerpo->giroPatasIzquierdas();
   }

 void Elefante::modificaGiroTrompaPequeniaX(){
        cabeza->modificaGiroTrompaPequeniaX();
    
 }
   void Elefante::modificaGiroTrompaPequeniaZ(){
      cabeza->modificaGiroTrompaPequeniaZ();
    
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
         cuerpo->setAgacharse(agacha);
    }else{
         glTranslatef(0,25,0);
         cuerpo->setAgacharse(agacha);
    }
    
 }

 /*-----------------------------------------MODIFICADORES DE VARIABLES--------------------------------------------*/

     void Elefante::setGiroPatas(float valor){
         cuerpo->setGiroPatas(valor);
        
     }
     void Elefante::setGiroTrompaX(float valor){
        cabeza->setGiroTrompaX(valor);
     }
     void Elefante::setGiroTrompaZ(float valor){
        cabeza->setGiroTrompaZ(valor);
     }
     void Elefante::setGiroCabezaX(float valor){
        giroCabezaX+=valor;
     }
     void Elefante::setGiroCabezaY(float valor){
        giroCabezaY+=valor;
     }

      void Elefante::setGiroTrompaPequeniaX(float valor){
        cabeza->setGiroTrompaPequeniaX(valor);
     }
      void Elefante::setGiroTrompaPequeniaZ(float valor){
        cabeza->setGiroTrompaPequeniaZ(valor);
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

   float Elefante::getCabezaYMax(){
      return cabezaYmax;
   }  

   float Elefante::getCabezaXMax(){
      return cabezaXmax;
   }

 /*  float Elefante::getPatasMax(){
      return patasMax;
   }
   float Elefante::getTrompaXMax(){
      return trompaXMax;
   }
   float Elefante::getTrompaZMax(){
      return trompaZMax;
   }
  
   
   float Elefante::getTrompaPequeniaXMax(){
      return trompitaXMax;
   }
   float Elefante::getTrompaPequeniaZMax(){
      return trompitaYMax;
   }

*/