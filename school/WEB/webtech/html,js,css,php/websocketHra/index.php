<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	 <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
	<script src="https://ajax.aspnetcdn.com/ajax/jquery/jquery-3.6.0.js"></script>
	<script type="text/javascript" src="phaser.min.js"></script>
	<link rel="stylesheet" type="text/css" href="index.css">
	<title></title>
</head>
<body>
	<style>
ul {
  list-style-type: none;
}

li {
  display: inline-block;
  width: 250px;
  height: 250px;
  background-color: #eba834;
  border: 1px solid #ccc;
  text-align: center;
  line-height: 100px;
  font-size: 24px;
  margin-right: 10px;
}
</style>

	<?php 
	session_start();
	 if ($_SESSION['loginVisited'] != true){
	 	  header("Location: login.php");
	 
	exit();
}
?>
<div class="container">
<H1 class= "display-1 text-center">HRA</H1>
  <div class="row justify-content-center">

    <div class="col-md-12">
      <ul id="client-list" class="list-unstyled d-flex justify-content-center">
              </ul>
    </div>
  </div>
</div>


	<div id="privileged-area" class = "text-center"></div>

	<div id="game-container"></div>
	

	<script type="text/javascript">
		var p1,p2,p3,p4;
		var p1hp,p2hp,p3hp,p4hp;
		var p1text, p2text, p3text, p4text;
		var ball;
		var movementX = 0, movementyY = 0;
		var privileged = false;
		var clients = [];
		var ws;
		var windowH , windowW;
		var example;
		var ballSpeed =400;
		var centerX;
		var centerY;
		var endGame = false;
		var hits = 0;
		var hitsText;
		var ballVelocity;
		$(".field").hide();
		$(document).ready(function () {
			var username = decodeURIComponent(window.location.search.substring(1).split('=')[1]);
			ws = new WebSocket("wss://site218.webte.fei.stuba.sk:9000");
			ws.onopen = function () { console.log("Connection established"); 
			ws.send(JSON.stringify({
				type: "username",
				username: username
			}));
		};
		ws.onerror = function (error) { console.log("Unknown WebSocket Error " + JSON.stringify(error)); };
		ws.onmessage = function (e) {  
			var data = JSON.parse(e.data);
			//console.log(data);
				if (data.type === "connected_clients") {
  var clients = data.clients;
  var clientList = $('#client-list');
  clientList.empty();
  clients.forEach(function (client) {
    var listItem = $('<li>').text(client.username);
    clientList.append(listItem);
  });
}

			if (data.type === "server_full") {
				
				window.location.replace('https://site218.webte.fei.stuba.sk/pokus/login.php?warning=full');
			}
			if (data.type === 'startGame') {
				
				startGame(data.clientsCount,data);
			}
			if (data.type === 'position') {
				if (data.cube == 1) {
					p1.y += data['direction'];
					const currentTop = p1.y;
					const currentLeft = p1.x;
					ws.send(JSON.stringify({
						type: "cubePosition",
						positionTop: currentTop,
						positionLeft: currentLeft
					}));
				}
				if (data.cube == 2) {
					p2.y += data['direction'];
					const currentTop = p2.y;
					const currentLeft = p2.x;
					ws.send(JSON.stringify({
						type: "cubePosition",
						positionTop: currentTop,
						positionLeft: currentLeft
					}));
				}
				if (data.cube == 3) {
					p3.x += data['direction'];
					const currentTop = p3.y;
					const currentLeft = p3.x;
					ws.send(JSON.stringify({
						type: "cubePosition",
						positionTop: currentTop,
						positionLeft: currentLeft
					}));
					
				}
				if (data.cube == 4) {
					p4.x += data['direction'];
					const currentTop = p4.y;
					const currentLeft = p4.x;
					ws.send(JSON.stringify({
						type: "cubePosition",
						positionTop: currentTop,
						positionLeft: currentLeft
					}));
					
				}
				
				
			}
			if (data.type === 'privileged') {
				privileged = true;
				var card = $('<div>').addClass('card text-center');
    var cardBody = $('<div>').addClass('card-body');
    var button = $('<button>').addClass('btn btn-warning').text('Click me');
    button.click(function() {
        ws.send(JSON.stringify({
            type: "startGameButtonClicked"
        }));
    });
    cardBody.append(button);
    card.append(cardBody);
    $('#privileged-area').append(card);}			
			if (data.type === 'sendingBallPosition') {
				if (privileged != true) {

					movementX = data['ballx'];
					movementyY = data['bally'];

				}
				

			}
			if (data.type === 'Hpstatus') {
				console.log("player "+ data.player);

			
				switch(data.player){
    
				case 1: 

						p1hp = data.hp;
						p1text.text = p1hp;
						console.log(p1hp);
					break;
				case 2:
						p2hp = data.hp;
							p2text.text = p2hp;
										console.log(p2hp);

					break;
				case 3:
						p3hp = data.hp;
							p3text.text = p3hp;
										console.log(p3hp);
					break;
				case 4:
        	p4hp = data.hp;
        		p4text.text = p4hp;
        					console.log(p4hp);
					break;

				}
				

			}

				if (data.type === 'END') {
					endGame = true;

				}

		};
		
		ws.onclose = function () { console.log("Connection closed - Either the host or the client has lost connection"); };
	});
