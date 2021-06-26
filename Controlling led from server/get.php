<?php
$db="id16188049_nit";
$user ="id16188049_lakshay";
$pass ="Database@123";
$host = "localhost";
$con = mysqli_connect($host,$user,$pass,$db);
$query = "select * from home";
$res = mysqli_query($con,$query);
$row = mysqli_fetch_array($res);
$data = $row['status'];
if($data == "1"){
	$data = "ON";
}
if($data == "0"){
	$data = "OFF";
}
echo $data;
?>