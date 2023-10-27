<?php
$hostname = "localhost:3306";
$username = "xsotakm";
$password = "8gIbHYiAL3l6xe7";
$dbname = "zadanie2";


  $db = new PDO("mysql:host=$hostname;dbname=$dbname", $username, $password);
  $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);


// Create connection
$conn = new mysqli($hostname, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
else{
  
}
?>