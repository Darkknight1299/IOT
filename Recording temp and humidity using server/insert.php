<?php
$db="id16188049_nit";
$user ="id16188049_lakshay";
$pass ="Database@123";
$host = "localhost";
// connect php to mysql
$con = mysqli_connect($host,$user,$pass,$db);
date_default_timezone_set("Asia/Kolkata");
$date = date("d-m-Y");  //06-09-2020
$time = date("H:i:s");  //17:02:36- 5:02 and 36 seconds
$hum = $_GET['field1'];
$temp = $_GET['field2'];
$query = "insert into sensor(date,time,humidity,temperature)
			values('$date','$time','$hum','$temp')"; // insert into table name(column name) values('variacle name')
if (mysqli_query($con,$query)){
	echo "Data Inserted";
}
else{
	echo "Failed to insert the Data";
}
?>