

var TutorialMenu = new Phaser.Class({

    Extends: Phaser.Scene,
    initialize: function() {
        Phaser.Scene.call(this, { "key": "tutorialmenu" });
    },
    init: function() {

    },
    preload: function() {
        this.load.image('backButton', 'homemade/backButton.jpg');
        this.load.image('powerplant', 'pictures/powerplant.png');
        this.load.image('cannon', 'pictures/cannon.png');
        this.load.image('npc', 'pictures/npc.png');
        this.load.image('shield', 'pictures/shield.png');
        this.load.image('background', 'homemade/startPicture.jpg');
        this.load.script('webfont', 'https://ajax.googleapis.com/ajax/libs/webfont/1.6.26/webfont.js');

    },
    create: function() {
        if (this.aGrid == undefined) {
            var aGrid = new AlignGrid({scene:this,rows:12,cols:11});
            //aGrid.showNumbers();
        }

        loadQuest();

        console.log(w);
        var style2 = {
            fontSize: "19px",
            fontFamily: 'CustomFont',
            color: '#baaa47',
        };

        var config3 = {
            text: "Aliens are attacking! Only you with your godlike power can stop them!\n" +
            "Use RIGT ARROW and LEFT ARROW to rotate Earth. Buy buildings for money\n" +
            "and use LEFT MOUSE BUTTON to shoot from cannons. Finish all quests \n"+
            "and save Earth. On mobile phone you can rotate Earth by rotating the device!\n",
            style: style2
        };
        var config5 = {
            text: ` drag and drop powerplants \n to generate shield 1/1sec \n you have to build shield first!`,
            style: style2
        };
        var config6 = {
            text: ` place cannons so you can shoot your enemies \n and get money ` ,
            style: style2
        };
        var config7 = {
            text: `buy shield with full power \n(you can buy this only once)` ,
            style: style2
        };
        var config8 = {
            text: `these intergalactic behemoths will attack your \nplanet protect your family and destroy them` ,
            style: style2
        };

        var background = this.add.sprite(w/2,w/2, 'background').setScale(w/943);

        var tutorialText = this.make.text(config3).setScale(w/700);
        tutorialText .setStroke('#333333', 8);
        tutorialText.setShadow(2, 2, "#333333", 5, true, true);

        var text1 = this.make.text(config5).setScale(w/700);
        var text2 = this.make.text(config6).setScale(w/700);
        var text3 = this.make.text(config7).setScale(w/700);
        var text4 = this.make.text(config8).setScale(w/700);

        text1 .setStroke('#333333', 8);
        text1.setShadow(2, 2, "#333333", 5, true, true);
        text2 .setStroke('#333333', 8);
        text2.setShadow(2, 2, "#333333", 5, true, true);
        text3 .setStroke('#333333', 8);
        text3.setShadow(2, 2, "#333333", 5, true, true);
        text4.setStroke('#333333', 8);
        text4.setShadow(2, 2, "#333333", 5, true, true);
     
        var backButton  = this.add.sprite(0,0, 'backButton').setInteractive().setScale(w/934);;
        var shield  = this.add.sprite(0,0, 'shield').setScale(w/8500);
        var cannon= this.add.sprite(0,0, 'cannon').setScale(w/4000);
        var npc  = this.add.sprite(0,0, 'npc').setScale(w/1500);
        var powerPlant= this.add.sprite(0,0, 'powerplant').setScale(w/4000);

        if (window.innerHeight < 500) {
            aGrid.placeAtIndex(60,background);
            aGrid.placeAtIndex(2,tutorialText);
            aGrid.placeAtIndex(36,text1);
            aGrid.placeAtIndex(47,text2);
            aGrid.placeAtIndex(69,text3);
            aGrid.placeAtIndex(91,text4);
            aGrid.placeAtIndex(40,powerPlant);
            aGrid.placeAtIndex(84,shield);
            aGrid.placeAtIndex(62,cannon);
            aGrid.placeAtIndex(106,npc);
        } else {
            aGrid.placeAtIndex(0,tutorialText);
            aGrid.placeAtIndex(34,text1);
            aGrid.placeAtIndex(45,text2);
            aGrid.placeAtIndex(67,text3);
            aGrid.placeAtIndex(89,text4);
            aGrid.placeAtIndex(41,powerPlant);
            aGrid.placeAtIndex(85,shield);
            aGrid.placeAtIndex(63,cannon);
            aGrid.placeAtIndex(107,npc);
        }

        tutorialText.x += 10    ;

        aGrid.placeAtIndex(115,backButton);

        text2.y += w/17

        backButton.on('pointerdown', function () {
         
            this.scene.start('menuB');
            this.scene.stop();
        },this);  
   
    },
    update: function() {}
});