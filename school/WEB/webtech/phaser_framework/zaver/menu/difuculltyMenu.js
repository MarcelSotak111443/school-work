var DifficultyMenu = new Phaser.Class({

    Extends: Phaser.Scene,
    initialize: function() {
        Phaser.Scene.call(this, { "key": "difficultyMenu" });
    },
    init: function() {},
    preload: function() {
        this.load.image('easy', 'homemade/easyLevel.jpg');
        this.load.image('medium', 'homemade/mediumLevel.jpg');
        this.load.image('hard', 'homemade/hardLevel.jpg');
        this.load.image('background', 'homemade/startPicture.jpg');
    },
    create: function() {
      
        var rec = this.add.rectangle(0,0,5000,5000,0x000000);

        var background = this.add.sprite(0,0, 'background').setScale(w/943);
        
        var easy = this.add.sprite(w/2, h/2-150, 'easy').setInteractive().setScale(w/734);
      
        var medium = this.add.sprite(w/2, h/2, 'medium').setInteractive().setScale(w/734);
        var hard = this.add.sprite(w/2, h/2+150,'hard').setInteractive().setScale(w/734);

       
        
        var aGrid = new AlignGrid(this);
        aGrid.placeAtIndex(7,easy);
        aGrid.placeAtIndex(12,medium);
        aGrid.placeAtIndex(17,hard);
        aGrid.placeAtIndex(12,background);


        easy.on('pointerdown', function () {
            this.scene.start('game', { level: 1});

        },this); 
        medium.on('pointerdown', function () {
            this.scene.start('game', { level : 2});
        },this); 
        hard.on('pointerdown', function () {
            this.scene.start('game', { level: 3});
        },this); 


    },
    update: function() {}
});