#include <boost/thread.hpp>
#include "EigenAnalysis.h"
#include "Componente.h"
#include "ObjectView.h"
#include "View.h"
#include <fstream>

float calcularPuntoDiagonal(std::vector< float > verts, char eje1, char eje2)
{
  std::vector< float > ps1;
  std::vector< float > ps2;
  std::vector< float >::iterator it = verts.begin();
  float prom1 = 0, prom2 = 0;
  int i = 0;

  for(; it != verts.end(); it++)
  {
    if(eje1 == 'x')
    {
      if(i % 3 == 0)
      {
        ps1.push_back(*it);
        prom1 += *it;
      }
    }
    else if(eje2 == 'x')
    {
      if(i % 3 == 0)
      {
        ps2.push_back(*it);
        prom2 += *it;
      }
    }

    if(eje1 == 'y')
    {
      if(i % 3 == 1)
      {
        ps1.push_back(*it);
        prom1 += *it;
      }
    }
    else if(eje2 == 'y')
    {
      if(i % 3 == 1)
      {
        ps2.push_back(*it);
        prom2 += *it;
      }
    }

    if(eje1 == 'z')
    {
      if(i % 3 == 2)
      {
        ps1.push_back(*it);
        prom1 += *it;
      }
    }
    else if(eje2 == 'z')
    {
      if(i % 3 == 2)
      {
        ps2.push_back(*it);
        prom2 += *it;
      }
    }

    i++;
  }

  prom1 /= ps1.size();
  prom2 /= ps2.size();

  float suma = 0;
  it = ps1.begin();
  std::vector< float >::iterator it2 = ps2.begin();

  for(; it != ps1.end(); it++)
  {
    suma += ((*it - prom1) * (*it - prom1)) + ((*it2 - prom2) * (*it2 - prom2));
    it2++;
  }

  return suma;
}

float calcularPuntoNoDiagonal(std::vector< float> verts, char eje1, char eje2)
{
  std::vector< float > ps1;
  std::vector< float > ps2;
  std::vector< float >::iterator it = verts.begin();
  float prom1 = 0, prom2 = 0;
  int i = 0;

  for(; it != verts.end(); it++)
  {
    if(eje1 == 'x')
    {
      if(i % 3 == 0)
      {
        ps1.push_back(*it);
        prom1 += *it;
      }
    }
    else if(eje2 == 'x')
    {
      if(i % 3 == 0)
      {
        ps2.push_back(*it);
        prom2 += *it;
      }
    }

    if(eje1 == 'y')
    {
      if(i % 3 == 1)
      {
        ps1.push_back(*it);
        prom1 += *it;
      }
    }
    else if(eje2 == 'y')
    {
      if(i % 3 == 1)
      {
        ps2.push_back(*it);
        prom2 += *it;
      }
    }

    if(eje1 == 'z')
    {
      if(i % 3 == 2)
      {
        ps1.push_back(*it);
        prom1 += *it;
      }
    }
    else if(eje2 == 'z')
    {
      if(i % 3 == 2)
      {
        ps2.push_back(*it);
        prom2 += *it;
      }
    }

    i++;
  }

  prom1 /= ps1.size();
  prom2 /= ps2.size();

  float suma = 0;
  it = ps1.begin();
  std::vector< float >::iterator it2 = ps2.begin();

  for(; it != ps1.end(); it++)
  {
    suma += ((*it - prom1) * (*it2 - prom2));
    it2++;
  }

  return (suma* -1);
}

void calcularRadii(std::vector< float > &eValues)
{

}

