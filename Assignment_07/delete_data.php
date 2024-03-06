<?php

// Reference: https://www.w3schools.com/php/php_mysql_delete.asp

$servername = "localhost" ;
$username = "root" ;
$password = "root" ;
$dbname = "inventory" ;

$item_id = $_GET[ 'id' ];

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "DELETE FROM items WHERE id=$item_id";

if ($conn->query($sql) === TRUE) {
  echo "Item deleted successfully";
} else {
  echo "Error deleting item: " . $conn->error;
}

$conn->close();
?>