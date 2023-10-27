<?php 

header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
require_once('config.php');


ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
$method = $_SERVER['REQUEST_METHOD'];


ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
// Check if the _method field is set (for method spoofing)
if (isset($_POST['_method'])) {
  $method = $_POST['_method'];
}

switch($method) {
    case 'GET':
        // If a "day" parameter is set, retrieve menu items for that day
        // Otherwise, retrieve all menu items
    if (isset($_GET['type']) && isset($_GET['day'])) {

        read_whole_menu($db,$_GET['day']);
    }
    else if (isset($_GET['day'])) {

        $day = $_GET['day'];
        read_menu_by_day($db, $day);
    } 

    
    else {
        read_menu($db);
    }

    break;

    case 'POST':
    $data = json_decode(file_get_contents("php://input"), true);
    
    create_menu($db, $data);


    break;

    case 'PUT':
        // Retrieve the request body
    $request_body = file_get_contents('php://input');
    
        // Convert the request body into a PHP associative array
    $data = json_decode($request_body, true);

        // Check if an ID   parameter is provided
    if (empty($_GET['id'])) {
            // Return a 400 Bad Request error if the ID parameter is missing
        http_response_code(400);
        echo '<h1>400 Bad Request</h1><p>The "id" parameter is missing.</p>';
    } else {
            // Check if a price is provided
        if (empty($data['price'])) {
                // Return a 400 Bad Request error if the price is missing
            http_response_code(400);
            echo '<h1>400 Bad Request</h1><p>The "price" parameter is missing.</p>';
        } else {
                // Update the menu item with the provided ID
            update_menu($db, $_GET['id'], $data);
        }
    }
    break;

    case 'DELETE':
        // Check if a restaurant parameter is provided
    if (empty($_GET['id'])) {
            // Return a 400 Bad Request error if the restaurant parameter is missing
        http_response_code(400);
        echo '<h1>400 Bad Request</h1><p>The "restaurant" parameter is missing.</p>';
    } else {
            // Delete all menu items for the provided restaurant
        delete_menu($db, $_GET['id']);
    }
    break;

    default:
        // Return a 405 Method Not Allowed error if the request method is not supported
    http_response_code(405);
    echo '<h1>405 Method Not Allowed</h1>';
    break;
}


function read_menu($db)
{
ini_set('display_errors', 1); error_reporting(E_ALL);
    $stmt = $db->query('SELECT name, price from site_parsed;');
    
    $games = $stmt->fetchAll(PDO::FETCH_ASSOC);

    $json = json_encode($games, JSON_UNESCAPED_UNICODE);
ini_set('display_errors', 1); error_reporting(E_ALL);
    if ($json === false) {
        echo 'Error encoding JSON: ' . json_last_error_msg();
    } else {
        if (!mb_check_encoding($json, 'UTF-8')) {
            $json = mb_convert_encoding($json, 'UTF-8', mb_detect_encoding($json));
        }
ini_set('display_errors', 1); error_reporting(E_ALL);
        echo $json;
    }
}
function read_whole_menu($db , $day){


   $first = "SELECT name, price, restaurant, CONCAT('data:image/png;base64,', TO_BASE64(image)) AS image, day FROM site_parsed";
   if ($day != "none") {
    $second = " WHERE day = '$day'";
    $first .= $second;
}
$first .= " ORDER BY CASE
WHEN day = 'Sunday' THEN 1
WHEN day = 'Monday' THEN 2
WHEN day = 'Tuesday' THEN 3
WHEN day = 'Wednesday' THEN 4
WHEN day = 'Thursday' THEN 5
WHEN day = 'Friday' THEN 6
WHEN day = 'Saturday' THEN 7
END ASC";

// echo $first;
$stmt = $db->query($first);
$games = $stmt->fetchAll(PDO::FETCH_ASSOC);
$json = json_encode($games, JSON_UNESCAPED_UNICODE);
if ($json === false) {
    echo 'Error encoding JSON: ' . json_last_error_msg();
} else {
    if (!mb_check_encoding($json, 'UTF-8')) {
        $json = mb_convert_encoding($json, 'UTF-8', mb_detect_encoding($json));
    }
    echo $json;
}
}


function read_menu_by_day($db, $day) {
	
	
    $stmt = $db->prepare('SELECT name, price, restaurant FROM site_parsed WHERE day = ?');
    $stmt->execute([$day]);
    $games = $stmt->fetchAll(PDO::FETCH_ASSOC);
    $json = json_encode($games, JSON_UNESCAPED_UNICODE);
    if ($json === false) {
        echo 'Error encoding JSON: ' . json_last_error_msg();
    } else {
        if (!mb_check_encoding($json, 'UTF-8')) {
            $json = mb_convert_encoding($json, 'UTF-8', mb_detect_encoding($json));
        }
        echo $json;
    }
}


function create_menu($db, $data) {
  $days = array("Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday");

  
  foreach ($days as $day) {
    $stmt = $db->prepare('INSERT INTO site_parsed (name, price, restaurant, day) VALUES (:name, :price, :restaurant, :day)');
    $stmt->bindParam(':price', $data['price']);
    $stmt->bindParam(':name', $data['name']);

    $stmt->bindParam(':restaurant', $data['restaurant']);
    $stmt->bindParam(':day', $day);
    $stmt->execute();
}
read_menu($db);
  //echo json_encode(array('success' => 'Data created successfully'));
}


function update_menu($db, $id, $data)
{
    $json = file_get_contents('php://input');
    $data = json_decode($json, true);
    if (isset($data['price'])) {
        $stmt = $db->prepare('UPDATE site_parsed SET price = :price WHERE id = :id;');
        $stmt->bindParam(':id', $id);
        $stmt->bindParam(':price', $data['price']);
        $stmt->execute();
       // echo json_encode(array('success' => 'Data updated successfully'));
    } else {
       // echo json_encode(array('error' => 'Price parameter is not defined'));
    }
    read_menu($db);
}

function delete_menu($db, $restaurant)
{
    if (empty($restaurant)) {
       // echo json_encode(array('error' => 'Delete failed'));
        http_response_code(400);
    } else {
        $stmt = $db->prepare('DELETE FROM site_parsed WHERE id = :id');
        $stmt->bindParam(':id', $restaurant);
        $stmt->execute();
      //  echo json_encode(array('success' => 'Data deleted successfully'));
    }
    read_menu($db);
}
?>