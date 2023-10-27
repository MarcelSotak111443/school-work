
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title></title>
</head>
<body>


<?php  
require 'config.php';
if(isset($_POST["submit"])){
  $password = $_POST["name"];

   $hash = password_hash($password, PASSWORD_BCRYPT);
   echo $hash ."<br>";

    $sql = "INSERT INTO tb_user(name,  password) VALUES (?,?)";
    $stmt = $db->prepare($sql);
    $success = $stmt->execute(["hm",$hash]);


  $stmt = $db->prepare("SELECT * FROM tb_user WHERE name = 'hm'");
  $stmt->execute();
  $row = $stmt->fetch(PDO::FETCH_ASSOC);
  if ($row) {
    echo  $row['password']."<br>";
    $verify = password_verify($password, $row['password']);
    echo $verify ."what <br>";}
}
?>

<form action="#" method="post" autocomplete="off" >
  <div class="container">
    <h1>Register</h1>

    <label for="name"><b>heslo:</b> </label>
    <input  type="text" name="name" id="name" class="check" required value=""> <br>
   

    <button type="submit" name="submit" class="registerbtn">Register</button>
  </div>

  
</form>
</body>
</html>
