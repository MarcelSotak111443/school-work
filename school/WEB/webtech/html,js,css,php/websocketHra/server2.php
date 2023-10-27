<?php
//php server2.php start
use Workerman\Worker;
use Workerman\Lib\Timer;
require_once __DIR__.'/vendor/autoload.php';

$clients = array();
$privilegedUser = null;
$gameStarted = false;



// SSL context.
$context = [
    'ssl' => [
        'local_cert'  => '/home/xsotakm/webte_fei_stuba_sk.pem',
        'local_pk'    => '/home/xsotakm/webte.fei.stuba.sk.key',
        'verify_peer' => false,
    ]
];
class Ball{
  public $x;
  public $y;

  public function __construct($x, $y) {
    $this->x = $x;
    $this->y = $y;
}
public function move($dx, $dy) {
    $this->x += $dx;
    $this->y += $dy;
}
}

$ball = new Ball(0,0);

class Player {
  public $x;
  public $y;

  public function __construct($x, $y) {
    $this->x = $x;
    $this->y = $y;
}

public function move($dx, $dy) {
    $this->x += $dx;
    $this->y += $dy;
}
public function getX(){
   return $this->x;
}
}


// Create A Worker and Listens 9000 port, use Websocket protocol
$ws_worker = new Worker("websocket://0.0.0.0:9000", $context);

// Enable SSL. WebSocket+SSL means that Secure WebSocket (wss://). 
// The similar approaches for Https etc.
$ws_worker->transport = 'ssl';

// 4 processes
 //$ws_worker->count = 4;
$ws_worker->count = 1;

// Add a Timer to Every worker process when the worker process start

$ws_worker->onWorkerStart = function($ws_worker) use (&$clients, &$gameStarted, &$ball) {   
    $GLOBALS['connected_players'] = 0; 
    $GLOBALS['userdata'] = 0;    
    $x = -2;
    $y = 0;
    echo "HAPENED";
    Timer::add(0.1, function() use ($ws_worker, &$x, &$y, &$gameStarted, &$ball) {          

        if ($gameStarted == true) {       


            $message = json_encode(array('type' => 'sendingBallPosition', 'ballx' => $ball->x , 'bally' => $ball->y));
            foreach ($ws_worker->connections as $connection) {


               $connection->send($message);         
           }     
       }          
   });
};


$myMap = array(
  1 => true,
  2 => true,
  3 => true,
  4 => true
);

