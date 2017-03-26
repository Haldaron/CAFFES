<?php
define("SERVERNAME","localhost");
define("MYPHPUSER","root");
define("MYPHPPASSWORD","gerrard8");
define("DATABASENAME", "CaffesDataBase");

function getTableColumns($tableName){
	$query="SHOW COLUMNS FROM ".$tableName;
	echo $query;
   $my_sql=connect_database();
   echo isset($my_sql)?"si":"no";
   $result=mysqli_query($my_sql,$query);
   
	$n=mysqli_num_rows($result);
	echo $n;
	for($i=0;$i<$n;$i++) {
		$row=	mysqli_fetch_row($result);
		foreach($row as $clave => $value){
		echo $clave." : " .$value."<br>";
	}
	}

	mysqli_close($my_sql);
}
				


function connect_database(){
	$identifier=mysqli_connect(SERVERNAME, MYPHPUSER, MYPHPPASSWORD);
	if(isset($identifier)){
		mysqli_select_db($identifier,DATABASENAME);	
	}
	return $identifier;
} 
?>