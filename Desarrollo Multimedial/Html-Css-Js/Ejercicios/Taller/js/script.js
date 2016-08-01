var canvas = document.getElementById('canvas');
var message = document.getElementById('message');
var score = document.getElementById('score');
var intentos = document.getElementById('intentos');
var menorP = document.getElementById('puntajeMenor');
var ctx = canvas.getContext('2d');
ctx.save();

var randomAzul = Math.floor((Math.random() * 350) + 1);
var randomVerde = Math.floor((Math.random() * 350) + 1);

var numScore = 0;
var numIntentos = 0;
var menorPuntaje = 9999999999;
var tryFlag = true;

var mouseX = 0;
var mouseY = 0;
var mouseWidth = 15;
var mouseHeight = 15;

var ballX = 70;
var ballY = 70;
var ballRadius = 25;
var ballDX = 4;
var ballDY = -4;

var bricksWidth = 200;
var bricksHeight = 25;

var brick01X = 300;
var brick01Y = 60;
var brick01DX = 5;

var brick02X = 400;
var brick02Y = 120;
var brick02DX = 4;

var brick03X = 300;
var brick03Y = 180;
var brick03DX = 3;

var brick04X = 400;
var brick04Y = 240;
var brick04DX = 2;

var brick05X = 300;
var brick05Y = 300;
var brick05DX = 1;

var sunsRadius = 40;
var rayWidth = 140;
var rayHeight = 10;
var rayAngle = 0;
var rayRotation = 5;

var sun01X = 750;
var sun01Y = 125;

var sun02X = 750;
var sun02Y = 250;

var ko = false;
var inicio = true;

canvas.addEventListener("mousemove", function(event){mouseHandler(event);});

canvas.addEventListener("mouseout", gameOver);

function draw()
{
	ctx.fillStyle = "rgba(255, 255, 255, 1)";
	ctx.fillRect(0, 0, 900, 400);

	ctx.fillStyle = "rgb(0, 0, 255)";
	ctx.fillRect(0, randomAzul, 50, 50);

	ctx.fillStyle = "rgb(0, 255, 0)";
	ctx.fillRect(850, randomVerde, 50, 50);

	ctx.save();
	ctx.beginPath();
	ctx.moveTo(300, 0);
	ctx.lineTo(300, 375);
	ctx.strokeStyle="red";
	ctx.lineWidth="3";
	ctx.stroke();
	ctx.closePath();

	ctx.beginPath();
	ctx.moveTo(600, 400);
	ctx.lineTo(600, 25);
	ctx.stroke();
	ctx.closePath();
	ctx.restore();

	drawBall();
	drawBricks();
	drawSuns();
	collisionHandler();

	intentos.innerHTML = "Intentos: " + numIntentos;
	score.innerHTML = "Puntaje: " + numScore;
	menorP.innerHTML = "Mejor Puntaje: " + menorPuntaje;
}

function mouseHandler(event)
{
	mouseX = event.clientX;
	mouseY = event.clientY;
}

function drawBall()
{
	ctx.beginPath();
	ctx.arc(ballX, ballY, ballRadius, 0, Math.PI*2);
	ctx.fillStyle = "red";
	ctx.fill();
	ctx.closePath();

	ballHandler();
}

function ballHandler()
{
	if(ballX + ballDX > (canvas.width/3)-ballRadius || ballX + ballDX < ballRadius)
	{
		ballDX = -ballDX;
	}
	if(ballY + ballDY > canvas.height-ballRadius || ballY + ballDY < ballRadius) {
		ballDY = -ballDY;
	}

	ballX += ballDX;
	ballY += ballDY;
}

function drawBricks()
{
	ctx.beginPath();
	ctx.fillStyle = "rgb(255, 0, 0)";
	ctx.fillRect(brick01X, brick01Y, bricksWidth, bricksHeight);
	ctx.closePath();

	ctx.beginPath();
	ctx.fillStyle = "rgb(255, 0, 0)";
	ctx.fillRect(brick02X, brick02Y, bricksWidth, bricksHeight);
	ctx.closePath();

	ctx.beginPath();
	ctx.fillStyle = "rgb(255, 0, 0)";
	ctx.fillRect(brick03X, brick03Y, bricksWidth, bricksHeight);
	ctx.closePath();

	ctx.beginPath();
	ctx.fillStyle = "rgb(255, 0, 0)";
	ctx.fillRect(brick04X, brick04Y, bricksWidth, bricksHeight);
	ctx.closePath();

	ctx.beginPath();
	ctx.fillStyle = "rgb(255, 0, 0)";
	ctx.fillRect(brick05X, brick05Y, bricksWidth, bricksHeight);
	ctx.closePath();

	bricksHandler();
}

