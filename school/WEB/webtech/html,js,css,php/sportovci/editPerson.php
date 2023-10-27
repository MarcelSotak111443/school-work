<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title></title>
	<script type="text/javascript" src="myscript.js"></script>
	<link rel="stylesheet" type="text/css" href="index.css">
	<link rel="stylesheet" href="css/bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="index.css">
	<link rel="stylesheet" type="text/css" href="https://cdn.datatables.net/1.10.24/css/jquery.dataTables.min.css">
<script type="text/javascript" src="https://cdn.datatables.net/1.10.24/js/jquery.dataTables.min.js"></script>

	<!-- Bootstrap JavaScript -->
	<script src="js/bootstrap.min.js"></script>
	<script type="text/javascript">
		  $(document).ready(function() {
        $('#placementsTable').DataTable();
    });

	</script>

</head>
<body>



<div class="float-left"><button class="btn btn-warning"><a class= 'text-dark' href="premiumPage.php">Home</a></button></div>

	<?php 
//if ($_SESSION['qr']==null) {
//	header("Location: login.php");
//}
	session_start();
	require 'config.php';

	$stmt = $db->prepare("SELECT * FROM person WHERE id = ? LIMIT 1");
	$stmt->execute(array($_GET['id']));
	$person = $stmt->fetch(PDO::FETCH_ASSOC);


	if(!empty($_POST) && !empty($_POST['name'])){
    //var_dump($_POST);
		
		$sql = "UPDATE person SET name=?, surname=?, birth_day=?, birth_place=?, birth_country=? WHERE id=?";
		$stmt = $db->prepare($sql);
		$result = $stmt->execute([$_POST['name'], $_POST['surname'], $_POST['birth_day'], $_POST['birth_place'], $_POST['birth_country'], intval($_POST['person_id']) ]);
       
       
		if ($result) {
			if ($stmt->rowCount() > 0) {
            // Delete successful, display alert message
				echo "<script>alert('update successful!');</script>";


				  $stmt = $db->prepare("SELECT * FROM person WHERE name = ?");
	              $stmt->execute([$_POST['name']]);
	              $person = $stmt->fetch(PDO::FETCH_ASSOC);


				  $currentDateTime = date('Y-m-d H:i:s');
		          $sql = "INSERT INTO operations (id, operation, tableName, rowName, time) VALUES (?,?,?,?,?)";
		          $stmt = $db->prepare($sql);
		          $success = $stmt->execute([$person['id'],"UPDATE","PERSON",$person['id'],$currentDateTime]);
				
			} else {
            // Delete failed
				echo "<script>alert('Update failed! No rows were affected.');</script>";
			}
		} else {
        // Error executing query
			echo "<script>alert('Error executing delete query: " . $stmt->errorInfo()[2] . "');</script>";
		}

		

		

	}
	$stmt = $db->prepare("SELECT * FROM person WHERE id = ? LIMIT 1");
	$stmt->execute(array($_GET['id']));
	$person = $stmt->fetch(PDO::FETCH_ASSOC);
	


	$query = "select placement.*, game.city from placement join game on placement.game_id = game.id where placement.person_id=?";
	$stmt = $db->prepare($query);
	$stmt->execute([$_GET['id']]);
	$placements = $stmt->fetchAll(PDO::FETCH_ASSOC);

	if(isset($_POST['del_placement_id'])){
		$sql = "DELETE FROM placement WHERE id=?";
		$stmt = $db->prepare($sql);
		$result = $stmt->execute([intval($_POST['del_placement_id'])]);

		if ($result) {
			if ($stmt->rowCount() > 0) {
            // Delete successful, display alert message
				echo "<script>alert('Delete successful!');</script>";
			} else {
            // Delete failed
				echo "<script>alert('Delete failed! No rows were affected.');</script>";
			}
		} else {
        // Error executing query
			echo "<script>alert('Error executing delete query: " . $stmt->errorInfo()[2] . "');</script>";
		}


		$inserted_id = $db->lastInsertId();

		$currentDateTime = date('Y-m-d H:i:s');
		$sql = "INSERT INTO operations (id, operation, tableName, rowName, time) VALUES (?,?,?,?,?)";
		$stmt = $db->prepare($sql);
		$success = $stmt->execute([$person['id'],"DELETE","PLACEMENT",$_POST['del_placement_id'],$currentDateTime]);
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
    <h1>EDIT PERSON</h1>

    <input type="hidden" name="person_id" id="person_id" value="<?php echo $person['id']; ?>"><br>

    <div class="row mb-3">
      <label for="name" class="col-sm-2 col-form-label"><b>NAME:</b></label>
      <div class="col-sm-10">
        <input onBlur="FieldCheck(this)" type="text" name="name" id="name" class="form-control check" value="<?php echo $person['name']; ?>" required value="">
        <div class="warning"></div>
      </div>
    </div>

    <div class="row mb-3">
      <label for="surname" class="col-sm-2 col-form-label"><b>SURNAME:</b></label>
      <div class="col-sm-10">
        <input onBlur="FieldCheck(this)" type="text" name="surname" id="surname" class="form-control check" value="<?php echo $person['surname']; ?>" required value="">
        <div class="warning"></div>
      </div>
    </div>

    <div class="row mb-3">
      <label for="birth_day" class="col-sm-2 col-form-label"><b>BIRTHDAY:</b></label>
      <div class="col-sm-10">
        <input onBlur="FieldCheck(this)" type="text" name="birth_day" class="form-control check" value="<?php echo $person['birth_day']; ?>" id="birth_day">
        <div class="warning"></div>
      </div>
    </div>

    <div class="row mb-3">
      <label for="birth_place" class="col-sm-2 col-form-label"><b>BIRTHPLACE:</b></label>
      <div class="col-sm-10">
        <input onBlur="FieldCheck(this)" type="text" name="birth_place" class="form-control check" value="<?php echo $person['birth_place']; ?>" id="birth_place">
        <div class="warning"></div>
      </div>
    </div>

    <div class="row mb-3">
      <label for="birth_country" class="col-sm-2 col-form-label"><b>BIRTHCOUNTRY:</b></label>
      <div class="col-sm-10">
        <input onBlur="FieldCheck(this)" type="text" name="birth_country" class="form-control check" value="<?php echo $person['birth_country']; ?>" id="birth_country">
        <div class="warning"></div>
      </div>
    </div>

    <div class="row mb-3">
      <div class="col-sm-10 offset-sm-2">
        <button type="submit" name="submit" class="btn btn-warning">EDIT</button>
      </div>
    </div>
  </div>

</form>


	<?php 

	if(isset($_POST['add_placing'])){
		$sql = "SELECT * FROM game WHERE city=?";
		$stmt = $db->prepare($sql);
		$stmt->execute([$_POST['city']]);
		if ($stmt->rowCount() == 0) {

		} else {
    // Row is not empty, retrieve the data
			$row = $stmt->fetch(PDO::FETCH_ASSOC);
			$id = $row['id'];
			
			$sql = "INSERT INTO placement(person_id, game_id, placing, discipline) VALUES (?,?,?,?)";
			$stmt = $db->prepare($sql);
			$result = $stmt->execute([$person['id'], $id, $_POST['placing'], $_POST['discipline']]);

			if ($result) {
				if ($stmt->rowCount() > 0) {
            // Delete successful, display alert message
					echo "<script>alert('Insert successful!');</script>";
				} else {
            // Delete failed
					echo "<script>alert('Insert failed! No rows were affected.');</script>";
				}
			} else {
        // Error executing query
				echo "<script>alert('Error executing delete query: " . $stmt->errorInfo()[2] . "');</script>";
			}

			$inserted_id = $db->lastInsertId();

			$currentDateTime = date('Y-m-d H:i:s');
			$sql = "INSERT INTO operations (id, operation, tableName, rowName, time) VALUES (?,?,?,?,?)";
			$stmt = $db->prepare($sql);
			$success = $stmt->execute([$person['id'],"INSERT","PLACEMENT",$inserted_id,$currentDateTime]);

		}
	}


	$query = "select placement.*, game.city from placement join game on placement.game_id = game.id where placement.person_id=?";
	$stmt = $db->prepare($query);
	$stmt->execute([$_GET['id']]);
	$placements = $stmt->fetchAll(PDO::FETCH_ASSOC);



	?>


<form action="#" method="post" autocomplete="off" onsubmit="return validateForm()">
  <div class="container">
    <h1>ADD RECORD</h1>

    <div class="form-group">
      <label for="placing"><b>PLACING:</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="placing" id="placing" class="form-control" required>
      <div class="warning"></div>
    </div>

    <div class="form-group">
      <label for="discipline"><b>DISCIPLINE:</b></label>
      <input onBlur="FieldCheck(this)" type="text" name="discipline" id="discipline" class="form-control" required>
      <div class="warning"></div>
    </div>

  <div class="form-group">
    <label for="city"><b>CITY:</b></label>
    <select name="city" id="city" class="form-control" required>
    <option value="">Select a city</option>
    <?php
        $stmt = $db->prepare("SELECT * FROM game");
        $stmt->execute();
        $games = $stmt->fetchAll(PDO::FETCH_ASSOC);

        foreach ($games as $game) { ?>
            <option value="<?php echo $game['city']; ?>"><?php echo $game['city']; ?></option>
        <?php } ?>
</select>
    <div class="warning"></div>
</div>

    <button type="submit" name="add_placing" class="btn btn-warning">ADD</button>
  </div>

  
</form>


<div class="container" style="width: 80%;">
    <h2>Placing</h2>
    <table id="placementsTable" class="table">
        <thead>
            <tr>
                <th>Placing</th>
                <th>Discipline</th>
                <th>OH</th>
                <th>Action</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($placements as $placement) { ?>
                <tr>
                    <td><?php echo $placement['placing']; ?></td>
                    <td><?php echo $placement['discipline']; ?></td>
                    <td><?php echo $placement['city']; ?></td>
                    <td>
                        <form action="#" method="post">
                            <input type="hidden" name="del_placement_id" value="<?php echo $placement['id']; ?>">
                            <button type="submit" class="btn btn-warning">Delete</button>
                        </form>
                    </td>
                </tr>
            <?php } ?>
        </tbody>
    </table>
</div>

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






</body>
</html>