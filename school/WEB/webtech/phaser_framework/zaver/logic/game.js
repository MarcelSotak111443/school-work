// Init of scene objects
var savedLevel = 0
var gameReseting = false;
var gamewasrestarted = false;
var questText = null;
var firtPlay = true;
var currentLevel = 1;
var bar  = null;
var angle = 0;
var level = 1;
var wasPaused = false;
var gameover = false;
var scene = null;
var earth = null;
var earthHitZone = null;
var cursors = null;
var ship = null;
var cannonGroup = null;
var npcGroup = null;
var laserGroup = [];
var r1 = null;
var middlePoint = null;
var hitZoneImage = null;
var fitbar = null;
var allPositionArray = null;
var positionArray = null;
var buildZone2 = null;
var oldX = 0;
var oldY = 0;
var earthImage = null;
var buildZone = null;
var powerPlantGroup = null;
var shieldGroup = null;
var groups = null;

//SOUND
var click = null;
var win= null;
var lost = null;
var gameSound = null;
var destroy = null;
var laserShoot = null;

//PAUSE MENU
var exit = null;
var continueGame = null;
var restart = null;

// User HP & Money bar vars
var shield = 0;
var earthHP = 0;
var money = 0;
var time = 0;
var npcDestroyed = 0;
var cannonPrice = 150;
var shieldPrice = 100;
var powerPlantPrice = 50;
var cannonPriceLabel = 0;
var shieldPriceLabel = 0;
var powerPlantPriceLabel = 0; 

// Interval of Shoot & Generate NPCs
window.npcDelay = 2200;
window.shootDelay = 2200;
window.shdRegenDelay = 1000;
window.npcInterval = null;
window.shootInterval = null;
window.shdRegenInterval = null;
var lastClicked = 0;

var oldOrientY = 0;
function handleOrientation(event) {
    if (window.isPaused || !isMobile) {return;}
    if (h < 500) {
        if (Math.floor(event.beta) < -5) {
            rotateEarth("right",true);
        } else if (Math.floor(event.beta) > 5) {
            rotateEarth("left",true);
        }
    } else {
        if (Math.floor(event.gamma) < -10) {
            rotateEarth("right",true);
        } else if (Math.floor(event.gamma) > 10) {
            rotateEarth("left",true);
        }
    }
}

