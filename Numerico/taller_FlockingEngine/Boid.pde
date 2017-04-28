public class Boid{
 public PVector p;
 public PVector v;
 public float R;
 
 public Boid(){
  this.p = new PVector();
  this.v = new PVector();
  this.R = 0;
 }
 public Boid(PVector p){
  this.p = p;
  this.v = new PVector();
  this.R = 0;
 } 
 public Boid(PVector p, PVector v){
  this.p = p;
  this.v = v;
  this.R = 0;
 }
 public Boid(PVector p, PVector v, float R){
  this.p = p;
  this.v = v;
  this.R = R;
 }
 public void update(float dt){
  p.add(PVector.mult(v,dt));
 }
 public void addForce(PVector F, float dt){
  v.add(PVector.mult(F,dt));
 }
} 
