#include "aux.h"
#include "material.h"
#include <math.h>

using namespace std;
// *****************************************************************************
//
// Clase Material
//
// *****************************************************************************

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo){
    this->ambiente=mambiente;
    this->especular=mespecular;
    this->difuso=mdifuso;
    this->brillo = brillo;
    
}

Material::~Material(){
   
}


void Material::aplicar(){
    Tupla4f color;
    color[0] = ambiente[0] + especular[0] + difuso[0];
    color[1] = ambiente[1] + especular[1] + difuso[1];
    color[2] = ambiente[2] + especular[2] + difuso[2];
    color[3] = ambiente[3] + especular[3] + difuso[3];
    color = ambiente + especular +difuso;
   

    float normalize = sqrt(pow(color[0],2)+ pow(color[1],2) + pow(color[2], 2) );
    color[0] /= normalize;
    color[1] /=normalize;
    color[2] /=normalize;
    color[3] = 1;
    
   glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT, GL_SHININESS, brillo);
   
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
}

/*
Tupla4f Material::getAmbiente(){
    return ambiente;
}
Tupla4f Material::getEspecular(){
    return especular;
}
Tupla4f Material::getDifuso(){
    return difuso;
}
float Material::getBrillo(){
    return brillo;
}


 void Material::setAmbiente(Tupla4f am){
     ambiente = am;
 }
 
 void Material::setEspecular(Tupla4f es){
     especular = es;
 }
 
 void Material::setDifuso(Tupla4f di){
     difuso =di;
 }
 
 void Material::setBrillo(float b){
     brillo = b;
 }*/