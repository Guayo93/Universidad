#!/usr/bin/python

import sys
import MineSweeper
from random import randint

class MineSolver:
    def __init__(self, width , height , mines):
        self.width = int(width)
        self.height = int(height)
        self.mines = int(mines)
        init = float(float(self.mines)/float(self.width * self.height))
        self.picked = [[ 0 for j in range(self.width) ] for i in range(self.height)]
        self.values = [[ -1 for j in range(self.width) ] for i in range(self.height)]
        self.probs = [[ init for j in range(self.width)] for i in range(self.height)]
        self.hasChosen = False
    ##end def init

    def getBestChoice( self ):
        if( self.hasChosen ):
            minimunProb = float(1241358798519745)
            x = -1
            y = -1
            for j in range(self.width):
                for i in range( self.height ):
                    if( self.probs[j][i] < minimunProb and self.picked[j][i] == 0 ):
                        x = i
                        y = j
                        minimunProb = self.probs[j][i]
                    ## end if
                ## end for i
            ## end for j
        else:
            self.hasChosen = True
            x = randint( 0 , (self.height - 1) )
            y = randint( 0 , (self.width  - 1) )
        ## end if
        self.picked[y][x] = 1
        return [y,x]
    ## end def getBestChoice

    def setMinevalue( self , j , i , value ):
        if( value != -1 ):
            self.values[j][i] = value
            self.probs[j][i] = 0
            self.updateProbs()
        ## end if
    ## end def setMinevalue

    def countPicked( self ):
        count = 0
        for j in range(self.width):
            for i in range(self.height):
                count += self.picked[j][i]
            ## end for i
        ## end for j
        return count
    ## end def countPicked

    def isInside( self , y , x  ):
        inside = True
        if y < 0 or y >= self.width:
            inside = False
        ## end if
        if x < 0 or x >= self.height:
            inside = False
        ## end if
        return inside
    ## end def isInside

    def getNeighbors( self , y , x ):
        count = 0;
        dirs = [ [j+1,i+1] , [j-1,i-1] , [j+1,i-1] , [j-1,i+1] , [j,i+1] , [j+1,i] , [j-1,i] , [j,i-1] ]
        for k in dirs:
            y = k[0]
            x = k[1]
            if( self.isInside( y , x ) and self.picked[y][x] == 0):
                count += 1
            ## end if
        ## end for k
        return count
    ## end def getNeighbors

    def updateProbs( self ):
        self.probs = [[ float(0) for j in range(self.width)] for i in range(self.height)]
        remainingMines = self.mines
        remainingSpaces = (self.width * self.height) - self.countPicked()
        for j in range(self.width):
            for i in range(self.height):
                if( self.picked[j][i] == 1 ):
                    self.probs[j][i] = float(0)
                else:
                    dirs = [ [j+1,i+1] , [j-1,i-1] , [j+1,i-1] , [j-1,i+1] , [j,i+1] , [j+1,i] , [j-1,i] , [j,i-1] ]
                    hasNeigh = False
                    hasCeroNeighbour = False
                    ki = 0
                    while ki < len(dirs) and not hasCeroNeighbour:
                        k = dirs[ki]
                        y = k[0]
                        x = k[1]
                        if( self.isInside(y,x) and self.picked[y][x] == 1 ):
                            hasNeigh = True
                            if( self.values[y][x] != 0 ):
                                mineCount = self.values[y][x]
                                neighCount = self.getNeighbors(y,x)
                                if( neighCount != 0 ):
                                    self.probs[j][i] += float(float(mineCount)/float(neighCount))
                                ## end if
                            else:
                                hasCeroNeighbour = True
                                self.probs[j][i] = float(0)
                            ## end if
                        ## end if
                        ki += 1
                    ## end while ki
                    if( not hasNeigh ):
                        self.probs[j][i] = float(float(remainingMines)/float(remainingSpaces))
                    ## end if
                ## end if
            ## end for i
        ## end for j
    ## end def updateProbs

    def Print( self ):
        for j in range( self.width ):
            for i in range( self.height ):
                sys.stdout.write( '+---' )
            print '+'
            print '|',
            for i in range( self.width ):
                print float(self.probs[ j ][ i ]),
                ##print str(j)+"+"+str(i),
                print '|',
            print
        for i in range( self.width ):
            sys.stdout.write( '+---' )
        print '+'
    ## end def

    def hasFinished( self ):
        uncovered = self.countPicked()
        total = self.width * self.height
        finito = False
        if( total - uncovered == self.mines ):
            finito = True
        ## end if
        return finito
    ## end def hasFinished
##end class


# -- Check command-line arguments --
argc = len( sys.argv )
if len( sys.argv ) != 4:
    print "Usage:", sys.argv[ 0 ], "width height number_of_mines"
    sys.exit( 1 )
width = sys.argv[ 1 ]
height = sys.argv[ 2 ]
number_of_mines = sys.argv[ 3 ]

# -- Create board and play --
board = MineSweeper.Board( width, height, number_of_mines )
board.Print( )
solver = MineSolver( width , height , number_of_mines )
##solver.Print()
success = 0
while success > -1 and not solver.hasFinished():
    print
    [ j, i ] = solver.getBestChoice( );
    print [j , i]
    success = board.UnCover( i, j )
    solver.setMinevalue( j , i , success )
    board.Print( )
    ##solver.Print( )
    print

## eof - test.py
