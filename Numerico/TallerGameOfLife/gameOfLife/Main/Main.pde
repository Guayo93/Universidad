// GUI
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

// GAME
boolean stopped;
boolean twoD;
Game g;
Plotter p;
int frame;

void setup() 
{
  // GUI STUFF
  size(800, 675);
  controlsLabel = new GLabel(this, 0, 600, 100, 25, "Controls");
  start = new GButton(this, 0, 625, 100, 25, "Start");
  stop = new GButton(this, 0, 650, 100, 25, "Stop");
  step = new GButton(this, 100, 625, 100, 25, "Step");
  reset = new GButton(this, 100, 650, 100, 25, "Reset");
  
  dimLabel = new GLabel(this, 200, 600, 100, 25, "Dimensions");
  twoDim = new GButton(this, 200, 625, 50, 50, "2D");
  threeDim = new GButton(this, 250, 625, 50, 50, "3D");
  
  fpsLabel = new GLabel(this, 300, 600, 150, 25, "Frames per Second");
  fps = new GCustomSlider(this, 300, 625, 150, 50);
  fps.setShowValue(true);
  fps.setShowLimits(true);
  fps.setLimits(30, 0, 60);
  fps.setNbrTicks(7);
  fps.setShowTicks(true);
  fps.setEasing(6.0);
  fps.setNumberFormat(G4P.INTEGER, 0);
  fps.setOpaque(true);
  
  peopleHorLabel = new GLabel(this, 450, 600, 175, 25, "People Horizontal");
  peopleHor = new GCustomSlider(this, 450, 625, 175, 50);
  peopleHor.setShowValue(true);
  peopleHor.setShowLimits(true);
  peopleHor.setLimits(40, 0, 80);
  peopleHor.setNbrTicks(9);
  peopleHor.setShowTicks(true);
  peopleHor.setEasing(6.0);
  peopleHor.setNumberFormat(G4P.INTEGER, 0);
  peopleHor.setOpaque(true);
  peopleVertLabel = new GLabel(this, 625, 600, 175, 25, "People Vertical");
  peopleVert = new GCustomSlider(this, 625, 625, 175, 50);
  peopleVert.setShowValue(true);
  peopleVert.setShowLimits(true);
  peopleVert.setLimits(30, 0, 60);
  peopleVert.setNbrTicks(7);
  peopleVert.setShowTicks(true);
  peopleVert.setEasing(6.0);
  peopleVert.setNumberFormat(G4P.INTEGER, 0);
  peopleVert.setOpaque(true);
  
  // GAME STUFF
  stopped = false;
  twoD = true;
  frame = 0;
  g = new Game(peopleHor.getValueI(), peopleVert.getValueI(), 3);
  p = new Plotter();
  try {
    int n = 3;
    for(int i = 0; i < peopleHor.getValueI(); i++)
    {
      if(n >= 6)
      {
        n = 3;
      }
      for(int j = 0; j < peopleVert.getValueI(); j++)
      {
       if(j % n == 0)
       {
        g.set(i, j, 1); 
       }
      }
      n++;
    }
  }
  catch(Exception e) { 
    e.printStackTrace();
  }
}

void draw() {
  frame++;
  if ( frame >= 15) {
    frame = 0;
    try {
      p.plot2dGame(g);   
      g.update();
    }
    catch( Exception e ) {
      e.printStackTrace();
    }
  }
}

public void handleButtonEvents(GButton button, GEvent event)
{
  if(button == start && event == GEvent.CLICKED)
  {
    if(stopped == true)
    {
      frameRate(fps.getValueI());
      loop();
    }
  }
  else if(button == stop && event == GEvent.CLICKED)
  {
    //Detener
    stopped = true;
    noLoop();
  }
  else if(button == step && event == GEvent.CLICKED)
  {
    //Paso
    if(stopped == true)
    {
      redraw();
    }
  }
  else if(button == reset && event == GEvent.CLICKED)
  {
    //Reset
    if(twoD == true)
    {
      g = new Game(peopleHor.getValueI(), peopleVert.getValueI(), 3);
      p = new Plotter();
      p = new Plotter();
      try {
        int n = 3;
        for(int i = 0; i < peopleHor.getValueI(); i++)
        {
          if(n >= 6)
          {
            n = 3;
          }
          for(int j = 0; j < peopleVert.getValueI(); j++)
          {
           if(j % n == 0)
           {
            g.set(i, j, 1); 
           }
          }
          n++;
        }
      }
      catch(Exception e) { 
        e.printStackTrace();
      }
    }
    else
    {
      println("Porfavor compre nuestra proxima version que incluye esta funcionalidad :D");
    }
  }
  else if(button == twoDim && event == GEvent.CLICKED)
  {
    //2D
    twoD = true;
  }
  else if(button == threeDim && event == GEvent.CLICKED)
  {
    //3D
    twoD = false;
  }
}