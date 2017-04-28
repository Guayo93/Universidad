public class GraphicalEngine{
 public float boidSize;
 public float boxSize;
 public color boidColor;
 
 public GraphicalEngine(){
  this.boidSize = 5;
  this.boxSize = 0;
 }
 
 public GraphicalEngine(float boxSize){
  this.boidSize = 5;
  this.boxSize = boxSize;
 }
 
 public GraphicalEngine(float boidSize, float boxSize){
  this.boidSize = 5;
  this.boxSize = boxSize;
 }
 
 public void plotBox(){
  noFill();
  stroke(255);
  box(boxSize);
 }
 public void plotBoid(Boid b){
  fill(boidColor);
  noStroke();
  pushMatrix();
   translate(b.p.x,b.p.y,b.p.z);
   box(boidSize);
  popMatrix(); 
 }
 public void plotFlock(Boid[] bs){
  for(int i=0;i<bs.length;i++){
   plotBoid(bs[i]);
  }
 } 
}  

