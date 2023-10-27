<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
   <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
     <link rel="stylesheet" type="text/css" href="index.css">


<!-- Bootstrap JavaScript -->
<script src="js/bootstrap.min.js"></script>
  <title></title>
</head>
<body>



<?php 




session_start();
require 'config.php';
if ($_SESSION["login"] != true) {
 header("Location: login.php");
}


require 'config.php';

 $exist = $db->prepare("SELECT qr, name FROM tb_user WHERE id = ?");
$exist->execute([$_SESSION['id']]);

if ($exist->rowCount() > 0){
    while($row = $exist->fetch(PDO::FETCH_ASSOC)) {
        
        if ($row['qr']!=null) {
            $randomString = strval($row['qr']);
        }
    
      else{
      
    $characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $charactersLength = strlen($characters);
    $randomString = '';
    for ($i = 0; $i < 10; $i++) {
        $randomString .= $characters[random_int(0, $charactersLength - 1)];
     }
       

      $stmt = $conn->prepare("UPDATE tb_user SET qr = ? WHERE id = ?");
      $stmt->bind_param("ss", $randomString, $_SESSION['id']);
      $stmt->execute();

     $conn->close();
      }
     }
  }


require_once 'vendor/autoload.php';
$secret =  $randomString;



$qr = \Sonata\GoogleAuthenticator\GoogleQrUrl::generate('diskretnaZona', $secret, 'diskretnaZona');

if (isset($_POST['submit'])) {
  $code = $_POST['pass-code'];
  $g = new \Sonata\GoogleAuthenticator\GoogleAuthenticator();
  if ($g->checkCode($secret, $code)) {
   

   $currentDate = date('Y-m-d');
$currentTime = date('H:i:s');

$sql = "UPDATE login_attr SET date = ?, time = ? WHERE user_id = ?";
$stmt = $db->prepare($sql);
$success = $stmt->execute([$currentDate, $currentTime, $_SESSION['id']]);

$_SESSION['qr'] = true;
    header("Location: premiumPage.php");
} else {
    
}

}
 ?><nav class="navbar navbar-expand-lg navbar-light bg-light">
 
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

<div class="container text-center">
  <div class="row justify-content-center">
    <div class="col-md-6">
      <img src="<?=$qr?>" class="img-fluid" style="margin: 20px">
      <form action="" method="post">
        <div class="form-group">
          <label for="pass-code">Pass Code:</label>
          <input type="text" name="pass-code" id="pass-code" class="form-control">
        </div>
        <button type="submit" name="submit" class="btn btn-warning">Submit</button>
      </form>
    </div>
  </div>
</div>



</body>
</html>