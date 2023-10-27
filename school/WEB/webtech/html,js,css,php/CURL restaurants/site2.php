<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="css/bootstrap.min.css">
	<script src="js/jquery.min.js"></script>
  <script src="js/bootstrap.min.js"></script>
	<title>	</title>
</head>
<body>


	<nav class="navbar navbar-expand-lg navbar-dark bg-dark">
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>
  <div class="collapse navbar-collapse" id="navbarNav">
    <ul class="navbar-nav">
      <li class="nav-item">
        <a class="nav-link" href="index.php">MENU</a>
      </li>
      <li class="nav-item active">
        <a class="nav-link" href="site2.php">API</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="https://documenter.getpostman.com/view/20814404/2s93XvWkEU#53836c40-da62-4dba-8ac8-541260b3a070">API-POPIS</a>
      </li>
    </ul>
  </div>
</nav>


<div class="container">
  <div class="row justify-content-center">
    <div class="col-md-6">
      <form method="post">
        <div class="text-center mb-3">
          <button type="submit" name="download" class="btn btn-dark m-2">STIAHNI</button>
          <button type="submit" name="parse" class="btn btn-dark m-2">PARSUJ</button>
          <button type="submit" name="delete" class="btn btn-dark m-2">VYMAZ</button>
        </div>
      </form>
    </div>
  </div>
</div>

</body>





<?php
include('php/simple_html_dom.php');

if(array_key_exists('download', $_POST)) {
	download();
}
else if(array_key_exists('parse', $_POST)) {
	parse();
}
else if(array_key_exists('delete', $_POST)) {
	delete();
}


function download() {

	$curl_handle = curl_init();

    // set options for the curl handle
	curl_setopt($curl_handle, CURLOPT_RETURNTRANSFER, true);

    // array of URLs to request
	$urls = array(
		'http://eatandmeet.sk/',
		'https://www.novavenza.sk/tyzdenne-menu',
		'http://www.freefood.sk/menu/',
	);

    // array to store the content
	$content_array = array();

    // loop through the URLs and fetch the content
	foreach ($urls as $url) {
        // set the URL for the curl handle
		curl_setopt($curl_handle, CURLOPT_URL, $url);

        // execute the curl handle and get the content
		$content = curl_exec($curl_handle);

        // parse the HTML content using the Simple HTML DOM Parser library
		$html = str_get_html($content);

        // store the parsed content in the array
		$content_array[] = $html;
	}

    // concatenate the text content of all URLs into a single string
	$text = "";
	foreach ($content_array as $content) {
		$text .= $content->outertext;
	}
    // close the curl handle
	curl_close($curl_handle);

    // prepare and execute a SQL statement to insert the content into the database
	include 'config.php';
	$sql = "INSERT INTO sitecontext (creation_date, sites_text) VALUES (?,?)";
	$stmt = $db->prepare($sql);
	$date = date("Y-m-d");
	$result = $stmt->execute([$date, $text]);

}



