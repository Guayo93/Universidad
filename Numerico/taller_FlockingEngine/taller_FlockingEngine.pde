float rotX = 0;
float rotY = 0;

GraphicalEngine graphEngine; 
FlockingEngine flockEngine;
void setup(){
 size(800,600,P3D);
 graphEngine = new GraphicalEngine(10,width/2);
 graphEngine.boidColor = color(255,0,0,150);
 flockEngine = new FlockingEngine(500,20);
 flockEngine.setRandomBoidsInBox(width/32);
 flockEngine.setParameters(0.05,0.1,0.5);
}
void mouseDragged(){
 rotX += (mouseX-pmouseX)*0.01;
 rotY -= (mouseY-pmouseY)*0.01;
}
void draw(){
 background(0);
 translate(width/2,height/2,0);
 rotateX(rotY);
 rotateY(rotX);
 graphEngine.plotBox();
 graphEngine.plotFlock(flockEngine.boids);
 flockEngine.updateFlock(0.5);
 flockEngine.boundaryControl(1,graphEngine.boxSize);
}