function bricksHandler()
{
	if(brick01X + bricksWidth > ((canvas.width * 2)/3) || brick01X < canvas.width/3)
	{
		brick01DX = -brick01DX;
	}

	if(brick02X + bricksWidth > ((canvas.width * 2)/3) || brick02X < canvas.width/3)
	{
		brick02DX = -brick02DX;
	}

	if(brick03X + bricksWidth > ((canvas.width * 2)/3) || brick03X < canvas.width/3)
	{
		brick03DX = -brick03DX;
	}

	if(brick04X + bricksWidth > ((canvas.width * 2)/3) || brick04X < canvas.width/3)
	{
		brick04DX = -brick04DX;
	}

	if(brick05X + bricksWidth > ((canvas.width * 2)/3) || brick05X < canvas.width/3)
	{
		brick05DX = -brick05DX;
	}

	brick01X += brick01DX;
	brick02X += brick02DX;
	brick03X += brick03DX;
	brick04X += brick04DX;
	brick05X += brick05DX;
}

function drawSuns()
{
	ctx.beginPath();
	ctx.arc(sun01X, sun01Y, sunsRadius, 0, Math.PI*2);
	ctx.fillStyle = "red";
	ctx.fill();
	ctx.closePath();

	ctx.beginPath();
	ctx.arc(sun02X, sun02Y, sunsRadius, 0, Math.PI*2);
	ctx.fillStyle = "red";
	ctx.fill();
	ctx.closePath();

	rayHandler();
}

function rayHandler()
{
	ctx.save();
	ctx.beginPath();
	ctx.translate(sun01X-5, sun01Y-5);
	ctx.rotate(Math.PI / 180 * rayAngle);
	ctx.fillStyle = "rgb(255, 0, 0)";
	ctx.fillRect(0, 0, rayWidth, rayHeight);
	ctx.closePath();
	ctx.restore();

	ctx.save();
	ctx.beginPath();
	ctx.translate(sun02X-5, sun02Y-5);
	ctx.rotate(Math.PI / 180 * -rayAngle);
	ctx.fillStyle = "rgb(255, 0, 0)";
	ctx.fillRect(0, 0, rayWidth, rayHeight);
	ctx.closePath();
	ctx.restore();

	rayAngle += rayRotation;
}

function collisionHandler()
{
	if(ctx.getImageData(mouseX, mouseY, 1, 1).data[0] === 255 && ctx.getImageData(mouseX, mouseY, 1, 1).data[1] === 0 && ctx.getImageData(mouseX, mouseY, 1, 1).data[2] === 0)
	{
		gameOver();

		if(tryFlag === true)
		{
			numIntentos++;
			tryFlag = false;
		}
	}

	if(ctx.getImageData(mouseX, mouseY, 1, 1).data[0] === 0 && ctx.getImageData(mouseX, mouseY, 1, 1).data[1] === 0 && ctx.getImageData(mouseX, mouseY, 1, 1).data[2] === 255)
	{
		message.innerHTML = "";
		inicio = true;
		tryFlag = true;
		numScore = 0;
	}

	if(ctx.getImageData(mouseX, mouseY, 1, 1).data[0] === 0 && ctx.getImageData(mouseX, mouseY, 1, 1).data[1] === 255 && ctx.getImageData(mouseX, mouseY, 1, 1).data[2] === 0 && inicio === true)
	{
		alert("Has ganado!!");
		inicio = false;

		if(menorPuntaje > numScore)
		{
			menorPuntaje = numScore;
		}
	}

	if(ctx.getImageData(mouseX, mouseY, 1, 1).data[0] === 255 && ctx.getImageData(mouseX, mouseY, 1, 1).data[1] === 255 && ctx.getImageData(mouseX, mouseY, 1, 1).data[2] === 255 && inicio === true)
	{
		numScore++;
	}
}

function gameOver()
{
	message.innerHTML = "Game Over! -> Vuelve a la zona Azul";
	inicio = false;
}

setInterval(draw, 10);
