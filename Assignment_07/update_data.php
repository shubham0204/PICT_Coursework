<?php

// Reference: https://www.w3schools.com/php/php_mysql_update.asp

$servername = "localhost" ;
$username = "root" ;
$password = "root" ;
$dbname = "inventory" ;

$item_id = $_GET[ 'id' ]; 
$item_name = $_GET[ 'name' ]; 
$item_quantity = $_GET[ 'quantity' ];
$item_price = $_GET[ 'price' ];

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "UPDATE items SET name='$item_name', quantity=$item_quantity, price=$item_price WHERE id=$item_id";

if ($conn->query($sql) === TRUE) {
  echo "Item updated successfully";
} else {
  echo "Error updating item: " . $conn->error;
}

?>