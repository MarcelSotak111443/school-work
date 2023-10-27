var PauseMenu = new Phaser.Class({

    
    Extends: Phaser.Scene,
    initialize: function() {
        Phaser.Scene.call(this, { "key": "pausemenu" });
    },
    init: function() {},
    preload: function() {

        this.load.image('continue', 'homemade/continueButton.jpg');
        this.load.image('restart', 'homemade/restartButton.jpg');
        this.load.image('exit', 'homemade/exitButton.jpg');
    },
    create: function() {

        var continueGame = this.add.sprite(w/2, h/2-150, 'continue').setInteractive().setScale(w/734);
        var restart = this.add.sprite(w/2, h/2, 'restart').setInteractive().setScale(w/734);
        var exit = this.add.sprite(w/2, h/2+150,'exit').setInteractive().setScale(w/734);

        var aGrid = new AlignGrid(this);
        aGrid.placeAtIndex(7,continueGame);
        aGrid.placeAtIndex(12,restart);
        aGrid.placeAtIndex(17,exit);

        clearInterval(window.npcInterval);
        clearInterval(window.shootInterval);
        clearInterval(window.shdRegenInterval);

        exit.on('pointerdown', function () {
            game.scene.stop('game');
            this.scene.start('menuB');
            this.scene.stop();
            
        },this);

        restart.on('pointerdown', function () {

            clearInterval(window.npcInterval);
            clearInterval(window.shootInterval);
            clearInterval(window.shdRegenInterval);
            level = currentLevel;
            localStorage.setItem('level', level);
            loadQuest()
           
            gameReseting = true;
            gamewasrestarted = true;
            this.scene.start('game');
            wasPaused = true;
            this.scene.stop();

        },this);

           continueGame.on('pointerdown', function () {

           console.log("Game Continue!")    
           window.npcInterval = window.setInterval(generateNPC, npcDelay - (Math.pow(level, 1/2)) * 100 + (time /2 )) ;
           window.shootInterval = window.setInterval(shootLaser, shootDelay - (Math.pow(level, 1/2)) * 100 + (time /2 ));
           window.shdRegenInterval = window.setInterval(regenShield, window.shdRegenDelay);
           
           continueGame.setVisible(false)
           restart.setVisible(false)
           exit.setVisible(false)
           window.isPaused = false;
           this.scene.resume('game');
           this.scene.stop();        
           
        },this);
    },
    update: function() {}
});




