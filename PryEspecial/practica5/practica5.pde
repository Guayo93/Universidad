float posX, posY, h, l, modX, modY;

void setup()
{
  size( 600, 500 );
  background( 255 );
  posX = width/2;
  posY = height/2;
  modX = modY = 5;
  h = l = 50;
}

void draw()
{
  background( 255 );
  fill( 255, 0, 0 );
  rect( posX, posY, h, l );
  
  if( keyPressed )
  {
    keyPressed();
  }
}

void keyPressed()
{
  if( key == 'w' )
  {
    posY -= modY;
  }
  if( key == 's' )
  {
    posY += modY;
  }
  if( key == 'a' )
  {
    posX -= modX;
  }
  if( key == 'd' )
  {
    posX += modX;
  }
}