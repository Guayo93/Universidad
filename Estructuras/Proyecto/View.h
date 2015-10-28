#ifndef __VIEW__H__
#define __VIEW__H__

#include <GL/gl.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <vector>
#include "ObjectView.h"

struct View
{
  // Attributes
  static bool Running;
  static int ScreenWidth, ScreenHeight;
  static bool MouseLeftDown, MouseRightDown;
  static float MouseX, MouseY;
  static float CameraAngleX, CameraAngleY, CameraDistance;
  static float CameraCenterX, CameraCenterY, CameraCenterZ;
  static std::vector< ObjectView* > Objects;

  static float MinX, MaxX;
  static float MinY, MaxY;
  static float MinZ, MaxZ;

  // OpenGL callbacks
  static void DisplayCB( );
  static void ReshapeCB( int w, int h );
  static void TimerCB( int millisec );
  static void IdleCB( );
  static void KeyboardCB( unsigned char key, int x, int y );
  static void MouseCB( int button, int state, int x, int y );
  static void MouseMotionCB( int x, int y );

  // OpenGL helpers
  static void AddObject(
    ObjectView* o,
    const float& r = float( 1 ),
    const float& g = float( 1 ),
    const float& b = float( 1 )
    );

  /*
   * Add a bounding box between min and max
   *
   * Returns the newly added mesh. Memory management is now user's responsabilty.
   */
  template< class TVector >
  static ObjectView* AddBoundingBox( const TVector& min, const TVector& max );

  /*
   * Show an oriented bounding box. Points in pnts should be numbered as:
   *
   *                 p4-----p7
   *                /.     /|
   *               / .    / |
   *              p5-+---p6 |
   *              |  p0..|..p3
   *              | '    | /
   *              |'     |/
   *              p1---- p2
   *
   * Returns the newly added mesh. Memory management is now user's responsabilty.
   */
   template< class TVector >
  static ObjectView* AddOrientedBoundingBox( TVector pnts[ 8 ] );

  /*
   * Show an ellipsoid centered in mean, with radii and rotation pm.
   *
   * Returns the newly added mesh. Memory management is now user's responsabilty.
   */
  template< class TMatrix, class TVector >
  static ObjectView* AddEllipsoid(
    const TMatrix& pm, const TVector& mean, const TVector& radii
    );

  static void DrawLoop( );
  static void Init( int argc, char* argv[] );
  static void InitGL( );
  static int InitGLUT( int argc, char* argv[] );
  static bool InitValues( );
  static void InitLights( );
  static void SetCamera(
    float posX, float posY, float posZ,
    float targetX, float targetY, float targetZ
    );
  static void ToPerspective( );
};

#include "View.hxx"

#endif // __VIEW__H__

// eof - View.h