var Game = new Phaser.Class({

    Extends: Phaser.Scene,
    initialize: function() {
        Phaser.Scene.call(this, { "key": "game" });
    },
    init: function (data)
    {
        varLevel = data.level;
       
    },
    preload: function() {

        this.load.image('pause', 'homemade/pauseButton.jpg');
        this.load.image('powerplant', 'pictures/powerplant.png');
        this.load.image('earth', 'pictures/earth.png');
        this.load.image('cannon', 'pictures/cannon.png');
        this.load.image('npc', 'pictures/npc.png');
        this.load.image('laser', 'pictures/laser.png');
        this.load.image('laser2', 'pictures/laserball.png');
        this.load.image('shield', 'pictures/shield.png');
        this.load.html("gun", "pictures/cannon.png");
        this.load.image("bullet", "pictures/laser.png");
        this.load.audio("laserShoot","sound/lasershot.mp3");
        this.load.audio("destroy","sound/destroying.mp3");
        this.load.audio("lost","sound/lostgame.wav");
        this.load.audio("shoot","sound/shot.wav");
        this.load.audio("win","sound/win.wav");
        this.load.image('continue', 'homemade/continueButton.jpg');
        this.load.image('restart', 'homemade/restartButton.jpg');
        this.load.image('exit', 'homemade/exitButton.jpg');
    },
    create: function() {

        if (this.aGrid == undefined) {
            this.aGrid = new AlignGrid({scene:this,rows:12,cols:11});
            //this.aGrid.showNumbers();
        }

        window.isPaused = false;
        
        console.log("var LEVEL " + varLevel)
        console.log("curent LEVEL "+ currentLevel)
        console.log("saved level" + savedLevel)
        console.log("level" + level)

        if(varLevel >= savedLevel){
           
            localStorage.setItem('level', varLevel);
            savedLevel = varLevel
           
            level = savedLevel
        }

        console.log("var LEVEL " + varLevel)
        console.log("curent LEVEL "+ currentLevel)
        console.log("saved level" + savedLevel)
        console.log("level" + level)
       
        click = this.sound.add('shoot');
        win = this.sound.add('win');
        lost = this.sound.add('lost');
        destroy = this.sound.add('destroy');
        laserShoot = this.sound.add('laserShoot');

        scene = this;
        groups = null;
    
        earthHP = 100;
        shield = 0;
        money = 200;

        time = 0;
        angle = 0;
        npcDestroyed = 0;
        
        gameover = false;

        bar = this.add.graphics();

        questText = this.add.text(0,0,'ahoj',{  fontFamily: 'CustomFont', color: '#baaa47', fontSize: '20px'})
        questText.setScale(w/700);

        if (window.innerHeight <= 400) {
            questText.setScale(w/450);
            this.aGrid.placeAtIndex(99,questText);
            questText.y += w/20;
            questText.x -= w/12;
        } else if (window.innerHeight < 500) {
            questText.setScale(w/450);
            this.aGrid.placeAtIndex(99,questText);
            questText.y += w/20;
            questText.x -= w/10;
        } else {
            this.aGrid.placeAtIndex(121,questText);
            questText.y -= w/15;
            questText.x -= w/45;
        }
        questText.setStroke('#333333', 8);
        questText.setShadow(2, 2, "#333333", 5, true, true);

        bar.fillStyle(0xfff000,1);
        bar.fillRect(0,0,w/4,w/25);
        this.aGrid.placeAtIndex(128,bar);
        bar.y -= w/45

        fitbar = this.add.graphics();

        fitbar.fillStyle(0xff0000,1)
        fitbar.fillRect(0,0,0,w/25);
        this.aGrid.placeAtIndex(128,fitbar);
        fitbar.y -= w/45

        //GAME TIMER 
        timedEvent = this.time.addEvent({ delay: 1000, callback: updateTime, callbackScope: this, loop: true });

        var flyoutEl = document.querySelector("canvas")
        flyoutEl.setAttribute("id", "canv");  

        addEventListener('blur', (event) => { 
            if(gameover == false) {
                console.log("Opustil herne okno");
                pause(this);  
            }
        });
   
        earth = this.physics.add.staticGroup();
        earthImage = this.physics.add.image(0,0, 'earth').setScale(w/800);
        this.aGrid.placeAtIndex(71,earthImage);
        earth.add(earthImage);

        buildZone = this.add.rectangle(earthImage.getBounds().x + 50,earthImage.getBounds().y,
        earthImage.getBounds().width / 1.8,earthImage.getBounds().height/1.15,null);
        this.aGrid.placeAtIndex(71,buildZone);
        this.physics.add.existing(buildZone);
        buildZone.setVisible(false);

        buildZone2 = this.add.rectangle(earthImage.getBounds().x + 50,earthImage.getBounds().y,
                     earthImage.getBounds().width - 50,earthImage.getBounds().height/2,null);
        this.aGrid.placeAtIndex(71,buildZone2);
        this.physics.add.existing(buildZone2);
        buildZone2.setVisible(false);
    
        hitZoneImage = this.physics.add.image(0,0, 'earth').setScale(w/1200);
        this.aGrid.placeAtIndex(71,hitZoneImage);
        hitZoneImage.setVisible(false);

        cannonGroup = this.physics.add.staticGroup();
        npcGroup = this.physics.add.staticGroup();
        shieldGroup = this.physics.add.staticGroup();
        powerPlantGroup = this.physics.add.staticGroup();
        this.npcBullets = this.add.group();
        this.playerBullets = this.add.group();

        middlePoint = new myPoint(earthImage.getCenter().x,earthImage.getCenter().y);

        text = this.add.text(10, 10, '', {   fontFamily: 'CustomFont', color: '#baaa47', fontSize: '25px'});
        text.setScale(w/700);

        updateText();

        if(firtPlay){
            if(savedLevel == 0)
            level = 1;
            level = savedLevel;
            loadQuest();
            chooseAnotherQuest()
            firtPlay = false;
        }
    
        if(gameReseting == true){
            level = varLevel;
            gameReseting = false;
        }

        if(gamewasrestarted == true){
            chooseAnotherQuest();
            console.log("stvrty");
            gamewasrestarted = false;
        }

        wasPaused = false;     

        // Delay Between Shots
        this.input.on('pointerdown', function() {
            var timeNow = (new Date()).getTime();
            if (timeNow > (lastClicked + 500)) {
                playerShoot();
                lastClicked = timeNow;
            }
        });

        // Build Game Bar & NPC Positions
        buildGameBar();
        buildPositions();

        // Mobile Responsive
        if (h < 500 || w < 500) {
            scaleToMobile();
        }

        // Drag & Drop
        this.input.on('pointerdown',this.startDrag,this);

        // Intervals & Keys
        window.npcInterval = window.setInterval(generateNPC, npcDelay - (Math.pow(level, 1/2)) * 100 + (time /2 )) ;
        window.shootInterval = window.setInterval(shootLaser, shootDelay - (Math.pow(level, 1/2)) * 100 + (time /2 ));
        window.shdRegenInterval = window.setInterval(regenShield, shdRegenDelay);
        cursors = this.input.keyboard.createCursorKeys();

        cannonPrice = 145 + 5*level;
        if(cannonPrice >= 200){
            cannonPrice = 200;
        }

        shieldPrice= 95 + 5*level;;
        powerPlantPrice= 45 + 5*level;;
        cannonPriceLabel.setText(cannonPrice);
        shieldPriceLabel.setText(shieldPrice);
        powerPlantPriceLabel.setText(powerPlantPrice); 
   
        window.addEventListener("deviceorientation", handleOrientation);
    },
    startDrag: function(pointer,targets) {
        if(targets != 0)
        if(targets[0].type == "Sprite"){
           
        return}

        if (targets.length != 0) {
            this.input.off('pointerdown',this.startDrag,this);
            this.dragObject = targets[0];
            if (this.dragObject.name != "Pause") { 
                oldX = this.dragObject.x;
                oldY = this.dragObject.y;
                this.input.on('pointermove',this.doDrag,this);
                this.input.on('pointerup',this.stopDrag,this);
                this.dragObject.disableInteractive();
            }
        }
    },
    doDrag: function(pointer) {
        this.dragObject.x = pointer.x;
        this.dragObject.y = pointer.y;
    },
    stopDrag: function(pointer) {
        this.input.on('pointerdown',this.startDrag,this);
        this.input.off('pointermove',this.doDrag,this);
        this.input.off('pointerup',this.stopDrag,this);
        var enoughMoney = false;

        var isOverlapping = scene.physics.overlap(this.dragObject,buildZone,null,null,this);
        if (isOverlapping) {
           
            console.log("Overlap!");
            enoughMoney = itemBuy(this.dragObject,buildZone);
        }
        var isOverlapping2 = scene.physics.overlap(this.dragObject,buildZone2,null,null,this);
        if (!isOverlapping && isOverlapping2) {
          
            console.log("Overlap!");
            enoughMoney = itemBuy(this.dragObject,buildZone2);
        }
        if ((!isOverlapping && !isOverlapping2) || !enoughMoney) {
            this.dragObject.x = oldX;
            this.dragObject.y = oldY;
            this.dragObject.setInteractive();
            if (!enoughMoney) {console.log("Insufficient Funds!");}
        }
    },
    update: function() {
        if (cursors.left.isDown) {
            rotateEarth("left");
        } else if (cursors.right.isDown) {
            rotateEarth("right");
        }
    }
});

