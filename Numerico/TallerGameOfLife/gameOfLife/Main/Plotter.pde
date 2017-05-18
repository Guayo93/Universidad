class Plotter{
  public Plotter(){}
  
  public void reset(){
    clear();
    background(0);
  }
  
  public void plot2dGame(Game g){
    reset();
    for( int i = 0 ; i < g.dims[0] ; i++ ){
      for( int j = 0 ; j < g.dims[1] ; j++ ){
        try{
          stroke(0);
          fill(#ff0000);
          if( g.get(i,j) == 1 ){
            fill(#00ff00);
          }
          rect(i*10,j*10,10,10);
        }catch( Exception e ){
        
        }
      }
    }
  }
}