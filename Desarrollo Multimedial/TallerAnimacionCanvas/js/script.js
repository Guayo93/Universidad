var canvas = document.getElementById('canvas');
var ctx = canvas.getContext('2d');

var ballRadius = 25;
var ballElasticity = 0.6;
var ballMass = 10;

var limXS = 62;
var limXI = 392;
var limYS = 25;
var limYI = 450;

// Inicia Clase Vector
function Vector(bx, by)
{
  this.x = bx;
  this.y = by;
}

Vector.prototype.punto = function(vectorV)
{
  return (this.x * vectorV.x) + (this.y * vectorV.y);
};

Vector.prototype.length = function()
{
  return Math.sqrt((this.x * this.x) + (this.y * this.y));
};

Vector.prototype.normalize = function()
{
  var norm = 1 / this.length();

  this.x *= norm;
  this.y *= norm;

  return this;
};

Vector.prototype.multiply = function(s)
{
  return new Vector(this.x * s, this.y *s);
};

Vector.prototype.tx = function(s)
{
  this.x += s.x;
  this.y += s.y;

  return this;
};

// Fin Vector

// Inicia Clase Circulo
function Circle(bx, by, velX, velY)
{
  this.position = new Vector(bx, by);
  this.velocity = new Vector(velX || 0, velY || 0);
  this.mass = ballMass;
  this.elasticity = ballElasticity;
  this.radius = ballRadius;
}

Circle.prototype.draw = function(ctx)
{
  ctx.beginPath();
  ctx.arc(this.position.x, this.position.y, this.radius, 0, 2 * Math.PI);
  ctx.closePath();
  ctx.fill();
  ctx.stroke();
};

Circle.prototype.update = function(gravity, dt, ppm)
{
  this.velocity.y += gravity * dt;
  this.position.x += this.velocity.x * dt * ppm;
  this.position.y += this.velocity.y * dt * ppm;
}

Circle.prototype.collide = function(obj)
{
  var dt, mT, v1, v2, cr, sm,
    dn = new Vector(this.position.x - obj.position.x, this.position.y - obj.position.y),
    sr = this.radius + obj.radius,
    dx = dn.length();

  if(dx > sr)
  {
    return;
  }

  sm = this.mass + obj.mass;
  dn.normalize();
  dt = new Vector(dn.y, -dn.x);

  mT = dn.multiply(this.radius + obj.radius - dx);
  this.position.tx(mT.multiply(obj.mass / sm));
  obj.position.tx(mT.multiply(-this.mass / sm));

  cr = Math.min(this.elasticity, obj.elasticity);

  v1 = dn.multiply(this.velocity.punto(dn)).length();
  v2 = dn.multiply(obj.velocity.punto(dn)).length();

  this.velocity = dt.multiply(this.velocity.punto(dt));
  this.velocity.tx(dn.multiply(((cr * obj.mass * (v2 - v1)) + (this.mass * v1) + (obj.mass * v2)) / sm));

  obj.velocity = dt.multiply(obj.velocity.punto(dt));
  obj.velocity.tx(dn.multiply(((cr * this.mass * (v1 - v2)) + (obj.mass * v2) + (this.mass * v1)) / sm));
};

// Fin Circulo

function FloorObject(floor)
{
  var py;

  this.velocity = new Vector(0, 0);
  this.mass = 9999999;
  this.radius = 1000000000;
  this.position = new Vector(0, py = this.radius + floor);

  this.update = function()
  {
    this.velocity.x = 0;
    this.velocity.y = 0;
    this.position.x = 0;
    this.position.y = py;
  };

  this.draw = function(ctx)
  {
    ctx.fillRect(0, limYI, 500, limYI);
  };
}

FloorObject.prototype = new Circle(1);

function WallObject(wall)
{
  var px;

  this.velocity = new Vector(0, 0);
  this.mass = 999999;
  this.radius = 10000000;
  this.position = new Vector(px = this.radius + wall, 0);

  this.update = function()
  {
    this.velocity.x = 0;
    this.velocity.y = 0;
    this.position.x = px;
    this.position.y = 0;
  };

  this.draw = function(ctx)
  {
    ctx.fillRect(wall, 0, wall + 10, 450);
  };
}

WallObject.prototype = new Circle(2);

var objects = [],
  fps = 60,
  ppm = 20,
  gravity = 9.8,
  t = new Date().getTime();

objects.push(new Circle(225, 50, 0, 20));
objects.push(new Circle(187, 100, 0, 20));
objects.push(new Circle(267, 100, 0, 20));
objects.push(new Circle(150, 150, 0, 20));
objects.push(new Circle(225, 150, 0, 20));
objects.push(new Circle(300, 150, 0, 20));
objects.push(new Circle(112, 200, 0, 20));
objects.push(new Circle(187, 200, 0, 20));
objects.push(new Circle(267, 200, 0, 20));
objects.push(new Circle(342, 200, 0, 20));
objects.push(new FloorObject(450));
//objects.push(new WallObject(0));
//objects.push(new WallObject(490));

ctx.fillStyle = 'rgb(255, 0, 0)';
ctx.strokeStyle = 'rgb(0, 0, 0)';

setInterval(function()
{
  ctx.clearRect(0, 0, 500, 500);

  var i, j,
  nt = new Date().getTime()
  dt = (nt - t) / 1000;

  for(i = 0; i < objects.length; i++)
  {
    objects[i].update(gravity, dt, ppm);

    for(j = i + 1; j < objects.length; j++)
    {
      objects[j].collide(objects[i]);
    }

    objects[i].draw(ctx);
  }

  t = nt;
}, 1000/fps);
