

#include "aux.h"
#include "ejes.h"

// -----------------------------------------------------------------------------

Ejes::Ejes()
{
    axisSize = 1000;
    createArrayData();
}
// -----------------------------------------------------------------------------

void Ejes::changeAxisSize( float newSize )
{
	axisSize = newSize;
	createArrayData();
}
// -----------------------------------------------------------------------------

void Ejes::createArrayData()
{
	colorArray[0] = 1; colorArray[1] = 0; colorArray[2] = 0;		//eje X rojo
	colorArray[3] = 1; colorArray[4] = 0; colorArray[5] = 0;		// eje X rojo
	colorArray[6] = 0; colorArray[7] = 1; colorArray[8] = 0;		//eje Y verde
	colorArray[9] = 0; colorArray[10] = 1; colorArray[11] = 0;		//eje Y verde
	colorArray[12] = 0; colorArray[13] = 0; colorArray[14] = 1;		//eje Z azul
	colorArray[15] = 0; colorArray[16] = 0; colorArray[17] = 1;		//eje Z azul

	vertexArray[0] = -axisSize; vertexArray[1] = 0; vertexArray[2] = 0;		//-1000, 0, 0	eje x
	vertexArray[3] = axisSize; vertexArray[4] = 0; vertexArray[5] = 0;		//1000,0,0		eje x
	vertexArray[6] = 0; vertexArray[7] = -axisSize; vertexArray[8] = 0;		//0,-1000,0		eje y
	vertexArray[9] = 0; vertexArray[10] = axisSize; vertexArray[11] = 0;	//0,1000,0		eje y
	vertexArray[12] = 0; vertexArray[13] = 0; vertexArray[14] = -axisSize;	//0,0,-1000		eje z
	vertexArray[15] = 0; vertexArray[16] = 0; vertexArray[17] = axisSize;	//0,0,1000		eje z
}
 

void Ejes::draw()
{
	glShadeModel(GL_FLAT);
	glDisable(GL_LIGHTING);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexArray );
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colorArray );
	glDrawArrays( GL_LINES, 0, 6 ) ;

	
}