</script>
<script type="text/javascript">

	
	
	function startGame(number , data) {


		class Example extends Phaser.Scene
		{
			preload ()
			{

		

				this.load.image('wall', 'sprites/wall.png');
				this.load.image('straightWall', 'sprites/straightWall.png');
				this.load.image('straightWallHorizontal', 'sprites/straightWallHorizontal.png');
				this.load.image('p1', 'sprites/p1.png');
				this.load.image('p2', 'sprites/p2.png');
				this.load.image('p3', 'sprites/p3.png');
				this.load.image('p4', 'sprites/p4.png');
				this.load.image('ball','sprites/ball.png')
			}
			create ()
			{
				if (data.type === 'privileged') {
					privileged = true;
				}
		
	

				window.addEventListener("keydown", (event) => {
					const key = event.key;
					let direction = 0;
					if (key === "ArrowLeft" || key === "ArrowDown") {
						direction = -1;
					} else if (key === "ArrowRight" || "ArrowUp") {
						direction = 1;
					}
					if (direction !== 0) {
						//console.log(direction);
						ws.send(JSON.stringify({ type: "move", direction: direction*5}));
					}
				})

				 windowH = this.game.config.height;
				 windowW = this.game.config.width;
				var H = windowH/6500;



				centerX = game.scale.width / 2;
				centerY = game.scale.height / 2;
				ball = this.physics.add.image(centerX, centerY, 'ball');
				ball.setBounce(1.01,1.01);

				ball.setCollideWorldBounds(true);
				ball.setScale(0.05);
				if (privileged === true) {
       
        const ballAngle = Phaser.Math.RND.angle();
        ball.body.setVelocity(ballSpeed * Math.cos(ballAngle), ballSpeed * Math.sin(ballAngle));
        ballVelocity = ball.body.velocity;

        ws.send(JSON.stringify({ type: "BallStartMove", positionTop: ball.x, positionLeft:ball.y}));
        ws.send(JSON.stringify({ type: "startGame" }));
        

      }



 /*const atari = this.physics.add.image(250, 200, 'straightWall')
            .setImmovable(true)
            .setScale(0.1);
        const sprite = this.physics.add.image(400, 300, 'ball')
            .setVelocity(100, 200)
            .setBounce(1, 1)
            .setCollideWorldBounds(true)
            .setGravityY(200)
            .setScale(0.1);*/


    
      this.physics.world.debugDraw = true;
      this.physics.world.debugBodyColor = 0x00ff00;
      var wall1 = this.physics.add.sprite(20, 20, 'straightWallHorizontal')
      .setImmovable(true);
      wall1.setScale(H,0.1);
      wall1.setOrigin(0,0);
      this.physics.add.collider(ball, wall1,colliderCounter);
      wall1.body.debug = true;

      var wall11 = this.physics.add.sprite(20, 20, 'straightWall')
      .setImmovable(true);
      wall11.setScale(0.1,H);
      wall11.setOrigin(0, 0);
      this.physics.add.collider(ball, wall11,colliderCounter);
      wall11.body.debug = true;
      var wall2 = this.physics.add.image(windowH -20, 20, 'straightWallHorizontal')
      .setImmovable(true);
      wall2.setScale(H,0.1);
      wall2.setOrigin(1, 0);
      this.physics.add.collider(ball, wall2,colliderCounter);
      var wall22 = this.physics.add.image(windowH -20, 20, 'straightWall')
      .setImmovable(true);
      wall22.setScale(0.1,H);
      wall22.setOrigin(1, 0);
      this.physics.add.collider(ball, wall22,colliderCounter);
      var wall3 = this.physics.add.sprite(20, windowH-20, 'straightWallHorizontal')
      .setImmovable(true);
      wall3.setScale(H,0.1);
      wall3.setOrigin(0,1);
      this.physics.add.collider(ball, wall3,colliderCounter);
      wall3.body.debug = true;
      var wall33 = this.physics.add.sprite(20, windowH-20, 'straightWall')
      .setImmovable(true);
      wall33.setScale(0.1,H);
      wall33.setOrigin(0, 1);
      this.physics.add.collider(ball, wall33,colliderCounter);
      wall33.body.debug = true;
      var wall4 = this.physics.add.sprite(windowW-20, windowH-20, 'straightWallHorizontal')
      .setImmovable(true);
      wall4.setScale(H,0.1);
      wall4.setOrigin(1,1);
      this.physics.add.collider(ball, wall4,colliderCounter);
      var wall44 = this.physics.add.sprite(windowW-20, windowH-20, 'straightWall')
      .setImmovable(true);
      wall44.setScale(0.1,H);
      wall44.setOrigin(1, 1);
      this.physics.add.collider(ball, wall44,colliderCounter);
      switch (number) {
      case 1:
      	var straightWall3 =  this.physics.add.image(windowW-20,20, 'straightWall');
      	straightWall3.setOrigin(1, 0);
      	straightWall3.setScale(0.1,0.5);
      	straightWall3.setImmovable(true);
      	this.physics.add.collider(ball, straightWall3,colliderCounter);
      case 2:
      	var straightWall2 =  this.physics.add.image(windowW-20,20, 'straightWallHorizontal');
      	straightWall2.setOrigin(1, 0);
      	straightWall2.setScale(0.5,0.1);
      	straightWall2.setImmovable(true);
      	this.physics.add.collider(ball, straightWall2,colliderCounter);
      case 3:
      	var straightWall1 =  this.physics.add.image(20,windowH-20, 'straightWallHorizontal');
      	straightWall1.setOrigin(0	, 1);
      	straightWall1.setScale(0.5,0.1);
      	straightWall1.setImmovable(true);
      	this.physics.add.collider(ball, straightWall1,colliderCounter);
      default:
      // default logic here (if number doesn't match any of the cases)
      	break;
      }
      switch (number) {
      case 4:
      	p4 = this.physics.add.sprite(windowW/2-80 ,windowW-40, 'p1')
      	.setImmovable(true);
      	p4.setOrigin(0,1)
      	p4.setScale(H-0.08);
      	this.physics.add.collider(ball, p4,colliderCounter);
      case 3:
      	p3 = this.physics.add.sprite(windowW/2-80 ,40, 'p2')
      	.setImmovable(true);
      	p3.setOrigin(0,0)
      	p3.setScale(H-0.08);
      	this.physics.add.collider(ball, p3,colliderCounter);
      case 2:
      	p2 = this.physics.add.sprite(windowW-80 ,windowW/2-80, 'p3')
      	.setImmovable(true);
      	p2.setOrigin(0,0)
      	p2.setScale(H-0.08);
      	this.physics.add.collider(ball, p2,colliderCounter);
      case 1:
      	p1 = this.physics.add.sprite(40 ,windowW/2-80, 'p4')
      	.setImmovable(true);
      	p1.setOrigin(0,0)
      	p1.setScale(H-0.08);
      	this.physics.add.collider(ball, p1,colliderCounter);
      	break;
      default:
      	break;
      }

   


        hitsText  = this.add.text(20, 20, 3).setFontFamily('Arial').setFontSize(40).setColor('#ff0000');
        hitsText.text = hits; 
      	p1text = this.add.text(p1.x, p1.y, 3).setFontFamily('Arial').setFontSize(32).setColor('#000000');
      	if (p2) {
      		p2text = this.add.text(p2.x, p2.y, 3).setFontFamily('Arial').setFontSize(32).setColor('#000000');
      	}
				if (p3) {
					p3text = this.add.text(p3.x, p3.y, 3).setFontFamily('Arial').setFontSize(32).setColor('#000000');
					
				}
				if (p4) {
						p4text = this.add.text(p4.x, p4.y, 3).setFontFamily('Arial').setFontSize(32).setColor('#000000');  

				}
			
    }
    update ()
    {
    	if (privileged === true) {
    		ws.send(JSON.stringify({ type: "BallStartMove", positionTop: ball.x, positionLeft:ball.y}));
    	//	console.log(ball.displayWidth);
    		if (ball.x <= 0+ball.displayWidth/2) {
    			console.log("left");
    			var one = 1;
    			ws.send(JSON.stringify({ type: "takehp", player: 1}));

      	ball.x = centerX;
      	ball.y = centerY;
      	const ballAngle = Phaser.Math.RND.angle();
        ball.body.setVelocity(ballSpeed * Math.cos(ballAngle), ballSpeed * Math.sin(ballAngle));
        ws.send(JSON.stringify({ type: "BallStartMove", positionTop: ball.x, positionLeft:ball.y}));
      

    		}
    		if (ball.x >= windowW-ball.displayWidth/2) {
    			console.log("right");
    			var two = 2;
    				ws.send(JSON.stringify({ type: "takehp", player: 2}));
    				ball.x = centerX;
      	ball.y = centerY;
      	const ballAngle = Phaser.Math.RND.angle();
        ball.body.setVelocity(ballSpeed * Math.cos(ballAngle), ballSpeed * Math.sin(ballAngle));
        ws.send(JSON.stringify({ type: "BallStartMove", positionTop: ball.x, positionLeft:ball.y}));

    		}
    		if (ball.y <= 0+ball.displayHeight/2) {
    			console.log("top");
    			var three = 3;
    				ws.send(JSON.stringify({ type: "takehp", player: 3}));
    				ball.x = centerX;
      	ball.y = centerY;
      	const ballAngle = Phaser.Math.RND.angle();
        ball.body.setVelocity(ballSpeed * Math.cos(ballAngle), ballSpeed * Math.sin(ballAngle));
        ws.send(JSON.stringify({ type: "BallStartMove", positionTop: ball.x, positionLeft:ball.y}));

    		}
    		if (ball.y >= windowH-ball.displayHeight/2) {
    			console.log("bottom");
    			var four = 4;
    				ws.send(JSON.stringify({ type: "takehp", player: 4}));
    				ball.x = centerX;
      	ball.y = centerY;
      	const ballAngle = Phaser.Math.RND.angle();
        ball.body.setVelocity(ballSpeed * Math.cos(ballAngle), ballSpeed * Math.sin(ballAngle));
        ws.send(JSON.stringify({ type: "BallStartMove", positionTop: ball.x, positionLeft:ball.y}));

   }

    	}else{
    		ball.x = movementX;
    		ball.y = movementyY;
    	}
   if (p4hp <= 0) { 
    		var straightWall1 =  this.physics.add.image(20,windowH-20, 'straightWallHorizontal');
      	straightWall1.setOrigin(0	, 1);
      	straightWall1.setScale(0.5,0.1);
      	straightWall1.setImmovable(true);
      	this.physics.add.collider(ball, straightWall1,colliderCounter);
      	p4.destroy();
      	p4text.destroy();
      	
      	p4hp++;

    	}
	if (p3hp <= 0) { 
    	var straightWall2 =  this.physics.add.image(windowW-20,20, 'straightWallHorizontal');
      	straightWall2.setOrigin(1, 0);
      	straightWall2.setScale(0.5,0.1);
      	straightWall2.setImmovable(true);
      	this.physics.add.collider(ball, straightWall2,colliderCounter);
      	p3.destroy();
      		p3text.destroy();
      
      	p3hp++;
      }
      	if (p2hp <= 0) { 
    	var straightWall3 =  this.physics.add.image(windowW-20,20, 'straightWall');
      	straightWall3.setOrigin(1, 0);
      	straightWall3.setScale(0.1,0.5);
      	straightWall3.setImmovable(true);
      	this.physics.add.collider(ball, straightWall3,colliderCounter);
      	p2.destroy();
      		p2text.destroy();
      	
      	p2hp++;
      }
      if (p1hp <= 0) { 
    	var straightWall4 =  this.physics.add.image(20,20, 'straightWall');
      	straightWall4.setOrigin(0, 0);
      	straightWall4.setScale(0.1,0.5);
      	straightWall4.setImmovable(true);
      	this.physics.add.collider(ball, straightWall4,colliderCounter);
      	p1.destroy();
      		p1text.destroy();
      	
      	p1hp++;
      }
    	if (p1) {
    	p1text.x = p1.x;
    	p1text.y = p1.y;

    	}
    	if (p2) {
    		p2text.x = p2.x;
    	p2text.y = p2.y;
    	}
    	if (p3) {

    	p3text.x = p3.x;
    	p3text.y = p3.y;
    	}
    if (p4) {
    	p4text.x = p4.x;
    	p4text.y = p4.y-30;
    }
    	if (endGame == true) {
    		this.scene.pause();
    		setTimeout(function() {
        
    }, 3000);
    		    	}

    }

 


  }
     function colliderCounter(){
hits++;
hitsText.text = hits;


}


  $(".container").hide();
  $("#privileged-area").hide();
  $("#connected-clients-h1").hide();
	
  const config = {
  	type: Phaser.AUTO,
  	backgroundColor: '#2d2d2d',
  	pixelArt: true,
  parent: 'game-container', // replace this with your desired ID
  scale: {
  	mode: Phaser.Scale.FIT,
  	autoCenter: Phaser.Scale.CENTER_BOTH,
  	width: Math.min(window.innerWidth, window.innerHeight),
  	height: Math.min(window.innerWidth, window.innerHeight),
  },
  physics: {
  default: 'arcade',
  	arcade: {
  		gravity: { y: 0 },
  		debug: true,
  		setBounds: true,
  		bounds: {
  			x: 0,
  			y: 0,
  			width: Math.min(window.innerWidth, window.innerHeight),
  			height: Math.min(window.innerWidth, window.innerHeight),
  		},
  	},
  },
  scene: Example,
  pauseOnBlur: false,
};

const game = new Phaser.Game(config);

}
</script>
<script type="text/javascript">
	
	
</script>
</body>
</html>
