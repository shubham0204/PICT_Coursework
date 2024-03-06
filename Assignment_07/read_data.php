<?php

// Reference: https://www.w3schools.com/php/php_mysql_select.asp

$servername = "localhost" ;
$username = "root" ;
$password = "root" ;
$dbname = "inventory" ;

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, name, quantity, price FROM items";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  $rows = $result -> fetch_all() ;
  echo json_encode( $rows ) ; 
} else {
  echo json_encode( '[]' );
}
$conn->close();

?>