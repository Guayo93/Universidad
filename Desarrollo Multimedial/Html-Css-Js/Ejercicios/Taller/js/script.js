function mouseController(event, height, width)
{
  var canvas = document.getElementById("canvas");
  var message = document.getElementById("message");
  var ctx = canvas.getContext("2d");
  ctx.save();

  ctx.fillStyle = "rgba(255, 255, 255, 1)";
  ctx.fillRect(0, 0, 1200, 600);

  var x = event.clientX;
  var y = event.clientY;

  ctx.fillStyle = "rgb(0, 0, 255)";
  ctx.fillRect(0, 0, 50, 50);

  ctx.fillStyle = "rgb(0, 255, 0)";
  ctx.fillRect(1150, 550, 50, 50);

  ctx.fillStyle = "rgb(0, 0, 0)";
  ctx.fillRect(x-15, y-15, width, height);

  ctx.restore();

  if(message.innerHTML != "" && (x-15) <= 50 && (y-15) <= 50)
  {
    message.innerHTML = "";
  }
}

function resetGame()
{
  document.getElementById('message').innerHTML = "Vuelve a la zona Azul!";
}
