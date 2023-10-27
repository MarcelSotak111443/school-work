var w = window.innerWidth;
var h = window.innerHeight;

if(w > h)
    w = h;

console.log(w)

var config = {
    type: Phaser.AUTO,
    autoCenter: Phaser.Scale.CENTER_BOTH,
    width: w,
    height: w,
    scene: [GameMenu,Game,PauseMenu,DifficultyMenu, GameMenuB , GameOverMenu,WinMenu,TutorialMenu],
    physics: {
        default: 'arcade',
        arcade: {
            debug: false
        }
    },
    dom: {
        createContainer: true
    },
};

if (h < 500) {
    config.width = window.innerWidth;
    config.height = window.innerHeight;
}

const isMobile = /iPhone|iPad|iPod|Android/i.test(navigator.userAgent);
if (isMobile) {
    //alert("Mobile");
    requestOrientationPermission();
}

window.isOrientationChanged = false;
addEventListener('orientationchange', (event) => { 
    location.reload();
    window.isOrientationChanged = true;
});

addEventListener('resize', (event) => { 
    location.reload();
});


function requestOrientationPermission() {
    try {
        DeviceOrientationEvent.requestPermission()
        .then(response => {
            if (response == 'granted') {
                console.log("Recieved Permission to Use Mobile Orientation");
            }
        });
    } catch(error) {}
}

var game = new Phaser.Game(config);