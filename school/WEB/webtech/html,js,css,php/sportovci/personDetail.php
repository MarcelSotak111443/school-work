<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title></title>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.3/jquery.min.js"></script>
    <link rel="stylesheet" type="text/css" href="index.css">
     <link rel="stylesheet" href="css/bootstrap.min.css">

<!-- Bootstrap JavaScript -->
<script src="js/bootstrap.min.js"></script>
  <link rel="stylesheet" type="text/css" href="//cdn.datatables.net/1.13.2/css/jquery.dataTables.min.css">
  <script type="text/javascript" src="//cdn.datatables.net/1.13.2/js/jquery.dataTables.min.js"></script>
  <script type="text/javascript">
    $(document).ready(function(){
      $('#dataTable3').dataTable();
    })

  </script>
</head>
<body>



<button class="btn btn-warning float-left"><a href="index.php">BACK</a>
</button>


<?php  
include('config.php');

$sql = "SELECT * 
FROM placement as p
JOIN game ON p.game_id = game.id
JOIN person ON person.id = p.person_id
WHERE person.id = ".$_GET['id']."
ORDER BY name";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
 
  $array =  "<table id='dataTable3'><thead><tr><th>MENO</th><th>PRIEZVISKO</th><th>UMIESTNENIE</th><th>DISCIPLINA</th><th>YEAR</th></tr><tbody>";

  while($row = $result->fetch_assoc()) {
   
 
      $array .= "<tr><td>".$row["name"]."</td><td>".$row["surname"]."</td><td>".$row["placing"]."</td><td>".$row["discipline"]."</td><td>".$row["year"]."</td></tr>";
  
  }
  echo "</tbody></table>";
} else {
  echo "0 results";
}

$conn->close();

echo $array;


 ?>
</body>
</html>

