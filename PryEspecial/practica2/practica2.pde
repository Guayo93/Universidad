int x, y, modX, modY, colCont, modCol;

void setup()
{
  size( 500, 600 );
  background( 255 );
  modX = modY = 5;
  modCol = 1;
  x = floor( random( 0, width - 50 ) );
  y = floor( random( 0, height - 50 ) );
  colorMode( HSB, 100 );
}

void draw()
{
  fill( colCont, 100, 100 );
  noStroke();
  rect( x, y, 50, 50 );
  
  if( x + 50 >= width || x < 0 )
  {
    modX *= -1;
  }
  if( y + 50 >= height || y < 0 )
  {
    modY *= -1;
  }
  if( colCont >= 100 || colCont < 0 )
  {
    modCol *= -1;
  }
  
  x += modX;
  y += modY;
  colCont += modCol;
}