function parse() {
ini_set('display_errors', 1); error_reporting(E_ALL);
	include 'config.php';
	$exist = false;
	$stmt = $db->prepare("SELECT * FROM sitecontext ORDER BY id DESC LIMIT 1");
	$stmt->execute();
ini_set('display_errors', 1); error_reporting(E_ALL);
    // Check if there is a result
	if ($stmt->rowCount() > 0) {
    $row = $stmt->fetch(PDO::FETCH_ASSOC); // Fetch the last row
    $lastID = $row['id'];
    $date = $row['creation_date'];
ini_set('display_errors', 1); error_reporting(E_ALL);
    $html = new simple_html_dom();
    $html->load($row['sites_text']);


    $menu_items = array();
    $dayCounter = 0;
    $day = " ";

    $element = $html->find('.menu-title h2');
     
     if ($element != null) {
      $dayCounter=+ 9;
   }

    foreach($html->find('.menu-body') as $menu_item) {

   

    	switch ((int) ($dayCounter / 9)) {
    		case 0:
    		$day = "Monday";
    		break;
    		case 1:
    		$day = "Tuesday";
    		break;
    		case 2:
    		$day = "Wednesday";
    		break;
    		case 3:
    		$day = "Thursday";
    		break;
    		case 4:
    		$day = "Friday";
    		break;
    		case 5:
    		$day = "Saturday";
    		break;
    		case 6:
    		$day = "Sunday";
    		break;
    		default:
    		$day = "Monday";

    		$dayCounter = 0;

    		break;
    	}
    

    	if ($menu_item->find('.menu-title h4', 0) != null) {
    			$dayCounter ++;

    		$menu_title = $menu_item->find('.menu-title h4', 0)->plaintext;
    		if ($menu_item->find('.price', 0) != null) {


    			$menu_price = $menu_item->find('.price', 0)->plaintext;

    			if ($menu_item->find('.menu-description p.desc', 0) != null) {
    				$menu_description = $menu_item->find('.menu-description p.desc', 0)->plaintext;
    				$image_url = $menu_item->find('.img-responsive', 0)->src;
    				$image_data = file_get_contents($image_url);


    				$menu_items[] = array(
    					'title' => $menu_title,
    					'price' => $menu_price,
    					'description' => $menu_description,
    					'image' => $image_data,
    					'day' => $day
    				);
    			}
    		}}
    	}
    	$stmt = $db->prepare("SELECT * FROM site_parsed WHERE id_site_context = ?");
    	$stmt->execute([$lastID]);
    	$rows = $stmt->fetchAll();
    	if (count($rows) > 0) {
    		$exist = true;
    	}


    	if (true) {
    		foreach ($menu_items as $item) {


    			include 'config.php';
    			$sql = "INSERT INTO site_parsed(name, price,restaurant,day,image,id_site_context) VALUES (?,?,?,?,?,?)";
    			$stmt = $db->prepare($sql);
    			$date = date("Y-m-d");
    			$day = date("l", strtotime($date));

    			$result = $stmt->execute([ $item['description'],  $item['price'],"EATANDMEET",$item['day'],$item['image'],$lastID]);
 //   echo "Title: " . $item['title'] . "<br>";
//   echo "Price: " . $item['price'] . "<br>";
//    echo "Description: " . $item['description'] . "<br>";
//    echo '<img src="data:image/jpeg;base64,' . base64_encode($item['image']) . '" alt="Image description"><br>';
    		}
    	}


    	$menu_itemsVenza = array();
    	$dayCounter = 10;
    	$day = " ";
    	foreach($html->find('li.d-flex.align-items-start') as $menu_item) {
    		switch ((int) ($dayCounter / 10)) {
    			case 0:
    			$day = "Monday";
    			break;
    			case 1:
    			$day = "Tuesday";
    			break;
    			case 2:
    			$day = "Wednesday";
    			break;
    			case 3:
    			$day = "Thursday";
    			break;
    			case 4:
    			$day = "Friday";
    			break;
    			case 5:
    			$day = "Saturday";
    			break;
    			case 6:
    			$day = "Sunday";
    			break;
    			default:
    			$day = "Monday";

    			$dayCounter = 0;

    			break;
    		}
    		$dayCounter ++;

    		($menu_title = $menu_item->find('.leftbar', 0)->plaintext);

    		$menu_price = $menu_item->find('.rightbar', 0)->plaintext;
    		$image_data = file_get_contents($image_url);

    		$menu_itemsVenza[] = array(
    			'title' => $menu_title,
    			'price' => $menu_price,
    			'day' => $day

    		);
    	}


    	if (true) {
    		foreach ($menu_itemsVenza as $item) {
    			include 'config.php';
    			$sql = "INSERT INTO site_parsed(name, price, restaurant, day, image, id_site_context) VALUES (?, ?, ?, ?, ?, ?)";
    			$stmt = $db->prepare($sql);
    			$date = date("Y-m-d");
    			$day = date("l", strtotime($date));
    $name = preg_replace('/[\x00-\x1F\x7F]/u', '', trim(trim($item['title']), "\n")); // remove non-printable characters, end-of-line characters, and leading/trailing whitespace from name
    $price = trim(trim($item['price']), "\n"); // remove end-of-line characters and leading/trailing whitespace from price
    if (!empty($name) && !empty($price)) {
    	$result = $stmt->execute([$name, $price, "VENZA", $item['day'], NULL, $lastID]);
  //      echo "Title: " . $name . "<br>";
  //      echo "Price: " . $price . "<br>";
    }
  }
}









// Parse the HTML code into a DOM object



$menu_items = $html->find('.day-offer li');
$dayCounter = 0;
$day = " ";
// Initialize an array to store the menu items
$items = array();

$free_food_div = $html->find('div#free-food.tab-pane.active.row', 0);




foreach ($html->find('.tab-pane.active .day-offer li') as $item) {
	switch ((int) ($dayCounter / 4)) {
		case 0:
		$day = "Monday";
		break;
		case 1:
		$day = "Tuesday";
		break;
		case 2:
		$day = "Wednesday";
		break;
		case 3:
		$day = "Thursday";
		break;
		case 4:
		$day = "Friday";
		break;
		case 5:
		$day = "Saturday";
		break;
		case 6:
		$day = "Sunday";
		break;
		default:
		$day = "Monday";

		$dayCounter = 0;

		break;
	}
	$dayCounter ++;
    // Extract the name of the menu item
	$name = trim(str_replace($item->find('.brand.price', 0)->plaintext, '', strip_tags($item->innertext)));

	if($name == "1.")
		$dayCounter +=2;


    // Extract the price of the menu item
	$price = trim($item->find('.brand.price', 0)->plaintext);

    // Add the menu item to the array with the appropriate price
	$items[] = array('title' => $name, 'price' => $price, 'day' => $day);
}

// Print the menu items with their names and prices




if (true) {
	foreach ($items as $item) {

		include 'config.php';
		$sql = "INSERT INTO site_parsed(name, price,restaurant,day,image,id_site_context) VALUES (?,?,?,?,?,?)";
		$stmt = $db->prepare($sql);
		$date = date("Y-m-d");
		$day = date("l", strtotime($date));
		$result = $stmt->execute([ $item['title'],  $item['price'],"FREEFOOD",$item['day'],NULL,$lastID]);
  //  echo "Title: " . $item['title'] . "<br>";
  //  echo "Price: " . $item['price'] . "<br>";

	}
}



// clean up the Simple HTML DOM Parser object
$html->clear();
}
}
function delete() {
	include 'config.php';

	$sql = "DELETE FROM site_parsed";
	$stmt = $conn->prepare($sql);

	if ($stmt->execute()) {
		echo "All rows deleted successfully";
	} else {
		echo "Error deleting rows";
	}
	$sql = "DELETE FROM sitecontext";
	$stmt = $conn->prepare($sql);

	if ($stmt->execute()) {
		echo "All rows deleted successfully";
	} else {
		echo "Error deleting rows";
	}

}
?>