function rotateEarth(side,isMobile) {
    if (groups == null) {
        groups = [cannonGroup,shieldGroup,powerPlantGroup];
    }
    var rotation = 0.01;
    if (isMobile)
        rotation *= 1.5;

    if (side == "left") {
        for (var obj of groups) {
            obj.rotateAround(middlePoint,rotation);
            obj.rotate(rotation);
            angle += rotation*100;
        }
        earth.rotate(rotation);
    } else if (side == "right") {
        for (var obj of groups) {
            obj.rotateAround(middlePoint,-rotation);
            obj.rotate(-rotation);
            angle += rotation*100;
        }
        earth.rotate(-rotation);
    }
}

function itemBuy(object,zone) {

    switch (object.name) {
        case 'Shield':
            console.log('Buy shield');
            if (money - shieldPrice < 0) {return false};
            
            if (shieldGroup.getLength() == 0) {    
                money -= shieldPrice;
                shieldGroup.add(object);
                shield = 100;
            } else {object.destroy();}

            var shieldItem = scene.physics.add.image(0,0,'shield').setScale(w/15000).setInteractive();
            shieldItem.name = "Shield";
            scene.aGrid.placeAtIndex(4,shieldItem);
            if (h < 500) {
                Align.scaleToGameW(shieldItem,0.045);
                shieldItem.y += 10;
            }
            shieldItem.x += w/20;   
            break;
        case 'Cannon':
            console.log('Buy cannon');
            if (money - cannonPrice < 0) {return false};
            money -= cannonPrice;
            cannonGroup.add(object);
            var cannon = scene.physics.add.image(0,0,'cannon').setScale(w/7000).setInteractive();
            cannon.name = "Cannon";
            scene.aGrid.placeAtIndex(6,cannon);
            if (h < 500) {
                Align.scaleToGameW(cannon,0.06);
                cannon.y += 10;  
            }
            cannon.x += w/20; 
            break;
        case 'Powerplant':
            console.log('Buy powerplant');
            if (money - powerPlantPrice < 0) {return false};
            money -= powerPlantPrice;
            powerPlantGroup.add(object);
            var powerPlant = scene.physics.add.image(0,0,'powerplant').setScale(w/8000).setInteractive();
            powerPlant.name = "Powerplant";
            scene.aGrid.placeAtIndex(2,powerPlant);
            if (h < 500) {
                Align.scaleToGameW(powerPlant,0.04);
                powerPlant.y += 10;
            }
            powerPlant.x += w/20;    
            break;
        default:
            console.log('Unidentified shop item!');
    }
    updateText();
    return true;
}

