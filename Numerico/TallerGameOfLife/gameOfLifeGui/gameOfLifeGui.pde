import g4p_controls.*;

GLabel controlsLabel;
GButton start;
GButton stop;
GButton step;
GButton reset;

GLabel dimLabel; 
GButton twoDim;
GButton threeDim;

GLabel fpsLabel;
GCustomSlider fps;

GLabel peopleVertLabel;
GLabel peopleHorLabel;
GCustomSlider peopleVert;
GCustomSlider peopleHor;

void setup() {
  size(800, 75);
  
  controlsLabel = new GLabel(this, 0, 0, 100, 25, "Controls");
  start = new GButton(this, 0, 25, 100, 25, "Start");
  stop = new GButton(this, 0, 50, 100, 25, "Stop");
  step = new GButton(this, 100, 25, 100, 25, "Step");
  reset = new GButton(this, 100, 50, 100, 25, "Reset");
  
  dimLabel = new GLabel(this, 200, 0, 100, 25, "Dimensions");
  twoDim = new GButton(this, 200, 25, 50, 50, "2D");
  threeDim = new GButton(this, 250, 25, 50, 50, "3D");
  
  fpsLabel = new GLabel(this, 300, 0, 150, 25, "Frames per Second");
  fps = new GCustomSlider(this, 300, 25, 150, 50);
  fps.setShowValue(true);
  fps.setShowLimits(true);
  fps.setLimits(30, 0, 60);
  fps.setNbrTicks(7);
  fps.setShowTicks(true);
  fps.setEasing(6.0);
  fps.setNumberFormat(G4P.INTEGER, 0);
  fps.setOpaque(true);
  
  peopleHorLabel = new GLabel(this, 450, 0, 175, 25, "People Horizontal");
  peopleHor = new GCustomSlider(this, 450, 25, 175, 50);
  peopleHor.setShowValue(true);
  peopleHor.setShowLimits(true);
  peopleHor.setLimits(40, 0, 80);
  peopleHor.setNbrTicks(9);
  peopleHor.setShowTicks(true);
  peopleHor.setEasing(6.0);
  peopleHor.setNumberFormat(G4P.INTEGER, 0);
  peopleHor.setOpaque(true);
  peopleVertLabel = new GLabel(this, 625, 0, 175, 25, "People Vertical");
  peopleVert = new GCustomSlider(this, 625, 25, 175, 50);
  peopleVert.setShowValue(true);
  peopleVert.setShowLimits(true);
  peopleVert.setLimits(30, 0, 60);
  peopleVert.setNbrTicks(7);
  peopleVert.setShowTicks(true);
  peopleVert.setEasing(6.0);
  peopleVert.setNumberFormat(G4P.INTEGER, 0);
  peopleVert.setOpaque(true);
}

void draw() {
  background(200, 200, 220);
}

public void handleButtonEvents(GButton button, GEvent event)
{
  if(button == start && event == GEvent.CLICKED)
  {
    frameRate(fps.getValueI());
    loop();
    println("Start");
  }
  else if(button == stop && event == GEvent.CLICKED)
  {
    //Detener
    noLoop();
    println("Stop");
  }
  else if(button == step && event == GEvent.CLICKED)
  {
    //Paso
    redraw();
    println("Step");
  }
  else if(button == reset && event == GEvent.CLICKED)
  {
    //Reset
    background(0);
    println("Reset");
  }
  else if(button == twoDim && event == GEvent.CLICKED)
  {
    //2D
    println("2D");
  }
  else if(button == threeDim && event == GEvent.CLICKED)
  {
    //3D
    println("3D");
  }
}