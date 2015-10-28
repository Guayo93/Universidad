#include "View.h"

#include <cmath>

// -------------------------------------------------------------------------
// Link static members

bool View::Running;
int View::ScreenWidth;
int View::ScreenHeight;
bool View::MouseLeftDown;
bool View::MouseRightDown;
float View::MouseX;
float View::MouseY;
float View::CameraAngleX;
float View::CameraAngleY;
float View::CameraDistance;
float View::CameraCenterX;
float View::CameraCenterY;
float View::CameraCenterZ;
float View::MinX;
float View::MinY;
float View::MinZ;
float View::MaxX;
float View::MaxY;
float View::MaxZ;
std::vector< ObjectView* > View::Objects;

// -------------------------------------------------------------------------
void View::
DisplayCB( )
{
  // Prepare canvas and camera
  glClear(
    GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
    );
  glPushMatrix( );
  glTranslatef( float( 0 ), float( 0 ), -View::CameraDistance );
  glRotatef( View::CameraAngleX, float( 1 ), float( 0 ), float( 0 ) );
  glRotatef( View::CameraAngleY, float( 0 ), float( 1 ), float( 0 ) );
  glTranslatef(
    -View::CameraCenterX,
    -View::CameraCenterY,
    -View::CameraCenterZ
    );

  // Draw objects
  for( unsigned int i = 0; i < View::Objects.size( ); ++i )
    View::Objects[ i ]->Draw( );

  // Finish frame rendering
  glPopMatrix( );
  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
void View::
ReshapeCB( int w, int h )
{
  View::ScreenWidth = w;
  View::ScreenHeight = h;
  View::ToPerspective( );
}

// -------------------------------------------------------------------------
void View::
TimerCB( int millisec )
{
  glutTimerFunc( millisec, TimerCB, millisec );
  glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void View::
IdleCB( )
{
  glutPostRedisplay( );
  if( !( View::Running ) )
    throw( 0 );
}

// -------------------------------------------------------------------------
void View::
KeyboardCB( unsigned char key, int x, int y )
{
  switch( key )
  {
  default:
    break;
  } // hctiws
}

// -------------------------------------------------------------------------
void View::
MouseCB( int button, int state, int x, int y )
{
  View::MouseX = x;
  View::MouseY = y;
  if( button == GLUT_LEFT_BUTTON )
    View::MouseLeftDown = ( state == GLUT_DOWN );
  else if( button == GLUT_RIGHT_BUTTON )
    View::MouseRightDown = ( state == GLUT_DOWN );
}

// -------------------------------------------------------------------------
void View::
MouseMotionCB( int x, int y )
{
  if( View::MouseLeftDown )
  {
    View::CameraAngleY += ( x - View::MouseX );
    View::CameraAngleX += ( y - View::MouseY );
    View::MouseX = x;
    View::MouseY = y;
  }
  if( View::MouseRightDown)
  {
    View::CameraDistance -= ( y - View::MouseY ) * 0.2f;
    View::MouseY = y;

  } // fi
}

// -------------------------------------------------------------------------
void View::
AddObject(
  ObjectView* o,
  const float& r, const float& g, const float& b
  )
{
  View::Objects.push_back( o );
  ( *( View::Objects.rbegin( ) ) )->SetColor( r, g, b );

  if( View::Objects.size( ) > 1 )
  {
    View::MinX = ( o->GetMinX( ) < View::MinX )? o->GetMinX( ): View::MinX;
    View::MaxX = ( o->GetMaxX( ) > View::MaxX )? o->GetMaxX( ): View::MaxX;

    View::MinY = ( o->GetMinY( ) < View::MinY )? o->GetMinY( ): View::MinY;
    View::MaxY = ( o->GetMaxY( ) > View::MaxY )? o->GetMaxY( ): View::MaxY;

    View::MinZ = ( o->GetMinZ( ) < View::MinZ )? o->GetMinZ( ): View::MinZ;
    View::MaxZ = ( o->GetMaxZ( ) > View::MaxZ )? o->GetMaxZ( ): View::MaxZ;
  }
  else
  {
    View::MinX = o->GetMinX( );
    View::MinY = o->GetMinY( );
    View::MinZ = o->GetMinZ( );
    View::MaxX = o->GetMaxX( );
    View::MaxY = o->GetMaxY( );
    View::MaxZ = o->GetMaxZ( );

  } // fi

  float dx = View::MaxX - View::MinX;
  float dy = View::MaxY - View::MinY;
  float dz = View::MaxZ - View::MinZ;
  View::CameraDistance =
    std::sqrt( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) );
  View::CameraDistance *= double( 1.2 );

  View::CameraCenterX = ( View::MaxX + View::MinX ) / float( 2 );
  View::CameraCenterY = ( View::MaxY + View::MinY ) / float( 2 );
  View::CameraCenterZ = ( View::MaxZ + View::MinZ ) / float( 2 );
}

// -------------------------------------------------------------------------
void View::
DrawLoop( )
{
  try
  {
    glutMainLoop( );
  }
  catch( int error_code )
  {
  } // yrt
}

// -------------------------------------------------------------------------
void View::
Init( int argc, char* argv[] )
{
  View::InitValues( );
  View::InitGLUT( argc, argv );
  View::InitGL( );
}

// -------------------------------------------------------------------------
void View::
InitGL( )
{
  glShadeModel( GL_SMOOTH );
  glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
  glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
  glDisable( GL_COLOR_MATERIAL );
  glClearColor( 0, 0, 0, 0 );
  glClearStencil( 0 );
  glClearDepth( float( 1 ) );
  glDepthFunc( GL_LEQUAL );
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_CULL_FACE );
  View::InitLights( );
}