function buildGameBar() {
    var pauseSprite = scene.add.sprite(0, 0,'pause').setInteractive();
    pauseSprite.setScale(w/1200)
    pauseSprite.name = "Pause";
    scene.aGrid.placeAtIndex(10,pauseSprite);

    pauseSprite.on('pointerdown', function () {
        if(gameover == false)
        pause(this);
    },scene);



    var shopItem = scene.physics.add.image(0,0,'shield').setScale(w/15000).setInteractive();
    shopItem.name = "Shield";
    shieldPriceLabel = scene.add.text(0, 0, '100', {  fontFamily: 'CustomFont', color: '#baaa47', fontSize: '25px'});
    shieldPriceLabel.setScale(w/700);
    scene.aGrid.placeAtIndex(4,shopItem);
    scene.aGrid.placeAtIndex(5,shieldPriceLabel);
    shopItem.x += w/20;

    var shopItem2 = scene.physics.add.image(0,0,'cannon').setScale(w/7000).setInteractive();
    shopItem2.name = "Cannon";
    cannonPriceLabel = scene.add.text(0, 0, '150', {  fontFamily: 'CustomFont', color: '#baaa47', fontSize: '25px'});
    cannonPriceLabel.setScale(w/700);
    scene.aGrid.placeAtIndex(6,shopItem2);
    scene.aGrid.placeAtIndex(7,cannonPriceLabel);
    shopItem2.x += w/20;

    var shopItem3 = scene.physics.add.image(0,0,'powerplant').setScale(w/8000).setInteractive();
    shopItem3.name = "Powerplant";
    powerPlantPriceLabel = scene.add.text(0, 0, '50',{  fontFamily: 'CustomFont', color: '#baaa47', fontSize: '25px'});
    powerPlantPriceLabel.setScale(w/700);
    scene.aGrid.placeAtIndex(2,shopItem3);
    scene.aGrid.placeAtIndex(3,powerPlantPriceLabel);
    shopItem3.x += w/20;

     if (h < 500) {
        Align.scaleToGameW(shieldPriceLabel,0.04);
        Align.scaleToGameW(cannonPriceLabel,0.04);
        Align.scaleToGameW(powerPlantPriceLabel,0.03);
        Align.scaleToGameW(shopItem,0.045);
        Align.scaleToGameW(shopItem2,0.06);
        Align.scaleToGameW(shopItem3,0.04);
        shopItem.y += 10;
        shopItem2.y += 10;
        shopItem3.y += 10;
    }
}

