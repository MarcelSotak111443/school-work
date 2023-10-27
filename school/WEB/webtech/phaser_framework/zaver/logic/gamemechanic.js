function pause(scene) {
    clearInterval(window.npcInterval);
    clearInterval(window.shootInterval);
    clearInterval(window.shdRegenInterval);

    console.log("Game Paused!");
    scene.paused = true;
    scene.scene.pause();
    window.isPaused = true;

    scene.scene.launch('pausemenu');
}