<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ZOZNAMY</title>
     <script type="text/javascript" src="myscript.js"></script>
        <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>


<link rel="stylesheet" type="text/css" href="index.css">
<!-- Bootstrap JavaScript -->
<script src="js/bootstrap.min.js"></script>
<script type="text/javascript" src="//cdn.datatables.net/1.13.2/js/jquery.dataTables.min.js"></script>
  <script type="text/javascript">
   
$(document).ready(function() {
        $('#personTable').DataTable();
    });

  </script>

</head>
<body>


<div class="float-left"><button class="btn btn-warning"><a class= 'text-dark' href="index.php">Home</a></button></div>


<?php 

session_start();



if ($_SESSION['login']==false) {
    header("Location: login.php");
}
require 'config.php';
$sql = "SELECT * FROM tb_user WHERE id = ?";
$stmt = $db->prepare($sql);
$success = $stmt->execute([$_SESSION['id']] );
$row = $stmt->fetch();
$_SESSION['name'] = $row["name"];
$_SESSION['surname'] = $row["surname"];

if(!empty($_POST) && !empty($_POST['name'])){
    //var_dump($_POST);
    $sql = "INSERT INTO person (name, surname, birth_day, birth_place, birth_country) VALUES (?,?,?,?,?)";
    $stmt = $db->prepare($sql);
    $result = $stmt->execute([$_POST['name'], $_POST['surname'], $_POST['birth_day'], $_POST['birth_place'], $_POST['birth_country']]);

    if ($result) {
        if ($stmt->rowCount() > 0) {
            // Delete successful, display alert message
            echo "<script>alert('insert successful!');</script>";
        } else {
            // Delete failed
            echo "<script>alert('insert failed! No rows were affected.');</script>";
        }
    } else {
        // Error executing query
        echo "<script>alert('Error executing delete query: " . $stmt->errorInfo()[2] . "');</script>";
    }
    $id = $db->lastInsertId();

    $currentDateTime = date('Y-m-d H:i:s');

    $sql = "INSERT INTO operations (id, operation, tableName, rowName, time) VALUES (?,?,?,?,?)";
    $stmt = $db->prepare($sql);
    $success = $stmt->execute([$_SESSION['id'],"INSERT","PERSON",$id,$currentDateTime]);
}
 if(isset($_POST['del_placement_id'])){
        $sql = "DELETE FROM person WHERE id=?";
        $stmt = $db->prepare($sql);
        $result = $stmt->execute([intval($_POST['del_placement_id'])]);

        if ($result) {
        if ($stmt->rowCount() > 0) {
            // Delete successful, display alert message
            echo "<script>alert('delete successful!');</script>";
        } else {
            // Delete failed
            echo "<script>alert('delete failed! No rows were affected.');</script>";
        }
        } else {
        // Error executing query
        echo "<script>alert('Error executing delete query: " . $stmt->errorInfo()[2] . "');</script>";
        }


$currentDateTime = date('Y-m-d H:i:s');
         $sql = "INSERT INTO operations (id, operation, tableName, rowName, time) VALUES (?,?,?,?,?)";
         $stmt = $db->prepare($sql);
         $success = $stmt->execute([$_SESSION['id'],"DELETE","PERSON",$_POST['del_placement_id'],$currentDateTime]);
    }

 ?>

      
  



<form action="logout.php" method="post" autocomplete="off">
  <div class="container-loginInfo">
    <div class="priemiumPageLoginWindow">
        <div class="text-center"><?php echo $_SESSION['name']; ?></div>
        <div class="text-center"><?php echo $_SESSION['surname']; ?></div>
      </div>

    <button type="submit" name="submit" class="btn btn-warning mx-auto d-block">Logout</button>
  </div>
</form>



<form action="#" method="post" autocomplete="off" onsubmit="return validateForm()">
  <div class="container">
    <h1 class="text-center">Add person</h1>

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
      <label for="birth_day"><b>BIRTHDAY:</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="birth_day" class="form-control check" id="birth_day">
      <div class="warning"></div>
    </div>

    <div class="form-group">
      <label for="birth_place"><b>BIRTHPLACE:</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="birth_place" class="form-control check" id="birth_place">
      <div class="warning"></div>
    </div>

    <div class="form-group">
      <label for="birth_country"><b>BIRTHCOUNTRY:</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="birth_country" class="form-control check" id="birth_country">
      <div class="warning"></div>
    </div>

    <div class="text-center">
      <button type="submit" name="submit" class="btn btn-warning">ADD</button>
    </div>
  </div>

  
</form>

<script>
    function validateForm() {
      console.log("working");
    const nodeList = document.querySelectorAll(".check");
    for (let i = 0; i < nodeList.length; i++) {
     
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
<div style="margin: 0 auto; width: 60%;">
    <?php
    include('config.php');

    $stmt = $db->prepare("SELECT * FROM person");
    $stmt->execute();
    $result = $stmt->fetchAll();

    if (count($result) > 0) {
        echo "<table id='personTable' class='table table-striped'><thead><tr><th>NAME</th><th>SURNAME</th><th>BIRTHDATE</th><th>ACTION</th></tr></thead><tbody>";

        foreach($result as $row) {
            echo '<tr><td><a href="editPerson.php?id='.$row["id"].'">'.$row["name"].'</a></td><td>'.$row["surname"].'</td><td>'.$row["birth_day"].'</td><td><form action="#" method="post"><input type="hidden" name="del_placement_id" value=' . $row['id'] . '><button type="submit" class="btn btn-danger">DELETE</button></form></td></tr>';
        }
        echo '</tbody></table>';
    } else {
        echo "0 results";
    }

    $conn = null;
?>
 </div>

</body>
</html>