/*
 Game:
 - Arroja excepcion si y solo si se crea en n dimensiones y se intenta acceder o modificar en un numero de dimensiones diferentes.
 - soporta 2d y 3d (no estoy 100% seguro).
 - hasta ahora no encontre como totearlo.
 - cualquier acceso o modificacion deber estar en un try-catch ( dado a que soy flojo y use throws).
*/

class World {

  ArrayList<ArrayList<Integer>> matrix;

  public World( int x, int y ) {
    this.matrix = new ArrayList<ArrayList<Integer>>();
    for ( int i = 0; i < x; i++ ) {
      matrix.add( new ArrayList<Integer>() );
      for ( int j = 0; j < y; j++) {
        matrix.get(i).add(0);
      }
    }
  }

  public int get( int x, int y) {
    return this.matrix.get(x).get(y);
  }

  public void set( int x, int y, int value ) {
    this.matrix.get(x).set(y, value);
  }
}

class Game {

  ArrayList<World> m;
  ArrayList<World> future;
  int[] dims;
  int type;
  int rule;

  public Game( int x, int y, int rule) {
    m = new ArrayList<World>();
    m.add( new World(x, y) );
    
    future = new ArrayList<World>();
    future.add(new World(x,y));
    
    type = 0;
    this.rule = rule;
    dims = new int[2];
    dims[0] = x;
    dims[1] = y;
  }

  public Game( int x, int y, int z, int rule) {
    m = new ArrayList<World>();
    for ( int i = 0; i < x; i++ ) {
      m.add( new World(y, z) );
    }
    
    future = new ArrayList<World>();
    for ( int i = 0; i < x; i++ ) {
      future.add( new World(y, z) );
    }
    
    type = 1;
    this.rule = rule;
    dims = new int[3];
    dims[0] = x;
    dims[1] = y;
    dims[2] = z;
  }

  public int get( int x, int y) throws Exception {
    if ( type == 0) {
      return this.m.get(0).get(x, y);
    } else {
      throw new Exception("Wrong dimension exception");
    }
  }

  public int get( int x, int y, int z) throws Exception {
    if ( type == 1) {
      return this.m.get(x).get(y, z);
    } else {
      throw new Exception("Wrong dimension exception");
    }
  }

  public void set( int x, int y, int value ) throws Exception {
    if ( type == 0) {
      this.m.get(0).set(x, y, value);
    } else {
      throw new Exception("Wrong dimension exception");
    }
  }

  public void set( int x, int y, int z, int value ) throws Exception {
    if ( type == 1) {
      this.m.get(x).set(y, z, value);
    } else {
      throw new Exception("Wrong dimension exception");
    }
  }

  public void update() throws Exception {
    if ( type == 0) {
      update2d();
    } else if (type == 1) {
      update3d();
    }
  }

  private void sweep() throws Exception {
    for ( int i = 0; i < dims[0]; i++) {
      for ( int j = 0; j < dims[1]; j++) {
        if ( type == 1 ) {
          for ( int k = 0; k < dims[2]; k++ ) {
            int aux = future.get(i).get(j,k);
            set(i,j,k,aux);
          }
        } else {
          int aux = future.get(0).get(i,j);
          set(i,j,aux);
        }
      }
    }
  }

  private void update2d() throws Exception {
    //-1 marked for life
    //-2 marked for death
    for ( int i = 0; i < dims[0]; i++ ) {
      for ( int j = 0; j < dims[1]; j++) {
        int c = 0;
        //check i
        //check j-1
        if ( j-1 >= 0) {
          if ( get(i, j-1)== 1) {
            c++;
          }
        }
        //check j+1
        if ( j+1 < dims[1] ) {
          if ( get(i, j+1) == 1) {
            c++;
          }
        }

        //check i-1
        if ( i-1 >= 0) {
          //check j-1
          if ( j-1 >= 0) {
            if ( get(i-1, j-1)== 1) {
              c++;
            }
          }
          //check j
          if ( get(i-1, j) == 1) {
            c++;
          }
          //check j+1
          if ( j+1 < dims[1] ) {
            if ( get(i-1, j+1) == 1) {
              c++;
            }
          }
        }

        //check i+1
        if ( i+1 < dims[0] ) {
          //check j-1
          if ( j-1 >= 0) {
            if ( get(i+1, j-1)== 1) {
              c++;
            }
          }
          //check j
          if ( get(i+1, j) == 1) {
            c++;
          }
          //check j+1
          if ( j+1 < dims[1] ) {
            if ( get(i+1, j+1) == 1) {
              c++;
            }
          }
        }   
        
        /*if( c != 0 )
          println("i: "+i+", j: "+j+", c: "+c);*/
        int aux = get(i,j);
        //if dead and is about to live
        if ( c == rule && aux == 0) {
          //mark for life
          future.get(0).set(i,j,1);
        }else
        //if alive and about to die
        if ( (c < rule-1 || c > rule) && aux == 1){
          //mark for death
          //println("DEATH i: "+i+", j: "+j+", c: "+c);
          future.get(0).set(i,j,0);
        }else{
          future.get(0).set(i,j,aux);
        }
      }
    }
    sweep();
  }