class myPoint {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

function hitNPC(bullet,npc) {
    console.log("Zostrel!");
    bullet.destroy();
    destroy.play();
    npc.destroy();
    money += 10;
    npcDestroyed += 1;
    updateText();
}

function buildPositions() {
    positionArray = [112,113,114,115,116,117,118,13,14,15,16,17,18,19,24,25,26,27,28,29,30];
    for (var i = 33; i<=110; i+=11) {positionArray.push(i);}
    for (var i = 34; i<=111; i+=11) {positionArray.push(i);}
    for (var i = 20; i<=119; i+=11) {positionArray.push(i);}
    for (var i = 21; i<=120; i+=11) {positionArray.push(i);}

    if (h < 500) {
        positionArray = [112,113,114,115,116,117,118,24,25,26,27,28,29,30];
        for (var i = 55; i<=110; i+=11) {positionArray.push(i);}
        for (var i = 56; i<=111; i+=11) {positionArray.push(i);}
        for (var i = 35; i<=101; i+=11) {positionArray.push(i);}
        for (var i = 36; i<=102; i+=11) {positionArray.push(i);}
        for (var i = 40; i<=106; i+=11) {positionArray.push(i);}
        for (var i = 41; i<=107; i+=11) {positionArray.push(i);}
        for (var i = 20; i<=119; i+=11) {positionArray.push(i);}
        for (var i = 21; i<=120; i+=11) {positionArray.push(i);}
    }
    allPositionArray = positionArray.slice();
}

function generateNPC() {
    if (positionArray.length == 0) {
        positionArray = allPositionArray.slice();
        for (var npc of npcGroup.getChildren()) {
            if (npc.position != undefined) {
                let indx = positionArray.indexOf(npc.position);
                positionArray.splice(indx,1);
            }
        }
        return;
    }
    var npc = scene.physics.add.image(0, 0, 'npc').setScale(w/2500);
    var rIndx = Math.floor(Math.random() * positionArray.length);
    npc.position = positionArray[rIndx];
    scene.aGrid.placeAtIndex(positionArray[rIndx],npc);
    positionArray.splice(rIndx,1);
    npcGroup.add(npc);

    for (var bullet of scene.playerBullets.getChildren()) {
        scene.physics.add.overlap(npc,bullet,hitNPC,null,this);
    }
}

function regenShield() {
    if (shieldGroup == null || shieldGroup == undefined) {return;}
    if (powerPlantGroup == null || powerPlantGroup == undefined) {return;}
    var shdCount = shieldGroup.getLength();
    var powerPlantCount = powerPlantGroup.getLength();
    if (shdCount && powerPlantCount) {
        console.log("Inkrementujem!");
        shield += powerPlantCount * 1;
        if (shield > 100) {shield = 100;}
        updateText();
    }
}

function updateTime(){
    time += 1;
    //console.log((Math.pow(level, 1/2)) * 60 +(time /2 ))
    updateText();
}

function updateText() {

    text.setText(' ')
    text.setText([
        'HP: ' + earthHP,
        'SHIELD: ' +  shield,
        'MONEY: ' + money,
        'KILLS: ' + npcDestroyed,
        'TIME: ' + time
    ]);
    updateQuestText(scene);
}

function shootLaser() {
    let speed = 300;
    let dX = middlePoint.x;
    let dY = middlePoint.y;

    for (var npc of npcGroup.getChildren()) {
        // Create bullet
        laserShoot.play();
        let sX = npc.x;
        let sY = npc.y;

        var sPoint = new myPoint(sX,sY);
        var dPoint = new myPoint(dX,dY);

        let npcBullet = scene.add.image(sX, sY, 'laser').setScale(w/1000);
        npcBullet.angle = Phaser.Math.Angle.BetweenPoints(sPoint, dPoint) * (180/Math.PI);
        scene.physics.add.existing(npcBullet);
        
        // Vector where to shoot bullet
        let vector = new Phaser.Math.Vector2( dX - sX, dY - sY);

        // Set speed of bullet 
        vector.setLength(speed);
        
        // Shoot in a straightline
        npcBullet.body.setAllowGravity(false);
        
        // Add bullet to group
        scene.npcBullets.add(npcBullet);
        npcBullet.body.setVelocity(vector.x, vector.y);
        scene.physics.add.overlap(npcBullet,hitZoneImage,hitEarth,null,this);
    }
}

function hitEarth(npcBullet,earth) {
    //console.log("Earth was HIT!");
    npcBullet.destroy();
    if (shield > 0) {shield -= 1;}
    else if (earthHP > 0) {earthHP -= 1;}
    else {
        lost.play();
        gameover = true;
        scene.paused = true;
        scene.scene.pause();
        clearInterval(window.npcInterval);
        clearInterval(window.shootInterval);
        clearInterval(window.shdRegenInterval);
        scene.scene.launch('gameovermenu');
    }
    updateText();
}

function playerShoot() {
    click.play();
    let speed = 500;

    for (var cannon of cannonGroup.getChildren()) {
        // Create bullet
        let sX = cannon.x;
        let sY = cannon.y;

        let dX = middlePoint.x + 20;
        let dY = middlePoint.y;

        var sPoint = new myPoint(sX,sY);
        var dPoint = new myPoint(dX,dY);

        let bullet = scene.add.image(sX, sY, 'laser2').setScale(w/1000);
        laserGroup.push(bullet);
        bullet.angle = Phaser.Math.Angle.BetweenPoints(sPoint, dPoint) * (180/Math.PI);
        scene.physics.add.existing(bullet);
        
        // Vector where to shoot bullet
        let vector = new Phaser.Math.Vector2( sX + 100, sY);

        // Set speed of bullet 
        vector.setLength(speed);
        
        // Shoot in a straightline
        bullet.body.setAllowGravity(false);

        bullet.setAngle(cannon.rotation);
        bullet.setPosition(cannon.x, cannon.y);

        var angle = Phaser.Math.DegToRad(cannon.body.rotation);
        bullet.body.world.scene.physics.velocityFromRotation(angle, 400, bullet.body.velocity);
        
        // Destroy the bullet after 2 seconds
        setTimeout( () => bullet.destroy(), 2000);
        
        // Add bullet to group
        scene.playerBullets.add(bullet);

        for (var npc of npcGroup.getChildren()) {
            scene.physics.add.overlap(bullet,npc,hitNPC,null,this);
        }  
    }
}

function scaleToMobile() {
    buildZone.destroy();
    buildZone2.destroy();

    buildZone = scene.add.rectangle(earthImage.getBounds().x,earthImage.getBounds().y,
                earthImage.getBounds().width / 1.8,earthImage.getBounds().height/1.15,0xffffff);
    scene.aGrid.placeAtIndex(71,buildZone);
    scene.physics.add.existing(buildZone);
    buildZone.setVisible(false);
    buildZone2 = scene.add.rectangle(earthImage.getBounds().x + 30,earthImage.getBounds().y,
                earthImage.getBounds().width - 30,earthImage.getBounds().height/2,0xffffff);
    scene.aGrid.placeAtIndex(71,buildZone2);
    scene.physics.add.existing(buildZone2);
    buildZone2.setVisible(false);

    text.setScale(0.80);

    text.x -= 10;
    text.y -= 10;
}