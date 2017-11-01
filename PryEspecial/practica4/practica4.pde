PImage img;

void setup()
{
  size( 600, 600 );
  background( 255 );
  img = loadImage( "Lenna.png" );
}

void draw()
{
  image( img, 0, 0 );
  //filter(THRESHOLD);
  filter(GRAY);
}