  private void update3d() throws Exception {
    //for
    for ( int i = 0; i < dims[0]; i++ ) {
      for ( int j = 0; j < dims[1]; j++ ) {
        for ( int k = 0; k < dims[2]; k++ ) {
          int c = neighbors3d(i, j, k);
          
          int aux = this.get(i, j, k);
          //if dead and is about to live
          if ( c == rule && aux == 0) {
            //mark for life
            future.get(i).set(j, k, 1);
          }else

          //if alive and about to die
          if ( (c < rule-1 || c > rule) && aux == 1) {
            //mark for death
            future.get(i).set(j,k,0);
          }else{
            future.get(i).set(j,k,aux);
          }
        }
      }
    }
    //rof
    sweep();
  }

  private int neighbors3d( int x, int y, int z) throws Exception {
    int c = 0;
    //x-1
    if ( x-1 >= 0) {
      //y-1
      if ( y-1 >= 0) {
        //z-1
        if ( z-1 >= 0) {
          c += get(x-1, y-1, z-1);
        }
        //z
        c += get(x-1, y-1, z);
        //z+1
        if ( z+1 < dims[2] ) {
          c += get(x-1, y-1, z+1);
        }
      }
      //y
      //z-1
      if ( z-1 >= 0) {
        c += get(x-1, y, z-1);
      }
      //z
      c += get(x-1, y, z);
      //z+1
      if ( z+1 < dims[2] ) {
        c += get(x-1, y, z+1);
      }
      //y+1
      if ( y+1 < dims[1] ) {
        //z-1
        if ( z-1 >= 0) {
          c += get(x-1, y+1, z-1);
        }
        //z
        c += get(x-1, y+1, z);
        //z+1
        if ( z+1 < dims[2] ) {
          c += get(x-1, y+1, z+1);
        }
      }
    }
    //x
    //y-1
    if ( y-1 >= 0) {
      //z-1
      if ( z-1 >= 0) {
        c += get(x, y-1, z-1);
      }
      //z
      c += get(x, y-1, z);
      //z+1
      if ( z+1 < dims[2] ) {
        c += get(x, y-1, z+1);
      }
    }
    //y
    //z-1
    if ( z-1 >= 0) {
      c += get(x, y, z-1);
    }
    //z
    //this one is the current pos
    //z+1
    if ( z+1 < dims[2] ) {
      c += get(x, y, z+1);
    }
    //y+1
    if ( y+1 < dims[1] ) {
      //z-1
      if ( z-1 >= 0) {
        c += get(x, y+1, z-1);
      }
      //z
      c += get(x, y+1, z);
      //z+1
      if ( z+1 < dims[2] ) {
        c += get(x, y+1, z+1);
      }
    }
    //x+1
    if ( x+1 < dims[0] ) {
      //y-1
      if ( y-1 >= 0) {
        //z-1
        if ( z-1 >= 0) {
          c += get(x+1, y-1, z-1);
        }
        //z
        c += get(x+1, y-1, z);
        //z+1
        if ( z+1 < dims[2] ) {
          c += get(x+1, y-1, z+1);
        }
      }
      //y
      //z-1
      if ( z-1 >= 0) {
        c += get(x+1, y, z-1);
      }
      //z
      c += get(x+1, y, z);
      //z+1
      if ( z+1 < dims[2] ) {
        c += get(x+1, y, z+1);
      }
      //y+1
      if ( y+1 < dims[1] ) {
        //z-1
        if ( z-1 >= 0) {
          c += get(x+1, y+1, z-1);
        }
        //z
        c += get(x+1, y+1, z);
        //z+1
        if ( z+1 < dims[2] ) {
          c += get(x+1, y+1, z+1);
        }
      }
    }
    return c;
  }
}