<html>
<title>LED CONTROL</title>
<center>
<h1>LED CONTROL</h1>
<a href="?led=on"><button>LED ON</button></a>
<a href="?led=off"><button>LED OFF</button></a>
</center>
</html>

<?php
$db="id16188049_nit";
$user ="id16188049_lakshay";
$pass ="Database@123";
$host = "localhost";
// connect php to mysql
$con = mysqli_connect($host,$user,$pass,$db);
if(isset($_GET['led'])){
	$status = $_GET['led'];
	if($status == "on"){
		$led = "1";
	}
	if($status == "off"){
		$led = "0";
	}
$query = "update home set status='$led'";
mysqli_query($con,$query);	
}
?>