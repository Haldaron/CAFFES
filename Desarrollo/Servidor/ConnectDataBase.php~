<?php
define("SERVERNAME","localhost");
define("MYPHPUSER","root");
define("MYPHPPASSWORD","GEST2017");
define("DATABASENAME", "CaffesDataBase");

//definiciones de la base de datos
define('ACCIONES',['upload'=>'escribir','download'=>'leer']);
define('ACTIONMASK',['upload'=>'Ingresar datos','download'=>'Descargar Datos']);


function getTableColumns($tableName){
	$query="SHOW COLUMNS FROM ".$tableName;
	//echo $query;
   $my_sql=connect_database();
   //echo isset($my_sql)?"si":"no";
   $result=mysqli_query($my_sql,$query);
   
	$n=mysqli_num_rows($result);
	//echo $n;
	for($i=0;$i<$n;$i++) {
		$row=	mysqli_fetch_row($result);
		foreach($row as $clave => $value){
		//echo $clave." : " .$value."<br>";
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

//Permite hace una validación al formulario de registro
function validar($nombre, $clave) {
	$cmp=false;
	$mysql=connect_database(); //socilita la conexion a la base de datos	
	if ($mysql){
		$query="SELECT UsuarioName, Password FROM Usuarios";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if((strcmp($row[0], $nombre)==0)&&(strcmp($row[1], $clave)==0)) {
				$cmp=true; // si enceuntra la combinacion de usuario y contraseña se pone en "true";
			}
		}
	}
	mysqli_close($mysql);	
	return $cmp;
}


/**************************************************
**Asocia un ID a un nombre de Usuario Determinado**
***************************************************/

function querryID($user) {
	$id=NULL; // inicializa la variable ID, la idea es buscarlos en base de datos
	$mysql=connect_database(); //socilita la conexion a la base de datos	
	if ($mysql){
		$query="SELECT UsuarioName, UsuarioID FROM Usuarios";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if(strcmp($row[0], $user)==0) {//determina si se encuentra el nombre
				$id=$row[1]; //devuelve el valor que se encuentra en el registro
			}
		}
	}
	mysqli_close($mysql);	
	return $id;
}

/********************************************************************
Obtiene un listado de las acciones a las que tiene permiso un usuario
*********************************************************************/
function queryActionList($UserName){
	$list=[];//Devuelve el valor de la lista de acciones del sujeto
	$mysql=connect_database(); //socilita la conexion a la base de datos	
	if ($mysql){
		$query="SELECT UsuarioName, permiso FROM Permisos";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
				if((strcmp($row[0], $UserName)==0)&&(strcmp($row[1], "escribir")==0)) {
					$list=array_merge($list,['action_1'=>'upload']);
				}
				if((strcmp($row[0], $UserName)==0)&&(strcmp($row[1], "leer")==0)) {
					$list=array_merge($list,['action_2'=>'download']);
				}
			}
		}
	mysqli_close($mysql);			
	return $list;
}

/***********************************************************
Selecciona un listado de cordinadores en los que un usuario 
puede desempeñar determinada función 
***********************************************************/
function querryCordinator($UserName, $action) {
	$opcion=ACCIONES[$action];
	$list=[]; //la lista inicialmente está vacía
	$mysql=connect_database(); //solicita la conexión a la base de datos	
	if ($mysql){
		$query="SELECT UsuarioName, permiso, CordinadorLugar FROM Permisos";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
				if((strcmp($row[0], $UserName)==0)&&(strcmp($row[1], $opcion)==0)) {				
					$list=array_merge($list,[$row[2]]);
				}
			}
		}
	mysqli_close($mysql);
	return $list;
}

/******************************************************************
Lista los remotos que estan asociados a un cordinador en especifico
******************************************************************/
function queryRemoto($action,$cord){
	$list=['Suelos'=>NULL,'Meteorológico'=>NULL,'Tanques'=>NULL];//variable que lista los remotos que perteneces a cada cordinador.
	//usando el nombre del cordinador obtengo el ID del mismo
	$cordID=NULL;
	$mysql=connect_database(); //solicita la conexión a la base de datos
	if($mysql){
		$query="SELECT Lugar, CordinadoresID FROM Cordinadores";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if(strcmp($row[0], $cord)==0){//busca el ID que coincida con el nombre 				
				$cordID=$row[1];
			}
		}//esta identificado el ID del cordinador
		mysqli_free_result($result);
		mysqli_close($mysql);
	}
	switch($action) {
		case "download":// Busco en la tablas: RemotoSuelos, RemotoMetereologico, RemotoTanques 
			seekSoilRemotes($list, $cordID);
			seekMeteoRemotes($list, $cordID);
			seekTanqRemotes($list, $cordID);
			break;
		case "upload":// Busco en la tablas: RemotoSuelos, RemotoTanques
			seekSoilRemotes($list, $cordID);
			seekTanqRemotes($list, $cordID);
			break;
	}
	return $list;
}
/**************************************************************
Consulta el listado de Remotos de Suelos Conectados a un CordID
***************************************************************/
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
	mysqli_free_result($result);
	mysqli_close($mysql);
}
/*******************************************************************
Consulta el listado de Remotos Metereologicos Conectados a un CordID
********************************************************************/
function seekMeteoRemotes(&$list, $cordID){
	$mysql=connect_database(); //solicita la conexión a la base de datos
	if($mysql){
		$query="SELECT CordinadorID, RemMetID FROM RemotoMetereologico";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if(strcmp($row[0], $cordID)==0){//busca el ID que coincida con el nombre 				
				$list['Meteorológico'][]=$row[1];
			}
		}	
	}
	mysqli_free_result($result);
	mysqli_close($mysql);
}

/*******************************************************************
Consulta el listado de Remotos de Tanques Conectados a un CordID
********************************************************************/
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
	mysqli_free_result($result);
	mysqli_close($mysql);
}

function queryVariable($remoteType, $RemoteID) {
	$list=[];
	switch($remoteType) {
		case "Suelos":
			$list=['Temperatura','Humedad','pH'];
			break;
		case "Meteorológico":
			$list=['Humedad Relativa','Temperatura','Brillo Solar','Velocidad de Viento', 'Dirección de Viento','Precipitación','PAR'];
			break;
		case "Tanques":
			$list=['pH','Temperatura'];
			break;
	}
	return $list;
}

/**************************************************
revisa si un coordinador tiene permisos de escribir
**************************************************/
?>