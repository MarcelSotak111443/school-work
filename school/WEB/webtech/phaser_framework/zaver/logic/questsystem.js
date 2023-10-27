w = window.innerWidth;
var questNumber = 0;
let quest;
let Mainquests;
let description;
let questAmount;
let questObject;
var randomQuest=0;
var check = false;
var level = 0;
var size = w/4;

function loadQuest() {
    fetch('./quests.json').then(function(response) {
        return response.json();
        }).then(function(data) {
            Mainquests = data;
        });
}

function checkAmountOfQuests() {
    questNumber = 0;
    for(let quest in Mainquests.quests)
    questNumber ++;

    return questNumber;
}

function chooseAnotherQuest() {
    
    if(checkAmountOfQuests() < 1){
       
        loadQuest();
        level ++;
        localStorage.setItem('level', level);
        
    }
    var randomQuest = Math.floor(Math.random() * checkAmountOfQuests());

    description = Mainquests.quests[randomQuest].description;
    questAmount = Mainquests.quests[randomQuest].number;
    questObject = Mainquests.quests[randomQuest].object;
    Mainquests.quests.splice(randomQuest,1)
    
    randomQuest = 0;
    updateQuestText();
}
      
function setLevel(level) {
    level = level;
}

function updateQuestText() {
    questText.setText([
        'lvl ' + level,
       'QUEST: ' + description + " " + questAmount*level  
    ]);    

    if (window.innerHeight < 500) {
        
        bar.x  = questText.displayWidth+w/5;
        fitbar.x  = questText.displayWidth+w/5;
        size = w/2;
        bar.fillRect(0,0,w/2,w/25);
    } else{
        bar.x  = questText.displayWidth + w/20;
        fitbar.x  = questText.displayWidth+ w/20 ;
        size = w/4;
    }
   
    fitbar.fillRect(0,0,getValueForQuest(questObject),w/25);
    if(getValueForQuest(questObject) >= size){
        win.play();
        time = 0;
        npcDestroyed = 0;
        angle = 0;
        
        gameover = true;
        scene.paused = true;
        scene.scene.pause();
        clearInterval(window.npcInterval);
        clearInterval(window.shootInterval);
        clearInterval(window.shdRegenInterval);
        scene.scene.launch('winmenu');
    } 
}

function getValueForQuest(object) {
    switch(object){
        case 'player':
            return time * (size/(questAmount*level));
        case 'npc':
            return npcDestroyed * (size/(questAmount*level));
        case 'earth':
            return (angle * 0.18) * (size/(questAmount*level));
        case 'factory':
            return (powerPlantGroup.getLength()) * (size/(questAmount*level));
        case 'cannon':
            return (cannonGroup.getLength()) * (size/(questAmount*level));     
    }
}