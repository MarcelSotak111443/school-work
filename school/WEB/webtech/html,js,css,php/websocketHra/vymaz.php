<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
        <script src="https://cdnjs.cloudflare.com/ajax/libs/phaser-ce/2.13.3/phaser.js"></script>
    <script type="text/javascript" src="phaser.min.js"></script>
    <title></title>
</head>
<body>
<script type="text/javascript">
    

   


class Example extends Phaser.Scene
{
    preload ()
    {
        this.load.image('bg', 'sprites/straighWall');
        this.load.image('arrow', 'sprites/p1.png');
    }

    create ()
    {
        this.add.image(400, 300, 'bg');

        this.physics.add.sprite(200, 150, 'arrow')
            .setVelocity(200, -200)
            .setCollideWorldBounds(true, 1, 1, true);

        
    }


    update (){
        
    }
}

const config = {
    type: Phaser.AUTO,
    width: 800,
    height: 600,
    pixelArt: true,
    parent: 'phaser-example',
    physics: {
        default: 'arcade',
        arcade: {
            debug: false
        }
    },
    scene: Example
};

const game = new Phaser.Game(config);


</script>
</body>
</html>