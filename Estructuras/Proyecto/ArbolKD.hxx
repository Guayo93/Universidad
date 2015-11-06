#include "Point.h"
#include <math.h>

ArbolKD::ArbolKD()
{
  this->raiz = NULL;
}

ArbolKD::~ArbolKD()
{

}

NodoKD* ArbolKD::darRaiz()
{
  return this->raiz;
}

void ArbolKD::setRaiz( NodoKD* nR )
{
  this->raiz = nR;
}

bool ArbolKD::insertarNodo( float x, float y, float z )
{
  Point p;
  p.x = x;
  p.y = y;
  p.z = z;

  NodoKD* n = new NodoKD();
  n->setPoint( p );

  if(this->raiz == NULL)
  {
    n->setTag('x');
    this->setRaiz( n );
    return true;
  }
  else
  {
    return this->raiz->insertarNodo( n );
  }

  return false;
}

bool ArbolKD::eliminarNodo( float x, float y, float z )
{
  Point poin;
  poin.x = x;
  poin.y = y;
  poin.z = z;

  if(this->raiz != NULL)
  {
    if(this->raiz->darPoint() == poin)
    {
      bool elim = false;
      NodoKD* n = this->raiz;

      if(n->darIzquierdo() == NULL && n->darDerecho() == NULL)
      {
        this->setRaiz(NULL);
        delete n;
        elim = true;
      }

      if(n->darIzquierdo() != NULL && n->darDerecho() == NULL && elim == false)
      {
        this->setRaiz(n->darDerecho());
        delete n;
        elim = true;
      }

      if(n->darIzquierdo() == NULL && n->darDerecho() != NULL && elim == false)
      {
        this->setRaiz(n->darDerecho());
        delete n;
        elim = true;
      }

      if(n->darIzquierdo() != NULL && n->darDerecho() != NULL && elim == false)
      {
        NodoKD* mdi = n->darIzquierdo();

        while(mdi->darDerecho() != NULL)
        {
          mdi = mdi->darDerecho();
        }

        bool elim2 = false;
        if(n->darIzquierdo()->darPoint() == mdi->darPoint())
        {
          n->setIzquierdo(mdi->darIzquierdo());
          elim2 = true;
        }
        else
        {
          elim2 = this->eliminarNodo(mdi->darPoint().x, mdi->darPoint().y, mdi->darPoint().z);
        }
        mdi->setIzquierdo(n->darIzquierdo());
        mdi->setDerecho(n->darDerecho());

        if(elim2 == true)
        {
          this->setRaiz(mdi);
          delete n;
          elim = true;
        }
      }

      return elim;
    }
    else
    {
      NodoKD* n = this->buscarNodo(x, y, z);

      if(n != NULL)
      {
        bool elim = false;
        NodoKD* p = this->buscarPadre(x, y, z);

        if(n->darIzquierdo() == NULL && n->darDerecho() == NULL)
        {
          if(p->darIzquierdo() != NULL)
          {
            if(p->darIzquierdo()->darPoint() == n->darPoint())
            {
              p->setIzquierdo(NULL);
              delete n;
              elim = true;
            }
          }

          if(p->darDerecho() != NULL && elim == false)
          {
            if(p->darDerecho()->darPoint() == n->darPoint())
            {
              p->setDerecho(NULL);
              delete n;
              elim = true;
            }
          }
        }

        if(n->darIzquierdo() != NULL && n->darDerecho() == NULL && elim == false)
        {
          if(p->darIzquierdo() != NULL)
          {
            if(p->darIzquierdo()->darPoint() == n->darPoint())
            {
              p->setIzquierdo(n->darIzquierdo());
              delete n;
              elim = true;
            }
          }

          if(p->darDerecho() != NULL && elim == false)
          {
            if(p->darDerecho()->darPoint() == n->darPoint())
            {
              p->setDerecho(n->darIzquierdo());
              delete n;
              elim = true;
            }
          }
        }

        if(n->darIzquierdo() == NULL && n->darDerecho() != NULL && elim == false)
        {
          if(p->darIzquierdo() != NULL)
          {
            if(p->darIzquierdo()->darPoint() == n->darPoint())
            {
              p->setIzquierdo(n->darDerecho());
              delete n;
              elim = true;
            }
          }

          if(p->darDerecho() != NULL && elim == false)
          {
            if(p->darDerecho()->darPoint() == n->darPoint())
            {
              p->setDerecho(n->darDerecho());
              delete n;
              elim = true;
            }
          }
        }

        if(n->darIzquierdo() != NULL && n->darDerecho() != NULL && elim == false)
        {
          NodoKD* mdi = n->darIzquierdo();

          while(mdi->darDerecho() != NULL)
          {
            mdi = mdi->darDerecho();
          }

          bool elim2 = false;
          if(n->darIzquierdo()->darPoint() == mdi->darPoint())
          {
            n->setIzquierdo(NULL);
            elim2 = true;
          }
          else
          {
            elim2 = this->eliminarNodo(mdi->darPoint().x, mdi->darPoint().y, mdi->darPoint().z);
          }
          mdi->setIzquierdo(n->darIzquierdo());
          mdi->setDerecho(n->darDerecho());

          if(elim2 == true)
          {
            if(p->darIzquierdo() != NULL)
            {
              if(p->darIzquierdo()->darPoint() == n->darPoint())
              {
                p->setIzquierdo(mdi);
                delete n;
                elim = true;
              }
            }

            if(p->darDerecho() != NULL && elim == false)
            {
              if(p->darDerecho()->darPoint() == n->darPoint())
              {
                p->setDerecho(mdi);
                delete n;
                elim = true;
              }
            }
          }
        }

        return elim;
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    return false;
  }
}

NodoKD* ArbolKD::buscarNodo( float x, float y, float z )
{
  NodoKD* n = NULL;

  Point p;
  p.x = x;
  p.y = y;
  p.z = z;

  if(this->raiz != NULL)
  {
    n = raiz->buscarNodo(p);
  }

  return n;
}

NodoKD* ArbolKD::buscarPadre( float x, float y, float z )
{
  NodoKD* n = NULL;

  Point p;
  p.x = x;
  p.y = y;
  p.z = z;

  if(this->raiz != NULL)
  {
    n = raiz->buscarPadre(p);
  }

  return n;
}

NodoKD* ArbolKD::buscarVecinoMasCercano( float x, float y, float z )
{
  if(this->raiz != NULL)
  {
    char tagD = ' ';
    if(x <= this->raiz->darPoint().x)
    {
      tagD = 'i';
    }
    else
    {
      tagD = 'd';
    }

    this->insertarNodo(x, y, z);
    NodoKD* aux = this->buscarPadre(x, y, z);
    NodoKD* resp = aux;
    float dist = sqrt(((x - aux->darPoint().x) * (x - aux->darPoint().x)) + ((y - aux->darPoint().y) * (y - aux->darPoint().y)) + ((z - aux->darPoint().z) * (z - aux->darPoint().z)));

    if(tagD == 'i')
    {
      while((aux->darPoint() == this->raiz->darPoint()) == false)
      {
        float temp = sqrt(((x - aux->darPoint().x) * (x - aux->darPoint().x)) + ((y - aux->darPoint().y) * (y - aux->darPoint().y)) + ((z - aux->darPoint().z) * (z - aux->darPoint().z)));

        if(temp < dist)
        {
          resp = aux;
          dist = temp;
        }

        aux = this->buscarPadre(aux->darPoint().x, aux->darPoint().y, aux->darPoint().z);
      }

      this->eliminarNodo(x, y, z);

      if(dist > sqrt(((x - this->raiz->darPoint().x) * (x - this->raiz->darPoint().x)) + ((y - y) * (y - y)) + ((z - z) * (z - z))))
      {
        NodoKD* n = new NodoKD();
        Point poin;
        poin.x = x;
        poin.y = y;
        poin.z = z;
        n->setPoint(poin);

        this->raiz->darDerecho()->insertarNodo(n);
        aux = this->raiz->darDerecho()->buscarPadre(poin);

        while((aux->darPoint() == this->raiz->darPoint()) == false)
        {
          float temp = sqrt(((x - aux->darPoint().x) * (x - aux->darPoint().x)) + ((y - aux->darPoint().y) * (y - aux->darPoint().y)) + ((z - aux->darPoint().z) * (z - aux->darPoint().z)));

          if(temp < dist)
          {
            resp = aux;
            dist = temp;
          }

          aux = this->buscarPadre(aux->darPoint().x, aux->darPoint().y, aux->darPoint().z);
        }

        this->eliminarNodo(x, y, z);
      }

      if(dist > sqrt(((x - this->raiz->darPoint().x) * (x - this->raiz->darPoint().x)) + ((y - this->raiz->darPoint().y) * (y - this->raiz->darPoint().y)) + ((z - this->raiz->darPoint().z) * (z - this->raiz->darPoint().z))))
      {
        resp = this->raiz;
      }
    }

    if(tagD = 'd')
    {
      while((aux->darPoint() == this->raiz->darPoint()) == false)
      {
        float temp = sqrt(((x - aux->darPoint().x) * (x - aux->darPoint().x)) + ((y - aux->darPoint().y) * (y - aux->darPoint().y)) + ((z - aux->darPoint().z) * (z - aux->darPoint().z)));

        if(temp < dist)
        {
          resp = aux;
          dist = temp;
        }

        aux = this->buscarPadre(aux->darPoint().x, aux->darPoint().y, aux->darPoint().z);
      }

      this->eliminarNodo(x, y, z);

      if(dist > sqrt(((x - this->raiz->darPoint().x) * (x - this->raiz->darPoint().x)) + ((y - y) * (y - y)) + ((z - z) * (z - z))))
      {
        NodoKD* n = new NodoKD();
        Point poin;
        poin.x = x;
        poin.y = y;
        poin.z = z;
        n->setPoint(poin);

        this->raiz->darIzquierdo()->insertarNodo(n);
        aux = this->raiz->darIzquierdo()->buscarPadre(poin);

        while((aux->darPoint() == this->raiz->darPoint()) == false)
        {
          float temp = sqrt(((x - aux->darPoint().x) * (x - aux->darPoint().x)) + ((y - aux->darPoint().y) * (y - aux->darPoint().y)) + ((z - aux->darPoint().z) * (z - aux->darPoint().z)));

          if(temp < dist)
          {
            resp = aux;
            dist = temp;
          }

          aux = this->buscarPadre(aux->darPoint().x, aux->darPoint().y, aux->darPoint().z);
        }

        this->eliminarNodo(x, y, z);
      }

      if(dist > sqrt(((x - this->raiz->darPoint().x) * (x - this->raiz->darPoint().x)) + ((y - this->raiz->darPoint().y) * (y - this->raiz->darPoint().y)) + ((z - this->raiz->darPoint().z) * (z - this->raiz->darPoint().z))))
      {
        resp = this->raiz;
      }
    }

    return resp;
  }
  else
  {
    return NULL;
  }
}

std::vector< NodoKD > buscarNodosRango( float x1, float x2, float y1, float y2, float z1, float z2 );

void ArbolKD::recorridoPreOrden()
{
  if(this->raiz == NULL)
  {
    std::cout << "El arbol esta vacio." << std::endl;
  }
  else
  {
    std::cout << this->raiz->darPoint() << std::endl;

    if(this->raiz->darIzquierdo() != NULL)
    {
      this->raiz->darIzquierdo()->recorridoPreOrden();
    }

    if(this->raiz->darDerecho() != NULL)
    {
      this->raiz->darDerecho()->recorridoPreOrden();
    }
  }
}

void ArbolKD::recorridoInOrden()
{
  if(this->raiz == NULL)
  {
    std::cout << "El arbol esta vacio." << std::endl;
  }
  else
  {
    if(this->raiz->darIzquierdo() != NULL)
    {
      this->raiz->darIzquierdo()->recorridoInOrden();
    }

    std::cout << this->raiz->darPoint() << std::endl;

    if(this->raiz->darDerecho() != NULL)
    {
      this->raiz->darDerecho()->recorridoInOrden();
    }
  }
}

void ArbolKD::recorridoPosOrden()
{
  if(this->raiz == NULL)
  {
    std::cout << "El arbol esta vacio." << std::endl;
  }
  else
  {
    if(this->raiz->darIzquierdo() != NULL)
    {
      this->raiz->darIzquierdo()->recorridoPosOrden();
    }

    if(this->raiz->darDerecho() != NULL)
    {
      this->raiz->darDerecho()->recorridoPosOrden();
    }

    std::cout << this->raiz->darPoint() << std::endl;
  }
}