<form method="GET" action="">
  <div class="container">
    <div class="row justify-content-center">
      <?php
      $days = array('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday');
      foreach ($days as $day) {
        echo '<div class="col-auto"><button type="button" name="day" value="' . $day . '" onClick="sort(this.value);" class="btn btn-dark mr-2">' . $day . '</button></div>';
      }
      ?>
    </div>
  </div>
</form>

<form id="my-form">
	<div class="container">
	<div class="row justify-content-center">
		<div class="col-md-6">
		
				<div class="form-group">
					<label for="method-select">Method:</label>
					<select class="form-control" name="_method" id="method-select">
						<option value="GET">GET</option>
						<option value="POST">POST</option>
						<option value="PUT">PUT</option>
						<option value="DELETE">DELETE</option>
					</select>
				</div>
			
		</div>
	</div>
</div>

	
	
	
<div class="container">
  <div class="row">
    <div class="col-md-6">
      <div class="form-group">
        <label for="id">ID:</label>
        <input id="id" type="text" name="id"  class="form-control" disabled required>
      </div>
      <div class="form-group">
        <label for="name">Name:</label>
        <input id="name" type="text" name="name" class="form-control" disabled required>
      </div>
    </div>
    <div class="col-md-6">
      <div class="form-group">
        <label for="day">Day:</label>
        <input id="day" type="text" name="day" class="form-control" >
      </div>
      <div class="form-group">
        <label for="price">Price:</label>
        <input id="price" type="text" name="price" class="form-control" disabled required>
      </div>
      <div class="form-group">
        <label for="restaurant">Restaurant:</label>
        <input id="restaurant" type="text" name="restaurant" class="form-control" disabled required>
      </div>
    </div>
  </div>
  <button type="submit" class="btn btn-dark">Submit</button>
</div>








</form>
<script type="text/javascript">
  const methodSelect = document.getElementById('method-select');
  const idInput = document.getElementById('id');
  const dayInput = document.getElementById('day');
  const nameInput = document.getElementById('name');
  const priceInput = document.getElementById('price');
  const restaurantInput = document.getElementById('restaurant');

  methodSelect.addEventListener('change', () => {
    if (methodSelect.value === 'GET') {
      dayInput.disabled = false;
      idInput.disabled = true;
      nameInput.disabled = true;
      priceInput.disabled = true;
      restaurantInput.disabled = true;
    } else if (methodSelect.value === 'PUT') {
      priceInput.disabled = false;
      dayInput.disabled = true;
      idInput.disabled = false;
      nameInput.disabled = true;
      restaurantInput.disabled = true;
    } else if (methodSelect.value === 'POST') {
      nameInput.disabled = false;
      priceInput.disabled = false;
      restaurantInput.disabled = false;
      dayInput.disabled = true;
      idInput.disabled = true;
    } else if (methodSelect.value === 'DELETE') {
      idInput.disabled = false;
      dayInput.disabled = true;
      nameInput.disabled = true;
      priceInput.disabled = true;
      restaurantInput.disabled = true;
    }
  });
