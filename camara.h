// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h

//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"



// *****************************************************************************
//
// clase camara
//
// *****************************************************************************
typedef enum {PERSPECTIVA, ORTOGONAL} TipoCamara;

class Camara
{
	private:
		Tupla3f eye;
		Tupla3f at;
		Tupla3f up;
		float bottom, top;
		float factor;

		TipoCamara tipo;
		float left, right, near, far;
		bool objeto;

	public:
		Camara(Tupla3f eye, Tupla3f at, Tupla3f up,  TipoCamara tipo, float bottom, float top, float left, float right, float near, float far);
		void rotarXExaminar(float angle);
		void rotarYExaminar(float angle);
		void rotarZExaminar(float angle);
		void rotarXFirstPerson(float angle);
		void rotarYFirstPerson(float angle);
		void rotarZFirstPerson(float angle);
		void mover(float x, float y, float z);

		void zoom(float factor);
		void setObserver();
		void setProyeccion();

		Tupla3f getAt();

		void objetoEncontrado(bool encontrado, int x, int y);
} ;


#endif
