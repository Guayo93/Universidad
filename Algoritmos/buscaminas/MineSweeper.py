import random
import sys

class Board:
    ## ---------------------------------------------------------------------
    Data   = [[]]
    Covers = [[]]
    NumberOfMines = 0
    Width = 0
    Height = 0
    Explosion = 0

    ## ---------------------------------------------------------------------
    def __init__( self, width, height, number_of_mines ):
        ## Initialize attributes
        self.NumberOfMines = int( number_of_mines )
        self.Width = int( width )
        self.Height = int( height )
        self.Explosion = 0

        ## Fill buffer data
        count = self.NumberOfMines
        size = self.Width * self.Height
        pivot = int( size / 2 )
        data = [ 0 ] * size
        pos = 0
        while count != 0:
            s = random.randrange( 1, pivot )
            pos += s
            while data[ pos % size ] == -1:
                pos += 1
            pos = pos % size
            data[ pos ] = -1
            count -= 1

        ## Fill matrix
        self.Data = \
                  [ [ 0 for i in range( self.Height ) ] \
                    for j in range( self.Width ) ]
        self.Covers = \
                    [ [ 1 for i in range( self.Height ) ] \
                      for j in range( self.Width ) ]
        k = 0
        for j in range( self.Height ):
            for i in range( self.Width ):
                self.Data[ i ][ j ] = data[ k ]
                k += 1

        ## Finish filling
        for j in range( self.Height ):
            for i in range( self.Width ):
                if self.Data[ i ][ j ] == 0:
                    count = 0
                    for y in [ -1, 0, 1 ]:
                        for x in [ -1, 0, 1 ]:
                            if ( x != 0 ) or ( y != 0 ):
                                cx = i + x
                                cy = j + y
                                cond =          ( cx >= 0 )
                                cond = cond and ( cy >= 0 )
                                cond = cond and ( cx < self.Width )
                                cond = cond and ( cy < self.Height )
                                if cond:
                                    if self.Data[ cx ][ cy ] == -1:
                                        count += 1
                    self.Data[ i ][ j ] = count

    ## ---------------------------------------------------------------------
    def UnCover( self, i, j ):
        if self.Explosion:
            return -1
        else:
            cond =          ( i >= 0 )
            cond = cond and ( j >= 0 )
            cond = cond and ( i < self.Width )
            cond = cond and ( j < self.Height )
            if cond:
                if self.Covers[ i ][ j ] == 1:
                    self.Explosion = ( self.Data[ i ][ j ] == -1 )
                    if self.Explosion:
                        self.Covers = \
                                    [ [ 0 for y in range( self.Height ) ] \
                                      for x in range( self.Width ) ]
                    else:
                        self.Covers[ i ][ j ] = 0
                    return self.Data[ i ][ j ]
                else:
                    return 0

    ## ---------------------------------------------------------------------
    def Print( self ):
        for j in range( self.Height ):
            for i in range( self.Width ):
                sys.stdout.write( '+---' )
            print '+'
            print '|',
            for i in range( self.Width ):
                if self.Covers[ i ][ j ] == 1:
                    print ' ',
                else:
                    if self.Data[ i ][ j ] == -1:
                        print '*',
                    else:
                        print self.Data[ i ][ j ],
                print '|',
            print
        for i in range( self.Width ):
            sys.stdout.write( '+---' )
        print '+'

## eof - MineSweeper.py