// -------------------------------------------------------------------------
int View::
InitGLUT( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL );
  glutInitWindowSize( View::ScreenWidth, View::ScreenHeight );
  glutInitWindowPosition( 100, 100 );
  int handle = glutCreateWindow( argv[ 0 ] );
  glutDisplayFunc( DisplayCB );
  glutIdleFunc( IdleCB );
  glutReshapeFunc( ReshapeCB );
  glutKeyboardFunc( KeyboardCB );
  glutMouseFunc( MouseCB );
  glutMotionFunc( MouseMotionCB );
  return( handle );
}

// -------------------------------------------------------------------------
bool View::
InitValues( )
{
  View::Running = true;
  View::ScreenWidth = 500;
  View::ScreenHeight = 500;
  View::MouseLeftDown = View::MouseRightDown = false;
  View::MouseX = View::MouseY = float( 0 );
  View::CameraAngleX = View::CameraAngleY = float( 0 );
  View::CameraDistance = float( 10 );
  View::CameraCenterX =
    View::CameraCenterY =
    View::CameraCenterZ = float( 0 );
  View::MinX = float( -1 );
  View::MinY = float( -1 );
  View::MinZ = float( -1 );
  View::MaxX = float( 1 );
  View::MaxY = float( 1 );
  View::MaxZ = float( 1 );

  return( true );
}

// -------------------------------------------------------------------------
void View::
InitLights( )
{
  /*
    GLfloat lightKa[ ] = { .2f, .2f, .2f, 1.0f };
    GLfloat lightKd[ ] = { .7f, .7f, .7f, 1.0f };
    GLfloat lightKs[ ] = { 1, 1, 1, 1 };
    glLightfv( GL_LIGHT0, GL_AMBIENT, lightKa );
    //glLightfv( GL_LIGHT0, GL_DIFFUSE, lightKd );
    //glLightfv( GL_LIGHT0, GL_SPECULAR, lightKs );
    float lightPos[ 4 ] = { 0, 0, 20, 1 };
    glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
    glEnable( GL_LIGHT0 );

    glLightfv( GL_LIGHT1, GL_AMBIENT, lightKa );
    //glLightfv( GL_LIGHT1, GL_DIFFUSE, lightKd );
    //glLightfv( GL_LIGHT1, GL_SPECULAR, lightKs );
    float lightPos1[ 4 ] = { 0, 0, -20, 1 };
    glLightfv( GL_LIGHT1, GL_POSITION, lightPos1 );
    glEnable( GL_LIGHT1 );
  */
}

// -------------------------------------------------------------------------
void View::
SetCamera(
  float posX, float posY, float posZ,
  float targetX, float targetY, float targetZ
  )
{
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );
  gluLookAt(
    posX, posY, posZ,
    targetX, targetY, targetZ,
    float( 0 ), float( 1 ), float( 0 )
    );
}

// -------------------------------------------------------------------------
void View::
ToPerspective( )
{
  glViewport(
    0, 0,
    static_cast< GLsizei >( View::ScreenWidth ),
    static_cast< GLsizei >( View::ScreenHeight )
    );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluPerspective(
    float( 60 ),
    float( View::ScreenWidth ) / float( View::ScreenHeight ),
    float( 1e-10 ), float( 1000 )
    );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );
}

// View.cxx
