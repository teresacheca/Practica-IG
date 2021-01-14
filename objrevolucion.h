// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: objRevolucion.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
   public:
        int n_instancias; 
        int n_ver;
        bool t_sup;
        bool t_inf;
        bool tapas=true;
        bool norte, sur;
        std::vector<Tupla3f> p;
        std::vector<Tupla3i> c;
        int num_caras_conTapas;
        int num_caras_sinTapas;
        Tupla4f colorMaterial;
        const float epsilon = 0.00001;


        ObjRevolucion();
        ~ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
        ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
        void crear(std::vector<Tupla3f>, int num_instancias, bool tapa_sup, bool tapa_inf);

        void ponerTapas(bool tapas);
        bool getTapas();
        void aniadirTapas(bool tapa_inf, bool tapa_sup);

        void setColorMaterial(Tupla4f c);

        Tupla4f getColorMaterial();

        bool esUnPolo(Tupla3f polo);

        void coordTextura();

        //Sobrecargado
        void draw(char letra);

    private:
        void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, const bool conTapas);

} ;




#endif
