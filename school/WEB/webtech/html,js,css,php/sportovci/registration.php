<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title></title>
  <script type="text/javascript" src="myscript.js"></script>
   <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
     <link rel="stylesheet" type="text/css" href="index.css">


<!-- Bootstrap JavaScript -->
<script src="js/bootstrap.min.js"></script>

</head>
<body>



<?php

session_start();  
require 'config.php';

if(isset($_POST["submit"])){
  $username = $_POST["name"];
  $surname = $_POST["surname"];
  $email = $_POST["email"];
  $password = $_POST["psw"];
  $confirmpassword = $_POST["psw-repeat"];


    

  $exist = $conn->query( "SELECT * FROM tb_user WHERE name = '$username' AND surname = '$surname' OR email = '$email'");

  if ($exist->num_rows > 0){
    "<script> alert('Username or Email Has Already Taken'); 
    </script>";
   //header('Location: registration.php');
  }
  else{

    if($password == $confirmpassword){
      $password =  password_hash($password, PASSWORD_BCRYPT);
    try {
    $sql = "INSERT INTO tb_user(name, surname, email, password) VALUES (?,?,?,?)";
    $stmt = $db->prepare($sql);
    $success = $stmt->execute([$username,$surname,$email,$password]);

$sql = "SELECT * FROM  tb_user WHERE email= ?";
$stmt = $db->prepare($sql);
$stmt->execute([$email]);
$row = $stmt->fetchAll(PDO::FETCH_ASSOC);
$value = $row[0]['id'];



    $sql = "INSERT INTO login_attr(user_id, login_type) VALUES (?,?)";
    $stmt = $db->prepare($sql);
    $success = $stmt->execute([$value, 'basic_registration']);

} catch (PDOException $e) {

    echo "Error: " . $e->getMessage();
} 
   
    //  echo
     // "<script> alert('Registration Successful'); </script>";
      header("Location: login.php");
    }
    else{
      echo
      "<script> alert('Password Does Not Match'); </script>";
    }
  }
 // header("Location: registration.php");


}

?>
<nav class="navbar navbar-expand-lg navbar-light bg-light ">
 
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>
  <div class="collapse navbar-collapse" id="navbarNav">
    <ul class="navbar-nav">
      <li class="nav-item active">
        <a class="nav-link" href="index.php">Home</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="registration.php">Register</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="login.php">Login</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="premiumPage.php">Admin</a>
      </li>
    </ul>
  </div>
</nav>

<form action="registration.php" method="post" autocomplete="off" onsubmit="return validateForm()">
  <div class="container">
    <h1 class="text-center">Registration</h1>

    <div class="form-group">
      <label for="name"><b>NAME:</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="name" id="name" class="form-control check" required value="">
      <div class="warning"></div>
    </div>

    <div class="form-group">
      <label for="surname"><b>SURNAME:</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="surname" id="surname" class="form-control check" required value="">
      <div class="warning"></div>
    </div>

    <div class="form-group">
      <label for="email"><b>EMAIL:</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="email" id="email" class="form-control check" required>
      <div class="warning"></div>
    </div>

    <div class="form-group">
      <label for="psw"><b>PASSWORD:</b></label>
      <input onBlur="FieldCheck(this)" type="password" name="psw" id="psw" class="form-control check" required>
      <div class="warning"></div>
    </div>

    <div class="form-group">
      <label for="psw-repeat"><b>PASSWORD:</b></label>
      <input onBlur="FieldCheck(this)" type="password" name="psw-repeat" id="psw-repeat" class="form-control check" required>
      <div class="warning"></div>
    </div>

   <button type="submit" name="submit" class="btn btn-warning mx-auto d-block">Register</button>
  </div>

<div class="text-center">
  <a href="login.php" class="text-dark">Login</a>
</div>
</form>

<script>
  
     function validateForm() {
      console.log("working");
    const nodeList = document.querySelectorAll(".check");
    for (let i = 0; i < nodeList.length; i++) {
      if (nodeList[i].value === "") {
        nodeList[i].style.border = "2px solid red";
      }
    }
    for (let i = 0; i < nodeList.length; i++) {
      if (String(nodeList[i].computedStyleMap().get('border-color')) === "rgb(255, 0, 0)") {
        console.log(String(nodeList[i].computedStyleMap().get('border-color')));
        return false;
      }
    }
    return true;
  }
</script>

<?php 
 //session_start();
require 'config.php';
require_once 'vendor/autoload.php';
// init configuration
$clientID = '945354833000-tld8abp352tt4q4a3i4cunbf3n9ajb9j.apps.googleusercontent.com';
$clientSecret = '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';
$redirectUri = 'http://localhost/phpZadanie1/registration.php';

// Create a new Google_Client object
$client = new Google_Client();
$client->setClientId($clientID);
$client->setClientSecret($clientSecret);
$client->setRedirectUri($redirectUri);
$client->addScope("profile");
$client->addScope("email");

// Create a new Google_Service_Oauth2 object
$service = new Google_Service_Oauth2($client);

// If the user has clicked the "Sign in with Google" button
if (isset($_GET['code'])) {

 $token = $client->fetchAccessTokenWithAuthCode($_GET['code']); // Exchange authorization 
  $_SESSION['access_token'] = $client->getAccessToken(); // Store the access token in the session
    $userInfo = $service->userinfo->get();


   $query = $db->prepare("SELECT * FROM tb_user WHERE email = ?");
   $query->execute([$userInfo['email']]);

    if ($query->rowCount() <= 0) {
       $sql = "INSERT INTO tb_user(name, surname, email, password) VALUES (?,?,?,?)";
    $stmt = $db->prepare($sql);
    $success = $stmt->execute([$userInfo['given_name'],$userInfo['family_name'],$userInfo['email'],$userInfo['id']]);

    $sql = "SELECT * FROM tb_user WHERE email=?";
    $stmt = $db->prepare($sql);
    $stmt->execute([$userInfo['email']]);
    $results = $stmt->fetchAll(PDO::FETCH_ASSOC);
    $value = $results[0]['id'];

    $sql = "INSERT INTO login_attr(user_id, login_type) VALUES (?,?)";
    $stmt = $db->prepare($sql);
    $success = $stmt->execute([$value, 'google_login']);
     }
     else{
       while ($row = $query->fetch(PDO::FETCH_ASSOC)) {
        $value = $row['id'];
    }
     }

   

//  header('Location: f2A.php');
}

// If the access token is already stored in the session
if (isset($_SESSION['access_token']) && $_SESSION['access_token']) {
  $client->setAccessToken($_SESSION['access_token']);
  $userInfo = $service->userinfo->get(); // Get the user's basic profile information

    // echo $value;
    // echo implode(" ",$_SESSION['access_token']);
       $_SESSION["login"] = true;
       $_SESSION["id"] = $value;
       
  
   //$client->revokeToken();

 unset($_SESSION['access_token']);
header('Location: 2fA.php');
} else {
  // Generate a URL to request access from the user
  $authUrl = $client->createAuthUrl();
  echo "<div class='text-center '><a href='$authUrl' class= 'text-dark'>Sign in with Google</a> </div>";
}
 ?>


 

</body>
</html>