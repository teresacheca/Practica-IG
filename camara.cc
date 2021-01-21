#include "camara.h"
Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up,  TipoCamara tipo, float bottom, float top, float left, float right, float near, float far){
   this->eye=eye;
   this->at = at;
   this->up = up;
   this->left = left;
   this->right = right;
   this->near = near;
   this->far = far;
   this->bottom = bottom;
   this->top = top;
   factor=1;
   objeto=false;
   activarModoExaminar=false;
   aspect=1;
}

void Camara::rotarXExaminar(float angle){
   eye[1]= (eye[1]*cos(angle)) + (sin(angle)*eye[2]);
   eye[2]= (eye[1]*(-sin(angle))) + (cos(angle)*eye[2]);
   up[1]= (up[1]*cos(angle)) + (sin(angle)*up[2]);
   up[2]= (up[1]*(-sin(angle))) + (cos(angle)*up[2]);
   if(eye[1]>=360){
      eye[1]=0;
   }
   if(eye[2]>=360){
      eye[2]=0;
   }
}

void Camara::rotarYExaminar(float angle){
   eye[0]= (eye[0]*cos(angle)) - (sin(angle)*eye[2]);
   eye[2]= (eye[0]*(sin(angle))) + (cos(angle)*eye[2]);
   up[0]= (up[0]*cos(angle)) - (sin(angle)*up[2]);
   up[2]= (up[0]*(sin(angle))) + (cos(angle)*up[2]);
   if(eye[0]>=360){
      eye[0]=0;
   }
   if(eye[2]>=360){
      eye[2]=0;
   }
}

void Camara::rotarZExaminar(float angle){
   eye[1]= (eye[0]*cos(angle)) + (sin(angle)*eye[1]);
   eye[2]= (eye[0]*(-sin(angle))) + (cos(angle)*eye[1]);
   up[1]= (up[0]*cos(angle)) + (sin(angle)*up[1]);
   up[2]= (up[0]*(-sin(angle))) + (cos(angle)*up[1]);
   if(eye[1]>=360){
      eye[1]=0;
   }
   if(eye[0]>=360){
      eye[0]=0;
   }
}

void Camara::rotarXFirstPerson(float angle){
   if(objeto){
      eye[0] = eye[0] + angle;
   }else{
      at[0] = at[0] + angle;
   }
   
}

void Camara::rotarYFirstPerson(float angle){
   if(objeto){
      eye[1] = eye[1] + angle;
   }else{
      at[1] = at[1] + angle;
   }
   
}

void Camara::rotarZFirstPerson(float angle){
   if(objeto){
      eye[2] = eye[2] + angle;
   }else{
      at[2] = at[2] + angle;
   }
   
}

void Camara::mover(float x, float y, float z){

}

void Camara::zoom(float factor){
   this->factor *= factor;

   eye[0] = eye[0]*factor;
   eye[1] = eye[1]*factor;
   eye[2] = eye[2] *factor;
}

void Camara::setObserver(){
   gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

}

void Camara::setProyeccion(){
   std::cout << "entra";
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

  std::cout << "factor  " << factor;
   switch (tipo)
   {
      
      case PERSPECTIVA:
         glFrustum(left/aspect, right/aspect, bottom/aspect, top/aspect, near, far);
      break;
      case ORTOGONAL:
         glOrtho(left, right, bottom, top, near, far);
      break;
   }

   glLoadIdentity();

}

Tupla3f Camara::getAt(){
   return at;
}

void Camara::objetoEncontrado(bool encontrado, int x, int y){
   objeto = encontrado;
   //activarModoExaminar = encontrado;
}

bool Camara::getModoExaminar(){
   return activarModoExaminar;
}


void Camara::setAspect(const float aspect){
   this->aspect = aspect;
}