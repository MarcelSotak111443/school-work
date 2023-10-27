<!DOCTYPE html>
<html>
<head>
   <meta charset="UTF-8"> 
    <title>WebSocket Client Example</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
	<script src="https://ajax.aspnetcdn.com/ajax/jquery/jquery-3.6.0.js"></script>
	<style>
	    .container-fluid {
	        min-height: 100vh;
	        display: flex;
	        align-items: flex-end;
	    }

	    #username-form {
	        margin-bottom: 50px;
	    }
	</style>
</head>
<body class="bg-light">

<div class="container-fluid d-flex justify-content-center align-items-center vh-100">
  <form id="username-form" method="post" action="" class="col-sm-6 col-md-4 col-lg-3 bg-white p-4 text-center">
    <div class="form-group mb-3 text-center">
      <label for="username">Username</label>
      <input type="text" class="form-control" name="username" id="username" required>
    </div>
    <button type="submit" class="btn btn-warning" name="submit">Submit</button>
  </form>
</div>

	<?php 
	session_start();
	$_SESSION['loginVisited'] = false;
	if (isset($_POST['submit'])) {
		$_SESSION['loginVisited'] = true;
		header("Location: index.php?username=" . str_replace('+', '%20', urlencode($_POST['username'])));

		exit();
	}
	?>
	
	<?php
	$warning = $_GET['warning'] ?? null;
	if ($warning === 'full') {
	    echo '<div class="alert alert-danger text-center" role="alert">The server is full. Please try again later.</div>';
	}
	?>

	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
</body>
</html>