// Emitted when new connection come
$ws_worker->onConnect = function($connection) use (&$clients, &$privilegedUser, &$myMap)
{
    // Emitted when websocket handshake done
    $connection->onWebSocketConnect = function($connection) use (&$clients, &$privilegedUser,&$myMap)
    {

        $GLOBALS['connected_players']++; 



        if ( $GLOBALS['connected_players'] > 4) {
            $connection->send(json_encode(array('type' => 'server_full')));
            $GLOBALS['connected_players']--; 
     //   $connection->close();

            return;
        }
        foreach ($myMap as $key => $value) {
            if ($value === true) {
        $freeNumber = $key; // Assign the current key to the $freeNumber variable
        $myMap[$key] = false; 
        break; // Stop iterating after the first true value is found
    }
}




echo "New client connected: {$connection->id}\n";

$player = new Player(0,0); 

$clients[$connection->id] = array('username' => null, 'connection' => $connection, 'player'=> $player, 'cube'=> $freeNumber, 'range' => 0,  'paddleTop' => null,'paddleLeft'=>null ,'hp'=>3);

        // Set the first user in the array as the privileged user
if (count($clients) === 1) {
    $privilegedUser = reset($clients);
    $privilegedUser['connection']->send(json_encode(array('type' => 'privileged')));
}

if ( $GLOBALS['connected_players'] == 4) {

    foreach ($clients as $client) {
        $message = json_encode(array('type' => 'startGame', 'clientsCount' => count($clients)));
        $client['connection']->send($message);
    }
}


};
};
$ws_worker->onMessage = function($connection, $data) use(&$privilegedUser , &$clients, &$gameStarted, &$ball)
{
   // if ($connection === $privilegedUser) {
            // process the data received and allow privileged user to click the button
   //     }

    $data = json_decode($data, true);
    if ($data['type'] === 'username') {
        $username = $data['username'];
        $clients[$connection->id]['username'] = $username;

    // Update the list of connected clients
        $connectedClients = array();
        foreach ($clients as $client) {
            $connectedClients[] = array('id' => $client['connection']->id, 'username' => $client['username']);
        }

    // Send the updated client list to all connected clients
        $message = json_encode(array('type' => 'connected_clients', 'clients' => $connectedClients));
        foreach ($clients as $client) {
            $client['connection']->send($message);
        }
    }

    if ($data['type'] === 'move') {
     $player =  $clients[$connection->id]['player'];
   //  $player->move($data['direction'], 0);




     $newRange = $clients[$connection->id]['range'] + $data['direction'];
     if ($newRange < 150 && $newRange > -150) {
        $clients[$connection->id]['range'] = $newRange;
        
        $updatedPosition = json_encode(array(
          'type' => 'position',
          'id' => $connection->id,
          'direction' => $data['direction'],
          'cube' => $clients[$connection->id]['cube']

      ));
        foreach ($clients as $client) {
            $client['connection']->send($updatedPosition);
        }

    }
}
if ($data['type'] === 'startGameButtonClicked') {

    foreach ($clients as $client) {
        $message = json_encode(array('type' => 'startGame', 'clientsCount' => count($clients)));
        $client['connection']->send($message);
    }
}
if ($data['type'] === 'ballMovement') {



    foreach ($clients as $client) {
        $message = json_encode(array('type' => 'startGame', 'clientsCount' => count($clients)));
        $client['connection']->send($message);
    }
}
if ($data['type'] === 'cubePosition') {
    $clients[$connection->id]['paddleTop'] = $data['positionTop'];
    $clients[$connection->id]['paddleLeft'] = $data['positionLeft'];

}

if ($data['type'] === 'BallStartMove') {

    $ball->x = $data['positionTop'];
    $ball->y = $data['positionLeft'];


}
if ($data['type'] === 'startGame') {
    $gameStarted = true;

}

if ($data['type'] === 'takehp') {

  foreach ($clients as $key => $client) {
    if ($client['cube'] == $data['player']) {
      $clients[$key]['hp'] = $client['hp'] - 1;

      echo $clients[$key]['hp'];
      $message = json_encode(array('type' => 'Hpstatus', 'player' =>$client['cube'], 'hp' =>$clients[$key]['hp'] ));
      foreach ($clients as $client) {

        $client['connection']->send($message);
    }
}
}

$clients_with_zero_hp = 0;

foreach ($clients as $key => $client) {
    if ($client['hp'] == 0) {
        $clients_with_zero_hp++;
    }
}

if ($clients_with_zero_hp == count($clients)) {
    $message = json_encode(array('type' => 'END'));
      foreach ($clients as $client) {

        $client['connection']->send($message);
    }
}
}



};

// Emitted when connection closed
$ws_worker->onClose = function($connection) use (&$clients, &$privilegedUser, &$myMap) {

 $myMap[$clients[$connection->id]['cube']] = true;





 $GLOBALS['connected_players']--;
 echo "Client disconnected: {$connection->id}\n";
 unset($clients[$connection->id]);



  // Update the privileged user if the first user in the array left
 if (is_array($privilegedUser) && $privilegedUser['connection'] === $connection) {
    $privilegedUser = reset($clients);
    if (is_array($privilegedUser) && $privilegedUser['connection'] !== null) {
        $privilegedUser['connection']->send(json_encode(array('type' => 'privileged')));
    }
}


  // Update connected clients and send to all clients
$connectedClients = array();
foreach ($clients as $client) {
    $connectedClients[] = array('id' => $client['connection']->id, 'username' => $client['username']);
}

    // Send the updated client list to all connected clients
$message = json_encode(array('type' => 'connected_clients', 'clients' => $connectedClients));
foreach ($clients as $client) {
    $client['connection']->send($message);
}
};
// Run worker
Worker::runAll();

?>