</script>


<script>
	document.getElementById('my-form').addEventListener('submit', function(e) {
    e.preventDefault(); // prevent the default form submission

    var jsonData;
    // get the form data
    const formData = new FormData(e.target);

    // call your function here
    myFunction(formData);
  });
  
	function myFunction(formData) {
		const selectElement = document.getElementById('method-select');
		const selectedValue = selectElement.value;
			

		const tableBody = document.getElementById('table-body');
  tableBody.innerHTML = ''; // clear previous content
let url
  if(selectedValue == 'GET')
  	url = 'https://site218.webte.fei.stuba.sk/Z2/api.php';
    const dayInput = document.getElementById('day');
    if(dayInput.value != ""){
    	 url = 'https://site218.webte.fei.stuba.sk/Z2/api.php?day='+ dayInput.value;
    	 console.log(url);
    }
   
 if(selectedValue == 'POST'){
  const nameInput = document.getElementById('name');
  const priceInput = document.getElementById('price');
  const restaurantInput = document.getElementById('restaurant');

 jsonData = JSON.stringify({
  name: nameInput.value,
  price: priceInput.value,
  restaurant: restaurantInput.value
});

  url = 'https://site218.webte.fei.stuba.sk/Z2/api.php?';
}
   


if(selectedValue == 'PUT'){
	const priceInput = document.getElementById('price');
	const idInput = document.getElementById('id');

	jsonData = JSON.stringify({
		
		price: priceInput.value,
		
	});

	url = 'https://site218.webte.fei.stuba.sk/Z2/api.php?id='+idInput.value;
}
  	
  if(selectedValue == 'DELETE'){
const idInput = document.getElementById('id');
  	 url = 'https://site218.webte.fei.stuba.sk/Z2/api.php?id=' +  idInput.value;
  	 jsonData = null;

  }
  	

  // add the method to the URL string


  fetch(url, {
  	method: selectedValue,
  	headers: {
  		'Content-Type':  'application/json'
  	},
  	body: selectedValue === 'GET' ? null :  jsonData // pass null for GET requests
  })
  .then(response => response.json())
  .then(data => {
  	data.forEach(item => {
  		const row = document.createElement('tr');
  		const nameCell = document.createElement('td');
  		nameCell.textContent = item.name;
  		const priceCell = document.createElement('td');
  		priceCell.textContent = item.price;
  		const descriptionCell = document.createElement('td');
  		descriptionCell.textContent = item.restaurant;
  		const dayCell = document.createElement('td');
  		dayCell.textContent = item.day;
  		const imageCell = document.createElement('td');
  		if (item.image) {
  			const image = new Image();
  			image.src = item.image;
  			image.style.width = '20px';
  			imageCell.appendChild(image);
  		}

  		row.appendChild(nameCell);
  		row.appendChild(priceCell);
  		row.appendChild(descriptionCell);
  		row.appendChild(dayCell);
  		row.appendChild(imageCell);
  		tableBody.appendChild(row);
  	});
  })
  .catch(error => console.error(error));
}







</script>




<table class="table">
	<thead>
		<tr>
			<th>Name</th>
			<th>Price</th>
			<th>Restaurnt</th>
			<th>Day</th>
			<th>Image</th>
		</tr>
	</thead>
	<tbody id="table-body">
	</tbody>
</table>

<script type="text/javascript">

	
	

	sort("none");
	function sort(day) {
		day = day.toString();
		const tableBody = document.getElementById('table-body');
  tableBody.innerHTML = ''; // clear previous content

  fetch('http://localhost/phpZadanie2/api.php?type=wow&day=' + day)
  .then(response => response.json())
  .then(data => {
  	data.forEach(item => {
  		const row = document.createElement('tr');
  		const nameCell = document.createElement('td');
  		nameCell.textContent = item.name;
  		const priceCell = document.createElement('td');
  		priceCell.textContent = item.price;
  		const descriptionCell = document.createElement('td');
  		descriptionCell.textContent = item.restaurant;
  		const dayCell = document.createElement('td');
  		dayCell.textContent = item.day;
  		const imageCell = document.createElement('td');
  		if (item.image) {
  			const image = new Image();
  			image.src = item.image;
  			image.style.width = '20px';
  			imageCell.appendChild(image);
  		}

  		row.appendChild(nameCell);
  		row.appendChild(priceCell);
  		row.appendChild(descriptionCell);
  		row.appendChild(dayCell);
  		row.appendChild(imageCell);
  		tableBody.appendChild(row);
  	});
  })
  .catch(error => console.error(error));
}
</script>






</html>