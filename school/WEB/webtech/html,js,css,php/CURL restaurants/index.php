<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>
	
		
	</title>
	<link rel="stylesheet" href="css/bootstrap.min.css">
	<script src="js/jquery.min.js"></script>
  <script src="js/bootstrap.min.js"></script>
</head>
<body>

	<nav class="navbar navbar-expand-lg navbar-dark bg-dark">
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>
  <div class="collapse navbar-collapse" id="navbarNav">
    <ul class="navbar-nav">
      <li class="nav-item active">
        <a class="nav-link" href="index.php">MENU</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="site2.php">API</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="https://documenter.getpostman.com/view/20814404/2s93XvWkEU#53836c40-da62-4dba-8ac8-541260b3a070">API-POPIS</a>
      </li>
    </ul>
  </div>
</nav>




<?php
include('php/simple_html_dom.php');

$url = 'http://eatandmeet.sk/';

// Initialize a new cURL session
$curl = curl_init();

// Set the cURL options
curl_setopt_array($curl, array(
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_URL => $url,
    CURLOPT_FOLLOWLOCATION => true,
    CURLOPT_MAXREDIRS => 10,
    CURLOPT_TIMEOUT => 30,
    CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3'
));
// Execute the cURL request and retrieve the response
$response = curl_exec($curl);

// Close the cURL session
curl_close($curl);


// create a new Simple HTML DOM Parser object and load the HTML from the response
$html = new simple_html_dom();
$html->load($response);

$menu_items = array();

// find all menu items and their details inside the div with class "active"
foreach($html->find('div.active .menu-body') as $menu_item) {
	if ($menu_item->find('.menu-title h4', 0) != null && $menu_item->find('.price', 0) != NULL) {
	$menu_title = $menu_item->find('.menu-title h4', 0)->plaintext;
    $menu_price = $menu_item->find('.price', 0)->plaintext;
    $menu_description = $menu_item->find('.menu-description p.desc', 0)->plaintext;
    $menu_items[] = array(
        'title' => $menu_title,
        'price' => $menu_price,
        'description' => $menu_description
    );

	}
  }  



// clean up the Simple HTML DOM Parser object
$html->clear();
?>
<div class="container">
  <h1 class="display-4 text-center">EAT AND MEET</h1>
 
</div>

<div class="table-responsive">
  <table class="table table-striped">
    <thead>
      <tr>
        <th>Item</th>
        
        <th>Price</th>
      </tr>
    </thead>
    <tbody>
      <?php foreach($menu_items as $item) { ?>
        <tr>
         
          <td><?php echo $item['description']; ?></td>
          <td><?php echo $item['price']; ?></td>
        </tr>
      <?php } ?>
    </tbody>
  </table>
</div>

<?php
// create a new cURL resource
$ch = curl_init();

// set URL and other cURL options
curl_setopt($ch, CURLOPT_URL, "https://www.novavenza.sk/tyzdenne-menu");
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

// send the request and store the response in a variable
$response = curl_exec($ch);

// create a new Simple HTML DOM Parser object and load the HTML from the response

$html = str_get_html($response);

$menu_items = array();



foreach($html->find('div.active li.d-flex.align-items-start') as $menu_item) {
        
       

        ($menu_title = $menu_item->find('.leftbar', 0)->plaintext);

        $menu_price = $menu_item->find('.rightbar', 0)->plaintext;
        
        $menu_itemsVenza[] = array(
          'title' => $menu_title,
          'price' => $menu_price,
          

        );
      }


// clean up the resources
$html->clear();
curl_close($ch);
?>
<div class="container">
  <h1 class="display-4 text-center">VENZA</h1>
 
</div>

<div class="table-responsive">
  <table class="table table-striped">
    <thead>
      <tr>
        <th>Item</th>
        <th>price</th>
        
      </tr>
    </thead>
    <tbody>
      <?php foreach($menu_itemsVenza as $item) { ?>
        <tr>
          <td><?php echo $item['title']; ?></td>
          <td><?php echo $item['price']; ?></td>
          
        </tr>
      <?php } ?>
    </tbody>
  </table>
</div>



 <?php
// Initialize cURL session
$ch = curl_init();

// Set cURL options
curl_setopt($ch, CURLOPT_URL, "http://www.freefood.sk");
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

// Execute the cURL request and get the response
$response = curl_exec($ch);

// Close the cURL session
curl_close($ch);

// Create a new Simple HTML DOM Parser object and load the HTML from the response
$html = str_get_html($response);

$menu_items = array();

$priceMain = $html->find('div#super-price strong', 1)->plaintext; $priceSoup =
$html->find('div#super-price strong', 2)->plaintext;

/*foreach ($html->find('div.row .col-md-4.text-center') as $menu_item) {
    // Extract the plaintext title from the menu item element
    $title = trim($menu_item->plaintext);

    // Add the menu item to the array
    $menu_items[] = array(
        'title' => $title,
        'price' => $priceMain,
    );
}*/


$count = 0;
foreach ($html->find('.col-md-4.text-center') as $menu_item) {
    // Extract the plaintext title from the menu item element
    $title = trim($menu_item->plaintext);

    // Add the menu item to the array with the appropriate price
    if ($count % 3 == 0 && !empty($title) && $title != "Zatvorené") {
        $menu_items[] = array(
            'title' => $title,
            'price' => $priceMain,
        );
    } 

    // Increment the count
    $count++;
}
 array_shift($menu_items);

 if(!empty($menu_items)){


 $menu_items[0]['price'] = $priceSoup;
}

// Clean up the Simple HTML DOM Parser object and the response
$html->clear();
$response = null;
?>
<div class="container">
  <h1 class="display-4 text-center">FREEFOOD</h1>
 
</div>

<div class="table-responsive">
  <table class="table table-striped">
    <thead>
      <tr>
        <th>Item</th>
        <th>price</th>
        
      </tr>
    </thead>
    <tbody>
      <?php foreach($menu_items as $item) { ?>
        <tr>
          <td><?php echo $item['title']; ?></td>
          <td><?php echo $item['price']; ?></td>
          
        </tr>
      <?php } ?>
    </tbody>
  </table>
</div>





</body>
</html>