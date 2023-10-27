


<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Main</title>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.3/jquery.min.js"></script>
  <link rel="stylesheet" type="text/css" href="//cdn.datatables.net/1.13.2/css/jquery.dataTables.min.css">
  <link rel="stylesheet" type="text/css" href="index.css">
  <link rel="stylesheet" href="css/bootstrap.min.css">

<!-- Bootstrap JavaScript -->
<script src="js/bootstrap.min.js"></script>

<link rel="stylesheet" type="text/css" href="index.css">
  <script type="text/javascript" src="//cdn.datatables.net/1.13.2/js/jquery.dataTables.min.js"></script>
  <script type="text/javascript">
    $(document).ready(function(){
      var table = $('#myTable').DataTable();

  // Get the first column's header element
  var col1Header = table.column(0).header();

  // Remove the sorting classes from the header element
  $(col1Header).removeClass('sorting').removeClass('sorting_asc');
      $('#dataTable1').dataTable({
        "ordering": false,
        
      });
      $('#dataTable2').dataTable();
    });



  </script>

</head>
<body>
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







  


  <?php

  if (isset($_GET['order'])) {
   
    $_SESSION["isOrder"] = $_GET['order'];
    $_SESSION["order"]  = "ORDER BY ".$_GET['order'];
  }
  else{

    $_SESSION["order"] = ""; 
    $_SESSION["isOrder"]= "";
  }
  if (isset($_GET['secondOrder'])) {
    $_SESSION["secondOrder"] = ",".$_GET['secondOrder'];

  }
  else{
    $_SESSION["secondOrder"] = ""; 

  }

  $sql = "SELECT person.id ,person.name , person.surname ,game.city, game.year , game.type , p.discipline
  FROM placement as p
  JOIN game ON p.game_id = game.id
  JOIN person ON person.id = p.person_id
  ".$_SESSION["order"].$_SESSION['secondOrder']."
  ";



?>
<h1 class="text-center">TABLE OF ATHLETES</h1>
<?php

tryThis($sql);

  $sql = "SELECT * ,COUNT(placing) as prices
  FROM placement as p
  JOIN game ON p.game_id = game.id
  JOIN person ON person.id = p.person_id
  
  GROUP BY placing,name,surname 
  ORDER BY prices DESC,name ASC LIMIT 10;";

  ?>
<h1 class="text-center">TOP 10 ATHLETES</h1>
<?php
  SQL_command_second_table($sql);


 function SQL_command_first_table($SQL_command) {
    include('config.php');
    $stmt = $db->prepare($SQL_command);
    $stmt->execute();
    $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);
    $array = "<table id='dataTable1'><thead><tr>
        <th><a href='index.php?order=name";
    $array .= "'>MENO</th>
        <th><a href='index.php?order=surname'>PRIEZVISKO</th>
        <th><a href='index.php?order=city'>MESTO</th>
        <th><a href='index.php?order=year'>ROK</th>
        <th><a href='index.php?order=".$_SESSION['isOrder']."&secondOrder=year'>TYP</th>
        <th><a href='index.php?order=discipline'>DISCIPLINA</th>
        </tr></thead><tbody>";
    foreach ($rows as $row) {
        $array .= "<tr><td>".$row["name"]."</td><td>".$row["surname"]."</td><td>".$row["city"]."</td><td>".$row["year"]."</td><td>".$row["type"]."</td><td>".$row["discipline"]."</td></tr>";
    }
    echo $array."</tbody></table>";
    $conn = null;
}
function tryThis($SQL_command) {
include('config.php');
     $stmt = $db->prepare($SQL_command);
    $stmt->execute();
    $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);
    
$array = "<table id='dataTable1'><thead><tr>
        <th><a href='index.php?order=name";
    $array .= "'>MENO</th>
        <th><a href='index.php?order=surname'>PRIEZVISKO</th>
        <th><a href='index.php?order=city'>MESTO</th>
        <th><a href='index.php?order=year'>ROK</th>
        <th><a href='index.php?order=".$_SESSION['isOrder']."&secondOrder=year'>TYP</th>
        <th><a href='index.php?order=discipline'>DISCIPLINA</th>
        </tr></thead><tbody>";



  foreach ($rows as $row) {
   
       $array .= "<tr><td><a href='personDetail.php?id=".$row['id']."'>".$row["name"]."</td><td>".$row["surname"]."</td><td>".$row["city"]."</td><td>".$row["year"]."</td><td>".$row["type"]."</td><td>".$row["discipline"]."</td></tr>";
    }
  echo $array."</tbody></table>";

}

function SQL_command_second_table($SQL_command) {
  include('config.php');
  $sql = $SQL_command;

  $result = $conn->query($SQL_command);

  if ($result->num_rows > 0) {

    $array =  "<table id='dataTable2'><thead><tr><th>MENO</th><th>PRIEZVISKO</th><th>MEDAILE</th></tr></thead><tbody>";

    while($row = $result->fetch_assoc()) {


     $array .= "  <tr> <td><a href='personDetail.php?id=".$row['person_id']."'>".$row["name"]."</a></td><td><a href='personDetail.php?id=".$row['person_id']."'>".$row["surname"]."</a></td>  <td><a href='personDetail.php?id=".$row['person_id']."'>".$row["prices"]."</a></td></tr>";
   }
   echo "</tbody></table>";
 } else {
  echo "0 results";
}

$conn->close();

echo $array;
}

?>

</script>


</body>
</html>