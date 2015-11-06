template< class T >
Arista< T >::Arista()
{

}

template< class T >
Arista< T >::~Arista()
{

}

template< class T >
T Arista< T >::darOrigen()
{
  return this->origen;
}

template< class T >
void Arista< T >::setOrigen( T nOri )
{
  this->origen = nOri;
}

template< class T >
T Arista< T >::darDestino()
{
  return this->destino;
}

template< class T >
void Arista< T >::setDestino( T nDes )
{
  this->destino = nDes;
}

template< class T >
bool Arista< T >::darMarca()
{
  return this->marca;
}

template< class T >
void Arista< T >::marcar()
{
  this->marca = true;
}

template< class T >
void Arista< T >::desmarcar()
{
  this->marca = false;
}
