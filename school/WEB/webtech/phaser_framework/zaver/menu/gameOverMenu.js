var GameOverMenu = new Phaser.Class({

    
    Extends: Phaser.Scene,
    initialize: function() {
        Phaser.Scene.call(this, { "key": "gameovermenu" });
    },
    init: function() {},
    preload: function() {
        this.load.image('restart', 'homemade/restartButton.jpg');
        this.load.image('exit', 'homemade/exitButton.jpg');
    },
    create: function() {

        window.isPaused = true;

        var gameOverText = this.add.text(100, 200, 'GAME OVER', { fontFamily: 'CustomFont', fontSize: 100, color: '#baaa47' });
        gameOverText.setStroke('#333333', 16);
        gameOverText.setShadow(2, 2, "#333333", 5, true, true);


        var restart = this.add.sprite(w/2, h/2, 'restart').setInteractive().setScale(w/734);
        var exit = this.add.sprite(w/2, h/2+150,'exit').setInteractive().setScale(w/734);
        gameOverText.setScale(w/700)

        var aGrid = new AlignGrid(this);
        aGrid.placeAtIndex(0,gameOverText);
        aGrid.placeAtIndex(12,restart);
        aGrid.placeAtIndex(17,exit);

        if (window.innerHeight < 500) {
            aGrid.placeAtIndex(12,gameOverText);
            gameOverText.x -= w/2.6;
            gameOverText.y -= w/2.6;  
        } 

        exit.on('pointerdown', function () {
             
            level = currentLevel;
           
            localStorage.setItem('level', level);
            loadQuest();
            
            console.log(checkAmountOfQuests());
            console.log(Mainquests.quests[randomQuest]);
            gamewasrestarted = true;
           
            game.scene.stop('game'); 
            this.scene.start('menuB');
            this.scene.stop();

        },this);

        restart.on('pointerdown', function () {

            gameReseting = true;
            clearInterval(window.npcInterval);
            clearInterval(window.shootInterval);
            clearInterval(window.shdRegenInterval);
            console.log("Game Restarted!")

            level = currentLevel;
            localStorage.setItem('level', level);

            loadQuest()

          
            game.scene.stop('game');  
            gamewasrestarted = true;
            this.scene.start('game');
            this.scene.stop();
            
        },this);
    },
    update: function() {}
});




