<?php
include 'ConnectDataBase.php'; 

$list=['Temperatura'=>1,'Humedad'=>NULL,'pH'=>NULL];

foreach($list as $clave=>$array){
	if($array) {
		foreach($array as $value) {
			echo $clave.":".$value;
		}
	}
}


function seekTempSoil(&$list, $RemID){
	$mysql=connect_database(); //solicita la conexión a la base de datos
	if($mysql){
		$query="SELECT Remoto_Suelos_ID FROM TemperaturaSuelo";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if(strcmp($row[0], $cordID)==0){//busca el ID que coincida con el nombre 				
				$list['Temperatura'][]=true;
			}
		}	
	}
	mysqli_close($mysql);
}

seekTempSoil($list, 1);

foreach($list as $clave=>$array){
	if($array) {
		foreach($array as $value) {
			echo $clave.":".$value;
		}
	}
}
?>
