var WinMenu = new Phaser.Class({

    
    Extends: Phaser.Scene,
    initialize: function() {
        Phaser.Scene.call(this, { "key": "winmenu" });
    },
    init: function() {},
    preload: function() {
        this.load.image('nextGame', 'homemade/nextGameButton.jpg');
        this.load.image('exit', 'homemade/exitButton.jpg');
    },
    create: function() {

        window.isPaused = true;

        var gameOverText = this.add.text(100, 200, 'YOU WON', { fontFamily: 'CustomFont', fontSize: 130, color: '#a89151' }).setScale(w/700);
        gameOverText.setStroke('#333333', 8);
        gameOverText.setShadow(2, 2, "#333333", 5, true, true);

        var nextGame = this.add.sprite(w/2, h/2, 'nextGame').setInteractive().setScale(w/700);
        var exit = this.add.sprite(w/2, h/2+150,'exit').setInteractive().setScale(w/700);

        var aGrid = new AlignGrid(this);
        aGrid.placeAtIndex(0,gameOverText);
        aGrid.placeAtIndex(12,nextGame);
        aGrid.placeAtIndex(17,exit);

        if (window.innerHeight < 500) {
            aGrid.placeAtIndex(12,gameOverText);
            gameOverText.x -= w/2.5;
            gameOverText.y -= w/2.5;
        } 
        
        exit.on('pointerdown', function () { 
            gamewasrestarted =  false;
            this.scene.start('menuB');
            this.scene.stop();
        },this);

        nextGame.on('pointerdown', function () {
            chooseAnotherQuest()
            gamewasrestarted = false;
            this.scene.start('game');
            this.scene.stop();
        },this);
    },
    update: function() {}
});




