<?php
include 'config.php';

if (isset($_POST['city'])) {
    $ch = curl_init(sprintf('%s?%s', 'http://api.positionstack.com/v1/forward', http_build_query([
        'access_key' => '090e7d65e3ab97ae5a507046863ec3f7',
        'query' => $_POST['city'],
        'output' => 'json',
        'limit' => 1,
    ])));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $json = curl_exec($ch);

    curl_close($ch);

    $apiResult = json_decode($json, true);

if ($apiResult['data'][0]['country']!= 0) {
            $state = $apiResult['data'][0]['country'];
            $code_api = $apiResult['data'][0]['country_code'];
            $latitude = $apiResult['data'][0]['latitude'];
            $longitude = $apiResult['data'][0]['longitude'];

    // ---------
}else{
    header('Location: ' . $_SERVER['PHP_SELF']);
    exit();
}

    $ch = curl_init(sprintf('%s', 'https://restcountries.com/v2/alpha/'. $code_api));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $json = curl_exec($ch);

    curl_close($ch);

    $apiResult = json_decode($json, true);
if (!empty($apiResult)) {
    
    $code = $apiResult["alpha2Code"];
    $capital = $apiResult["capital"];
}
    // ---------

    $ch = curl_init(sprintf('%s%s', 'https://api.weatherapi.com/v1/current.json?', http_build_query([
        'key' => '8a948563cab042c69ed145747222804',
        'q' => $latitude . ',' . $longitude,
    ])));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $json = curl_exec($ch);

    curl_close($ch);

    $apiResult = json_decode($json, true);
if (!empty($apiResult)) {
    $time = $apiResult["location"]['localtime'];
    $temp = $apiResult["current"]['temp_c'];
    $text = $apiResult["current"]['condition']['text'];
    $img = $apiResult["current"]['condition']['icon'];
}
    try {
        $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);


        $stmt = $conn->prepare("insert into visits(city, state, date, code, lon, lat) values(?, ?, ?, ?, ?, ?)");
        $stmt->execute([$_POST['city'], $state, $time, $code, $longitude, $latitude]);


        $stmt = $conn->prepare("SELECT COUNT(id) as poc, state, `code` FROM visits GROUP BY state, code ORDER BY COUNT(id) DESC;");
        $stmt->execute();
        $D1 = $stmt->fetchAll();

        $stmt = $conn->prepare("SELECT COUNT(id) FROM visits WHERE CAST(date AS TIME) BETWEEN '06:00' and '15:00'");
        $stmt->execute();
        $D41 = $stmt->fetch()[0];

        $stmt = $conn->prepare("SELECT COUNT(id) FROM visits WHERE CAST(date AS TIME) BETWEEN '21:00' and '23:59'");
        $stmt->execute();
        $D42 = $stmt->fetch()[0];

        $stmt = $conn->prepare("SELECT COUNT(id) FROM visits WHERE CAST(date AS TIME) BETWEEN '15:00' and '21:00'");
        $stmt->execute();
        $D43 = $stmt->fetch()[0];

        $stmt = $conn->prepare("SELECT COUNT(id) FROM visits WHERE CAST(date AS TIME) BETWEEN '23:59' and '06:00'");
        $stmt->execute();
        $D44 = $stmt->fetch()[0];

    } catch (PDOException $e) {
        echo $e->getMessage();
    }


}

?>



<!doctype html>
<html>
<head>
    <meta charset="UTF-8">
<!--    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge"> -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>zadane4</title>
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.8.0/dist/leaflet.css"
          integrity="sha512-hoalWLoI8r4UszCkZ5kL8vayOGVae1oxXe/2A4AO6J9+580uKHDO3JdHb7NzwwzK5xr/Fs0W40kiNHxM9vyTtQ=="
          crossorigin=""/>
    <script src="https://unpkg.com/leaflet@1.8.0/dist/leaflet.js"
            integrity="sha512-BB3hKbKWOc9Ez/TAwyWxNXeoV9c1v6FIeYiBieIWkpLjauysF18NzgR1MBNBXf8/KABdlkX68nAhlwcDFLGPCQ=="
            crossorigin=""></script>
            <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.3/jquery.min.js"></script>
            <link rel="stylesheet" href="css/bootstrap.min.css">
    <link rel="stylesheet" href="styles.css">
</head>
<body>
<header>

    <div class="container text-center">
  <h1 class="">FIND CITY</h1>
</div>
     <div class="container h-100">
        <div class="row align-items-center justify-content-center h-100">
            <div class="col-sm-6">
               <form class="form-inline d-flex justify-content-center" action="index.php" method="post">

                    <div class="form-group mb-2">
                        <label for="staticEmail2" class="sr-only">Email</label>
                        <input type="text" name="city" id="city" placeholder="Adresa" class="form-control border">
                    </div>
                    <button type="submit" class="btn btn-primary mb-2">FindCity</button>
                </form>
            </div>
        </div>
    </div>
</form>
</header>
</header>

       <div class="container mt-5">
        <div class="row justify-content-center">
            <div id="map"></div>
        </div>
    </div>

    <div class="<?php if (!isset($text)) echo 'hidden'; ?>"  id="secondSection">
        

  <div id="weather">
            <h3><?php echo $text?></h3>
            <img src="<?php echo $img?>" alt="">
            <p><?php echo $temp?> °C</p>
        </div>




 <div class="container" id="grid2sectionRight">
    <div class="row justify-content-center">
        <div class="col-md-6">
            <table  class="table">
                <tbody>
                    <tr>
                        <th>Country</th>
                        <td><?php echo $state?></td>
                    </tr>
                    <tr>
                        <th>CapitalCity</th>
                        <td><?php echo $capital?></td>
                    </tr>
                    <tr>
                      
                         <th>GPS</th>
                        <td><?php echo $latitude . ' ' . $longitude?></td>
                    </tr>
                </tbody>
            </table>
        </div>
    </div>
</div>

      <div id="D">
        <table  class="table">
            <thead>
                <tr>
                    <th>Visits</th>
                    <th>Country</th>
                    <th>Flag</th>
                </tr>
            </thead>
            <tbody id="countryVisitors">
            <?php
                foreach ($D1 as $data) {
                    echo '<tr><td>'.$data['poc'].'</td> <td>'.$data['state'].'</td> <td>  <img class="flag" src="https://www.geonames.org/flags/x/'.strtolower($data['code']).'.gif"/></td></tr>';
                }
            ?>
            </tbody>
        </table>
</div>
<div>
        <table id="visitorsFrom" class="hidden table">
            <thead>
                <tr>
                    <th>City</th>
                    <th>Visitors</th>
                </tr>
            </thead>
            <tbody ID="add"></tbody>
        </table>
</div>
 

     </div>
    <div  class="<?php if (!isset($state)) echo 'hidden'; ?>">
    <div class="container" id="siteVisitors">
 
   
      <table class="table">
        <thead>
          <tr>
            <th>Cas</th>
            <th>Pocet Navstiev</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td>6:00-15:00</td>
            <td><?php echo $D41?></td>
          </tr>
          <tr>
            <td>21:00-0:00</td>
            <td><?php echo $D42?></td>
          </tr>
          <tr>
            <td>15:00-21:00</td>
            <td><?php echo $D43?></td>
          </tr>
          <tr>
            <td>0:00-6:00</td>
            <td><?php echo $D44?></td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</div>


    <script src="script.js" defer></script>
</body>
</html>