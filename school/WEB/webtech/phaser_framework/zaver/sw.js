var cacheName = 'alien-invasion';
var filesToCache = [
  '/',
  '/index.html',
  '/quests.json',
  '/manifest.json',

  '/css/style.css',
  '../font/Thempo.ttf',

  '/favicon/android-chrome-192x192.png',
  '/favicon/android-chrome-512x512.png',
  '/favicon/apple-touch-icon.png',
  '/favicon/favicon-16x16.png',
  '/favicon/favicon-32x32.png',

  '/homemade/backButton.jpg',
  '/homemade/continueButton.jpg',
  '/homemade/easyLevel.jpg',
  '/homemade/exitButton.jpg',
  '/homemade/hardLevel.jpg',
  '/homemade/mediumLevel.jpg',
  '/homemade/nextGameButton.jpg',
  '/homemade/pauseButton.jpg',
  '/homemade/playButton.jpg',
  '/homemade/restartButton.jpg',
  '/homemade/startGameButton.jpg',
  '/homemade/startPicture.jpg',
  '/homemade/tutorialButton.jpg',

  "/logic/code.js",
  "/logic/game.js",
  "/logic/gamemechanic.js",
  "/logic/phaser.js",
  "/logic/questsystem.js",

  "/menu/difuculltyMenu.js",
  "/menu/gameOverMenu.js",
  "/menu/menu.js",
  "/menu/menuB.js",
  "/menu/pausemenu.js",
  "/menu/tutorialmenu.js",
  "/menu/winMenu.js",

  '/pictures/cannon.png',
  '/pictures/earth.png',
  '/pictures/laser.png',
  '/pictures/laserball.png',
  '/pictures/npc.png',
  '/pictures/powerplant.png',
  '/pictures/shield.png',

  '/sound/destroying.mp3',
  '/sound/gamesound.mp3',
  '/sound/lasershot.mp3',
  '/sound/lostgame.wav',
  '/sound/shot.wav',
  '/sound/win.wav',

  "/utilities/align.js",
  "/utilities/alignGrid.js",
  "/utilities/UIBlock.js",
];

self.addEventListener('install', function(event) {
  console.log('sw install');
  event.waitUntil(
    caches.open(cacheName).then(function(cache) {
      //console.log('sw caching files');
      return cache.addAll(filesToCache);
    }).catch(function(err) {
      console.log(err);
    })
  );
});

self.addEventListener('fetch', (event) => {
  //console.log('sw fetch');
  console.log(event.request.url);
  event.respondWith(
    caches.match(event.request).then(function(response) {
      return response || fetch(event.request);
    }).catch(function (error) {
      console.log(error);
    })
  );
});

self.addEventListener('activate', function(event) {
  //console.log('sw activate');
  event.waitUntil(
    caches.keys().then(function(keyList) {
      return Promise.all(keyList.map(function(key) {
        if (key !== cacheName) {
          //console.log('sw removing old cache', key);
          return caches.delete(key);
        }
      }));
    })
  );
});