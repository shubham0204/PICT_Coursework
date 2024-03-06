<html>
<body>
<?php

// Reference: https://www.w3schools.com/php/php_mysql_insert.asp

$servername = "localhost" ;
$username = "root" ;
$password = "root" ;
$dbname = "inventory" ;

$item_name = $_GET[ 'name' ];
$item_quantity = $_GET[ 'quantity' ];
$item_price = $_GET[ 'price' ];

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO items (name, quantity, price) VALUES ('$item_name', $item_quantity , $item_price )";

if ($conn->query($sql) === TRUE) {
  echo "New item added successfully";
} 
else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

?>
</body>
</html>