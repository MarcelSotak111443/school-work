

var GameMenuB = new Phaser.Class({

    Extends: Phaser.Scene,
    initialize: function() {
        Phaser.Scene.call(this, { "key": "menuB" });
    },
    init: function() {

    },
    preload: function() {
        this.load.image('startGame', 'homemade/startGameButton.jpg');
        this.load.image('tutorialButton', 'homemade/tutorialButton.jpg');
        this.load.image('background', 'homemade/startPicture.jpg'); 
        this.load.audio("gameSound","sound/gamesound.mp3");
      
    },
    create: function() {
        
        
        if (this.aGrid == undefined) {
            var aGrid = new AlignGrid({scene:this,rows:12,cols:11});
            //aGrid.showNumbers();
        }

        savedLevel = localStorage.getItem('level');
        console.log("toto je zaciatok "+ savedLevel);

        // Delay option can only be passed in config
        gameSound.play('loop', {
            delay: 0
        });

        var config4 = {
            text: 'ALIEN INVASION',
            style: {
                fontSize: '93px',
                fontFamily: 'CustomFont',
                color: '#baaa47'
            }
        };

        var background = this.add.sprite(w/2,w/2, 'background').setScale(w/943);

        var  gameTitle = this.make.text(config4).setScale(w/700);
        gameTitle.setStroke('#333333', 16);
        gameTitle.setShadow(2, 2, "#333333", 5, true, true);

        var startGame  = this.add.sprite(0,0, 'startGame').setInteractive().setScale(w/734);
        var tutorialButton= this.add.sprite(0,0, 'tutorialButton').setInteractive().setScale(w/734);
        
        var oldGrid = aGrid;
        if (window.innerHeight < 500) {
            var aGrid = new AlignGrid(this);
            aGrid.placeAtIndex(12,background);
            aGrid.placeAtIndex(12,gameTitle);
            this.cameras.main.setBackgroundColor(0x00000);
            gameTitle.x -= w/2.3;
            gameTitle.y -= w/2.3;
            aGrid = oldGrid;
        } else {
            aGrid.placeAtIndex(0 ,gameTitle);    
        }

        aGrid.placeAtIndex(60,startGame);
        aGrid.placeAtIndex(82,tutorialButton);
        
        startGame.on('pointerdown', function () {
            this.scene.start('difficultyMenu');
            this.scene.stop();
        },this); 


        tutorialButton.on('pointerdown', function () {
           this.scene.start('tutorialmenu');
           this.scene.stop();
        },this);
    
    },
    update: function() {}
});