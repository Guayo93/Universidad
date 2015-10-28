#ifndef __EIGENANALYSIS__H__
#define __EIGENANALYSIS__H__

/** \class EigenAnalysis
 *
 * The class contains routines taken from netlib sources (www.netlib.org).
 * netlib/tql1.c
 * netlib/tql2.c
 * netlib/tred1.c
 * netlib/tred2.c
 *
 * Reference:
 *     num. math. 11, 293-306(1968) by bowdler, martin, reinsch, and
 *     wilkinson.
 *     handbook for auto. comp., vol.ii-linear algebra, 227-240(1971).
 */
template< typename S >
class EigenAnalysis
{
public:
  typedef EigenAnalysis Self;

public:

  /**
   * Compute Eigen values and vectors of A
   */
  static unsigned int Compute(
    const S A[ 3 ][ 3 ], S eValues[ 3 ], S eVectors[ 3 ][ 3 ]
    );

private:

  /**
   * Reduces a real symmetric matrix to a symmetric tridiagonal matrix
   * using and accumulating orthogonal similarity transformations.
   *
   *  Reference:
   *  num. math. 11, 181-195(1968) by martin, reinsch, and wilkinson.
   *    handbook for auto. comp., vol.ii-linear algebra, 212-226(1971).
   */
  static void _Reduce( double*  a, S d[ 3 ], double*  e, double*  z );

  /** Finds the eigenvalues and eigenvectors of a symmetric tridiagonal
   * matrix by the ql method.
   *
   * On input:
   * 'd' contains the diagonal elements of the input matrix.
   * 'e' contains the subdiagonal elements of the input matrix
   * in its last n-1 positions.  e(1) is arbitrary.
   * 'z' contains the transformation matrix produced in the reduction by
   * _Reduce(), if performed. If the
   * eigenvectors of the tridiagonal matrix are desired, z must contain
   * the identity matrix.

   * On Output:
   * 'd' contains the eigenvalues.
   * 'e' has been destroyed.
   * 'z' contains orthonormal eigenvectors of the symmetric tridiagonal
   * (or full) matrix.
   *
   * Returns:
   *          zero       for normal return,
   *          j          if the j-th eigenvalue has not been
   *                     determined after 1000 iterations.
   *
   * Reference
   *  This subroutine is a translation of the algol procedure tql1,
   *  num. math. 11, 293-306(1968) by bowdler, martin, reinsch, and
   *  wilkinson.
   *  handbook for auto. comp., vol.ii-linear algebra, 227-240(1971).
   *
   *  Function Adapted from netlib/tql2.c.
   */
  static unsigned int _EigenDataByQL( S d[ 3 ], double* e, double* z );
};

#endif // __EIGENANALYSIS__H__

 // eof - EigenAnalysis.h