int main( int argc, char* argv[] )
{
  // Initialize visualization thread
  View::Init( argc, argv );
  boost::thread draw_thread( View::DrawLoop );

  std::list< Componente* > Objects;

  //variables para comandos (Agregado)
  std::istream* input;
  std::string in, ar;

  //A simple cube
  ObjectView* myFirstCube = new ObjectView( );

  /*Add vertices
  myFirstCube->AddVertex( 10, 10, 10 );
  myFirstCube->AddVertex( 14, 10, 10 );
  myFirstCube->AddVertex( 14, 14, 10 );
  myFirstCube->AddVertex( 10, 14, 10 );
  myFirstCube->AddVertex( 10, 10, 14 );
  myFirstCube->AddVertex( 14, 10, 14 );
  myFirstCube->AddVertex( 14, 14, 14 );
  myFirstCube->AddVertex( 10, 14, 14 );

  // Add faces
  myFirstCube->AddCell( 4, 0, 1, 2, 3 );
  myFirstCube->AddCell( 4, 4, 5, 6, 7 );
  myFirstCube->AddCell( 4, 2, 3, 7, 6 );
  myFirstCube->AddCell( 4, 0, 1, 5, 4 );
  myFirstCube->AddCell( 4, 1, 2, 6, 5 );
  myFirstCube->AddCell( 4, 0, 4, 7, 3 );

  // Show it in magenta
  View::AddObject( myFirstCube, 1, 0, 1 );

  //Another simple cube
  ObjectView mySecondCube;
  mySecondCube.AddVertex( 15, 15, 15 );
  mySecondCube.AddVertex(  6, 15, 15 );
  mySecondCube.AddVertex(  6,  6, 15 );
  mySecondCube.AddVertex( 15,  6, 15 );
  mySecondCube.AddVertex( 15, 15,  6 );
  mySecondCube.AddVertex(  6, 15,  6 );
  mySecondCube.AddVertex(  6,  6,  6 );
  mySecondCube.AddVertex( 15,  6,  6 );

  mySecondCube.AddCell( 4, 0, 1, 2, 3 );
  mySecondCube.AddCell( 4, 4, 5, 6, 7 );
  mySecondCube.AddCell( 4, 2, 3, 7, 6 );
  mySecondCube.AddCell( 4, 0, 1, 5, 4 );
  mySecondCube.AddCell( 4, 1, 2, 6, 5 );
  mySecondCube.AddCell( 4, 0, 4, 7, 3 );
  View::AddObject( &mySecondCube, 1, 1, 0 );*/


  while( View::Running )
  {
    //Obtener Comando
    std::cout<<"$ ";
    input = &std::cin;
    if(argc > 1)
    {
      input=new std::ifstream(argv[1]);
    }
    if(!(*input))
    {
       std::cerr<<"Error en la validacion de la entrada."<<std::endl;
       return(-1);
    }
    std::getline(*input, in);

    //------------Comando exit------------
    if(!in.find("exit")) View::Running = false;

    //------------Comando load------------
    if(!in.find("load"))
    {
      std::string::iterator it=in.begin();
      bool enc = false;
      float r=0, g=0, b=0;

      while(it!=in.end() )
      {
        if(*it == ' ' )
        {
          if(!enc)
          {
            it++;
            while(*it != ' ' && it != in.end())
            {
              ar += *it;
              it++;
            }
            enc=true;
          }
          else
          {
             std::string num;
             num += *it; std::stringstream s2(num); s2>>r;it++;num="";
             num += *it; std::stringstream s3(num); s3>>g;it++;it++;num="";
             num += *it; std::stringstream s4(num); s4>>b;num="";
          }
        }
        if(it != in.end())it++;
      }
      //std::cout<<ar<<std::endl;
      Componente* nuovo = new Componente();
      ObjectView* Obj = new ObjectView( );
      Obj = nuovo->load(ar);

      Objects.push_back(nuovo);

      View::AddObject( Obj, r, g, b );
      ar="";

    }
    //--------------Comando list------------
    if(!in.find("list"))
    {
      if(!Objects.empty())
      {
        std::list< Componente* >::iterator itC = Objects.begin();

        for(; itC != Objects.end(); itC++)
        {
          Componente* cp = *itC;
          std::cout << cp -> name << " contains " << cp -> nCant <<std::endl;
        }
      }
      else
      {
        std::cout << "No objects found." << std::endl;
      }
    }

    //-------------Comando unload-----------
    if(!in.find("unload"))
    {
      if(!Objects.empty())
      {
        for(int i = 0; i < in.length(); i++)
        {
          if(in[i] == ' ')
          {
            for(int j = i + 1; j < in.length(); j++)
            {
              ar.push_back(in[j]);
            }
          }
        }

        int pos = 0;
        bool enc = false;

        std::list< Componente* >::iterator it = Objects.begin();

        for(; it != Objects.end() && enc == false; it++)
        {
          Componente* cp = *it;
          if(cp->name == ar)
          {
            enc = true;
          }
          else
          {
            pos++;
          }
        }

        if(pos < Objects.size())
        {
          View::Objects.erase(View::Objects.begin() + pos);
          std::list< Componente* >::iterator it0 = Objects.begin();
          advance(it0, pos);
          Objects.erase(it0);
        }
      }
      else
      {
        std::cout << "No objects found." << std::endl;
      }

      ar = "";
    }

    //----------------Comando help-----------------
    if(!in.find("help"))
    {
      if(in.find(" ") != std::string::npos)
      {
        if(in.find("load") != std::string::npos)
        {
          std::cout << "load --> Carga en memoria los datos contenidos en el archivo identificado por <filename>."  << std::endl <<
            "load <filename>" << std::endl;
        }

        if(in.find("list") != std::string::npos)
        {
          std::cout << "list --> lista todos los objetos cargados en memoria junto con su cantidad de puntos."  << std::endl;
        }

        if(in.find("unload") != std::string::npos)
        {
          std::cout << "unload --> Descarga de la memoria el objeto identificado con el nombre dado" << std::endl <<
            "unload <object_name>" << std::endl;
        }

        if(in.find("bbox") != std::string::npos)
        {
          std::cout << "bbox --> Calcula la caja envolvente." << std::endl <<
            "bbox <object_name> --> bbox especifica." << std::endl <<
            "bbox --> bbox de todos los objetos cargados en memoria." << std::endl;
        }

        if(in.find("obbox") != std::string::npos)
        {
          std::cout << "obbox --> Calcula la caja envolvente orientada." << std::endl <<
            "obbox <object_name> --> bbox especifica." << std::endl <<
            "obbox --> obbox de todos los objetos cargados en memoria." << std::endl;
        }
      }
      else
      {
        std::cout << "Commands list:" << std::endl <<
          "load" << std::endl << "list" << std::endl <<
          "unload" << std::endl << "bbox" << std::endl <<
          "obbox" << std::endl << "ellipsoid" << std::endl;
      }
    }

    //-----------------Comando bbox-----------------------------
    if(!in.find("bbox"))
    {
      if(!Objects.empty())
      {
        if(in.find(" ") != std::string::npos)
        {
          for(int i = 0; i < in.length(); i++)
          {
            if(in[i] == ' ')
            {
              for(int j = i + 1; j < in.length(); j++)
              {
                ar.push_back(in[j]);
              }
            }
          }

          int pos = 0;
          bool enc = false;

          std::list< Componente* >::iterator it = Objects.begin();

          for(; it != Objects.end() && enc == false;it++)
          {
            Componente* cp = *it;
            if(cp->name == ar)
            {
              enc = true;
            }
            else
            {
              pos++;
            }
          }

          if(pos < Objects.size())
          {
            ObjectView* ov = View::Objects[pos];
            std::vector< float > mins;
            std::vector< float > maxs;

            mins.push_back(ov->GetMinX());
            mins.push_back(ov->GetMinY());
            mins.push_back(ov->GetMinZ());

            maxs.push_back(ov->GetMaxX());
            maxs.push_back(ov->GetMaxY());
            maxs.push_back(ov->GetMaxZ());

            ObjectView* bbox = View::AddBoundingBox(mins, maxs);
            Componente* cp = new Componente();
            cp->name = "bbox" + ar;
            cp->obj = bbox;
            cp->nCant = cp->obj->getVertices().size();
            Objects.push_back(cp);
          }
          else
          {
            std::cout << ar << " does not exist." << std::endl;
          }
        }
        else
        {
          std::vector< ObjectView* >::iterator it = View::Objects.begin();
          ObjectView* ov = *it;
          float minX = ov->GetMinX(), minY = ov->GetMinY(), minZ = ov->GetMinZ(), maxX = ov->GetMaxX(), maxY = ov->GetMaxY(), maxZ = ov->GetMaxZ();
          std::vector< float > mins;
          std::vector< float > maxs;

          for(; it != View::Objects.end(); it++)
          {
            ov = *it;

            if(ov->GetMinX() < minX)
            {
              minX = ov->GetMinX();
            }

            if(ov->GetMinY() < minY)
            {
              minY = ov->GetMinY();
            }

            if(ov->GetMinZ() < minZ)
            {
              minZ = ov->GetMinZ();
            }

            if(ov->GetMaxX() > maxX)
            {
              maxX = ov->GetMaxX();
            }

            if(ov->GetMaxY() > maxY)
            {
              maxY = ov->GetMaxY();
            }

            if(ov->GetMaxZ() > maxZ)
            {
              maxZ = ov->GetMaxZ();
            }
          }

          maxs.push_back(maxX);
          maxs.push_back(maxY);
          maxs.push_back(maxZ);

          mins.push_back(minX);
          mins.push_back(minY);
          mins.push_back(minZ);

          ObjectView* bboxAll = View::AddBoundingBox(mins, maxs);
          Componente* cp = new Componente();
          cp->name = "bboxAll";
          cp->obj = bboxAll;
          cp->nCant = cp->obj->getVertices().size();
          Objects.push_back(cp);
        }
      }
      else
      {
        std::cout << "No objects found." << std::endl;
      }

      ar = "";
    }

    //----------------------Comando obbox-----------------------------------
    if(!in.find("obbox"))
    {
      if(!Objects.empty())
      {
        if(in.find(" ") != std::string::npos)
        {
          for(int i = 0; i < in.length(); i++)
          {
            if(in[i] == ' ')
            {
              for(int j = i + 1; j < in.length(); j++)
              {
                ar.push_back(in[j]);
              }
            }
          }

          int pos = 0;
          bool enc = false;

          std::list< Componente* >::iterator it = Objects.begin();
          Componente* cp = *it;

          for(; it != Objects.end() && enc == false;it++)
          {
            cp = *it;
            if(cp->name == ar)
            {
              enc = true;
            }
            else
            {
              pos++;
            }
          }

          if(pos < Objects.size())
          {
            std::vector< float > verts = cp->obj->getVertices();
            std::vector< float >::iterator it = verts.begin();

            // Sacando Centro-------------------
            float centro[3];
            float promX = 0, promY = 0, promZ = 0;

            for(int i = 0; it != verts.end(); it++)
            {
              if(i % 3 == 0)
              {
                promX += *it;
              }
              else if(i % 3 == 1)
              {
                promY += *it;
              }
              else
              {
                promZ += *it;
              }
            }

            centro[0] = promX / (verts.size() / 3);
            centro[1] = promY / (verts.size() / 3);
            centro[2] = promZ / (verts.size() / 3);

            // Sacando Matriz de Inercia----------------
            float inercia[3][3];
            inercia[0][0] = calcularPuntoDiagonal(verts, 'y', 'z');
            inercia[0][1] = calcularPuntoNoDiagonal(verts, 'x', 'y');
            inercia[0][2] = calcularPuntoNoDiagonal(verts, 'x', 'z');
            inercia[1][0] = calcularPuntoNoDiagonal(verts, 'x', 'y');
            inercia[1][1] = calcularPuntoDiagonal(verts, 'x', 'z');
            inercia[1][2] = calcularPuntoNoDiagonal(verts, 'y', 'z');
            inercia[2][0] = calcularPuntoNoDiagonal(verts, 'x', 'z');
            inercia[2][1] = calcularPuntoNoDiagonal(verts, 'y', 'z');
            inercia[2][2] = calcularPuntoDiagonal(verts, 'x', 'y');

            // Sacando Valores y Vectores Propios---------
            float eValues[3];
            float eVectors[3][3];

            EigenAnalysis< float >::Compute(inercia, eValues, eVectors);

            // Sacando Matriz de Radios-------------------
            float vecRadii[3];
            vecRadii[0] = (float) sqrt((5 * (eValues[1] + eValues[2] - eValues[0]) / (2 * cp->nCant)));
            vecRadii[1] = (float) sqrt((5 * (eValues[0] + eValues[2] - eValues[1]) / (2 * cp->nCant)));
            vecRadii[2] = (float) sqrt((5 * (eValues[0] + eValues[1] - eValues[2]) / (2 * cp->nCant)));

            float matRadii[3][3];
            matRadii[0][0] = vecRadii[0];
            matRadii[0][1] = 0;
            matRadii[0][2] = 0;
            matRadii[1][0] = 0;
            matRadii[1][1] = vecRadii[1];
            matRadii[1][2] = 0;
            matRadii[2][0] = 0;
            matRadii[2][1] = 0;
            matRadii[2][2] = vecRadii[2];

            // Puntos de la Caja-------------
            std::vector< float > puntos[8];

            for(int i = 0; i < 8; i++)
            {
              if(i % 4 == 0 || i % 4 == 1)
              {
                puntos[i].push_back(-1);
              }
              else
              {
                puntos[i].push_back(1);
              }

              if(i % 4 == 1 || i % 4 == 2)
              {
                puntos[i].push_back(-1);
              }
              else
              {
                puntos[i].push_back(1);
              }

              if(i < 4)
              {
                puntos[i].push_back(-1);
              }
              else
              {
                puntos[i].push_back(1);
              }
            }

            // Aplicacion Transformacion-----------------------

              // Producto R y rs--------
            float matProd[3][3];
            matProd[0][0] = (eVectors[0][0] * matRadii[0][0]) + (eVectors[0][1] * matRadii[1][0]) + (eVectors[0][2] * matRadii[2][0]);
            matProd[0][1] = (eVectors[0][0] * matRadii[0][1]) + (eVectors[0][1] * matRadii[1][1]) + (eVectors[0][2] * matRadii[2][1]);
            matProd[0][2] = (eVectors[0][0] * matRadii[0][2]) + (eVectors[0][1] * matRadii[1][2]) + (eVectors[0][2] * matRadii[2][2]);
            matProd[1][0] = (eVectors[1][0] * matRadii[0][0]) + (eVectors[1][1] * matRadii[1][0]) + (eVectors[1][2] * matRadii[2][0]);
            matProd[1][1] = (eVectors[1][0] * matRadii[0][1]) + (eVectors[1][1] * matRadii[1][1]) + (eVectors[1][2] * matRadii[2][1]);
            matProd[1][2] = (eVectors[1][0] * matRadii[0][2]) + (eVectors[1][1] * matRadii[1][2]) + (eVectors[1][2] * matRadii[2][2]);
            matProd[2][0] = (eVectors[2][0] * matRadii[0][0]) + (eVectors[2][1] * matRadii[1][0]) + (eVectors[2][2] * matRadii[2][0]);
            matProd[2][1] = (eVectors[2][0] * matRadii[0][1]) + (eVectors[2][1] * matRadii[1][1]) + (eVectors[2][2] * matRadii[2][1]);
            matProd[2][2] = (eVectors[2][0] * matRadii[0][2]) + (eVectors[2][1] * matRadii[1][2]) + (eVectors[2][2] * matRadii[2][2]);

              // Producto xyz con matProd y suma con el centro
            std::vector< float > puntsResp[8];
            for(int  i = 0; i < 8; i++)
            {
              puntsResp[i].push_back((matProd[0][0] * puntos[i][0]) + (matProd[0][1] * puntos[i][1]) + (matProd[0][2] * puntos[i][2]));
              puntsResp[i].push_back((matProd[1][0] * puntos[i][0]) + (matProd[1][1] * puntos[i][1]) + (matProd[1][2] * puntos[i][2]));
              puntsResp[i].push_back((matProd[2][0] * puntos[i][0]) + (matProd[2][1] * puntos[i][1]) + (matProd[2][2] * puntos[i][2]));

              puntsResp[i][0] += centro[0];
              puntsResp[i][1] += centro[1];
              puntsResp[i][2] += centro[2];
            }

            ObjectView* obbox = View::AddOrientedBoundingBox(puntsResp);
            Componente* cp = new Componente();
            cp->name = "obbox" + ar;
            cp->obj = obbox;
            cp->nCant = cp->obj->getVertices().size();
            Objects.push_back(cp);
          }
          else
          {
            std::cout << ar << " does not exist." << std::endl;
          }
        }
        else
        {
          //obbox ALL -------------------------------------------------------------
          std::vector< float > vertis;
          std::list< Componente* >::iterator it2 = Objects.begin();

          int mayor = 0;
          for(; it2 != Objects.end(); it2++)
          {
            Componente* cp = *it2;
            if(cp->obj->getVertices().size() > mayor)
            {
              mayor = cp->obj->getVertices().size();
              vertis = cp->obj->getVertices();
            }
          }

          std::vector< float >::iterator it = vertis.begin();

          // Sacando Centro-------------------
          float centro[3];
          float promX = 0, promY = 0, promZ = 0;

          for(int i = 0; it != vertis.end(); it++)
          {
            if(i % 3 == 0)
            {
              promX += *it;
            }
            else if(i % 3 == 1)
            {
              promY += *it;
            }
            else
            {
              promZ += *it;
            }
          }

          centro[0] = promX / (vertis.size() / 3);
          centro[1] = promY / (vertis.size() / 3);
          centro[2] = promZ / (vertis.size() / 3);

          // Sacando Matriz de Inercia----------------
          float inercia[3][3];
          inercia[0][0] = calcularPuntoDiagonal(vertis, 'y', 'z');
          inercia[0][1] = calcularPuntoNoDiagonal(vertis, 'x', 'y');
          inercia[0][2] = calcularPuntoNoDiagonal(vertis, 'x', 'z');
          inercia[1][0] = calcularPuntoNoDiagonal(vertis, 'x', 'y');
          inercia[1][1] = calcularPuntoDiagonal(vertis, 'x', 'z');
          inercia[1][2] = calcularPuntoNoDiagonal(vertis, 'y', 'z');
          inercia[2][0] = calcularPuntoNoDiagonal(vertis, 'x', 'z');
          inercia[2][1] = calcularPuntoNoDiagonal(vertis, 'y', 'z');
          inercia[2][2] = calcularPuntoDiagonal(vertis, 'x', 'y');

          // Sacando Valores y Vectores Propios---------
          float eValues[3];
          float eVectors[3][3];

          EigenAnalysis< float >::Compute(inercia, eValues, eVectors);

          // Sacando Matriz de Radios-------------------
          float vecRadii[3];
          vecRadii[0] = (float) sqrt((5 * (eValues[1] + eValues[2] - eValues[0]) / (2 * vertis.size())));
          vecRadii[1] = (float) sqrt((5 * (eValues[0] + eValues[2] - eValues[1]) / (2 * vertis.size())));
          vecRadii[2] = (float) sqrt((5 * (eValues[0] + eValues[1] - eValues[2]) / (2 * vertis.size())));

          float matRadii[3][3];
          matRadii[0][0] = vecRadii[0];
          matRadii[0][1] = 0;
          matRadii[0][2] = 0;
          matRadii[1][0] = 0;
          matRadii[1][1] = vecRadii[1];
          matRadii[1][2] = 0;
          matRadii[2][0] = 0;
          matRadii[2][1] = 0;
          matRadii[2][2] = vecRadii[2];

          // Puntos de la Caja-------------
          std::vector< float > puntos[8];

          for(int i = 0; i < 8; i++)
          {
            if(i % 4 == 0 || i % 4 == 1)
            {
              puntos[i].push_back(-1);
            }
            else
            {
              puntos[i].push_back(1);
            }

            if(i % 4 == 1 || i % 4 == 2)
            {
              puntos[i].push_back(-1);
            }
            else
            {
              puntos[i].push_back(1);
            }

            if(i < 4)
            {
              puntos[i].push_back(-1);
            }
            else
            {
              puntos[i].push_back(1);
            }
          }

          // Aplicacion Transformacion-----------------------

            // Producto R y rs--------
          float matProd[3][3];
          matProd[0][0] = (eVectors[0][0] * matRadii[0][0]) + (eVectors[0][1] * matRadii[1][0]) + (eVectors[0][2] * matRadii[2][0]);
          matProd[0][1] = (eVectors[0][0] * matRadii[0][1]) + (eVectors[0][1] * matRadii[1][1]) + (eVectors[0][2] * matRadii[2][1]);
          matProd[0][2] = (eVectors[0][0] * matRadii[0][2]) + (eVectors[0][1] * matRadii[1][2]) + (eVectors[0][2] * matRadii[2][2]);
          matProd[1][0] = (eVectors[1][0] * matRadii[0][0]) + (eVectors[1][1] * matRadii[1][0]) + (eVectors[1][2] * matRadii[2][0]);
          matProd[1][1] = (eVectors[1][0] * matRadii[0][1]) + (eVectors[1][1] * matRadii[1][1]) + (eVectors[1][2] * matRadii[2][1]);
          matProd[1][2] = (eVectors[1][0] * matRadii[0][2]) + (eVectors[1][1] * matRadii[1][2]) + (eVectors[1][2] * matRadii[2][2]);
          matProd[2][0] = (eVectors[2][0] * matRadii[0][0]) + (eVectors[2][1] * matRadii[1][0]) + (eVectors[2][2] * matRadii[2][0]);
          matProd[2][1] = (eVectors[2][0] * matRadii[0][1]) + (eVectors[2][1] * matRadii[1][1]) + (eVectors[2][2] * matRadii[2][1]);
          matProd[2][2] = (eVectors[2][0] * matRadii[0][2]) + (eVectors[2][1] * matRadii[1][2]) + (eVectors[2][2] * matRadii[2][2]);

            // Producto xyz con matProd y suma con el centro
          std::vector< float > puntsResp[8];
          for(int  i = 0; i < 8; i++)
          {
            puntsResp[i].push_back((matProd[0][0] * puntos[i][0]) + (matProd[0][1] * puntos[i][1]) + (matProd[0][2] * puntos[i][2]));
            puntsResp[i].push_back((matProd[1][0] * puntos[i][0]) + (matProd[1][1] * puntos[i][1]) + (matProd[1][2] * puntos[i][2]));
            puntsResp[i].push_back((matProd[2][0] * puntos[i][0]) + (matProd[2][1] * puntos[i][1]) + (matProd[2][2] * puntos[i][2]));

            puntsResp[i][0] += centro[0];
            puntsResp[i][1] += centro[1];
            puntsResp[i][2] += centro[2];
          }

          ObjectView* obboxAll = View::AddOrientedBoundingBox(puntsResp);
          Componente* cp = new Componente();
          cp->name = "obboxAll";
          cp->obj = obboxAll;
          cp->nCant = cp->obj->getVertices().size();
          Objects.push_back(cp);
        }
      }
      else
      {
        std::cout << "No objects found.";
      }

      ar = "";
    }

  } // elihw

  draw_thread.join( );

  delete myFirstCube;

  return( 0 );
}

// eof - main.cxx
