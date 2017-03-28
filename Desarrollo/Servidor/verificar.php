<?php
include 'ConnectDataBase.php'; 

$list=['Suelos'=>NULL,'Metereologico'=>NULL,'Tanques'=>NULL];


function seekSoilRemotes(&$list, $cordID){
	$mysql=connect_database(); //solicita la conexión a la base de datos
	if($mysql){
		$query="SELECT CordinadorID, RemSuelosID FROM RemotoSuelos";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if(strcmp($row[0], $cordID)==0){//busca el ID que coincida con el nombre 				
				$list['Suelos'][]=$row[1];
			}
		}	
	}
	mysqli_close($mysql);
}

function seekMeteoRemotes(&$list, $cordID){
	$mysql=connect_database(); //solicita la conexión a la base de datos
	if($mysql){
		$query="SELECT CordinadorID, RemMetID FROM RemotoMetereologico";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if(strcmp($row[0], $cordID)==0){//busca el ID que coincida con el nombre 				
				$list['Metereologico'][]=$row[1];
			}
		}	
	}
	mysqli_close($mysql);
}

function seekTanqRemotes(&$list, $cordID){
	$mysql=connect_database(); //solicita la conexión a la base de datos
	if($mysql){
		$query="SELECT CordinadorID, RemTanqueID FROM RemotoTanques";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if(strcmp($row[0], $cordID)==0){//busca el ID que coincida con el nombre 				
				$list['Tanques'][]=$row[1];
			}
		}	
	}
	mysqli_close($mysql);
}

seekSoilRemotes($list, 3);
seekMeteoRemotes($list, 3);
seekTanqRemotes($list, 3);

foreach($list as $clave=>$array){
	if($array) {
		foreach($array as $value) {
			echo $clave.":".$value;
		}
	}
}
?>
