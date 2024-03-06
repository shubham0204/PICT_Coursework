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
  while($row = $result->fetch_assoc()) {
    echo "* " . $row["id"]. " - " . $row["name"]. " - " . $row["quantity"]. " - " . $row["price"] . "<br>";
  }
} else {
  echo "0 results";
}
$conn->close();

?>