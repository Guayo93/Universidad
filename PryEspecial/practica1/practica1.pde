int r, h, l, col, x, y, mod, cont;

void setup()
{
  size( 500, 500 );
  background( 255 );
  colorMode( HSB, 101 );
  cont = 0;
}

void draw()
{
  mod = floor( random( 1, 4 ) );
  r = floor( random( 5, 100 ) );
  h = floor( random( 5, 100 ) );
  l = floor( random( 5, 100 ) );
  x = floor( random( 1, width-50 ) );
  y = floor( random( 1, height-50 ) );
  col = floor( random( 0, 100 ) );
  
  if( cont < 10 )
  {
    noStroke();
    fill( col, 100, 100 );
    if( mod == 1 )
    {
      rect( x, y, h, h );
    }
    else if( mod == 2 )
    {
      rect( x, y, h, l );
    }
    else if( mod == 3 )
    {
      ellipse( x, y, r, r );
    }
  }
  
  cont++;
}