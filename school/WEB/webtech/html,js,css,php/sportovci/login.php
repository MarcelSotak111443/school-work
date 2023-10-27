

<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <link rel="stylesheet" type="text/css" href="index.css">
    <script type="text/javascript" src="myscript.js"></script>

<!-- Bootstrap JavaScript -->
<script src="js/bootstrap.min.js"></script>
  <title></title>
</head>
<body>


<?php
session_start();
require 'config.php';

if(isset($_POST["submit"])){
  
  $email = $_POST["email"];
  $password = $_POST["password"];
  $stmt = $db->prepare("SELECT * FROM tb_user WHERE email = ?");
  $stmt->execute([$email]);
  $row = $stmt->fetch(PDO::FETCH_ASSOC);

  if ($row) {
    
    $verify = password_verify($password, $row['password']);

    if($verify){
       $_SESSION["login"] = true;
       $_SESSION["id"] = $row["id"];
     
       
        header("Location: 2fA.php");
      
    }
    else{
      echo $password;
      echo $row['password'];  
          
    "<script> console.log('nejde'); </script>";
    }
  }
  else{
   
    echo
    "<script> alert('neregistrovaný'); </script>";
  }
}
?>
<nav class="navbar navbar-expand-lg navbar-light bg-light">
 
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

 <form action="login.php" method="post" autocomplete="off" onsubmit="return validateForm()">
  <div class="container">
    <h1 class="text-center">Login</h1>

    <div class="form-group">
      <label for="name"><b>EMAIL</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="email" id="email" class="form-control check" required value="">
      <div class="warning"></div>
    </div>

    <div class="form-group">
      <label for="psw"><b>PASSWORD:</b></label>
      <input onBlur="FieldCheck(this)" type="password" name="password" id="password" class="form-control check" required>
      <div class="warning"></div>
    </div>

    <button type="submit" name="submit" class="btn btn-warning mx-auto d-block">Login</button>
  </div>

   <div class="text-center">
     <a href="registration.php"  class= 'text-dark'>Register</a>
   </div>

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




    
</body>
</html>
