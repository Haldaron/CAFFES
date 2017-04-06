<?php define("TOKEN",","); ?>
<?php include "../ConnectDataBase.php";?>
<!DOCTYPE html>
<head>
<meta http-equiv=”Content-Type” content=”text/html; charset=utf-8″ />
<title>Servicio de Carga Automática</title>
</head>

<body>
<p>Diligencie los siguientes campos para exportar su archivo:</p>
<form name="import" method="post" action="<?php echo $_SERVER['PHP_SELF']?>" enctype="multipart/form-data">
<!--Nombre de usuario-->
<label for="user">Usuario: </label>
<input type="text" name="user"><br>
<!--Contraseña del equipo-->
<label for="password">Contraseña: </label>
<input type="password" name="password"><br>
<!-- Identificacion del Cordinador -->
<label for="cordPlace">Cordinador</label>
<input type="text" name="cordPlace"><br>
<!-- Remoto ID al cual quiere escribir -->
<label for="remoteID">ID del remoto: </label>
<input type="number" name="remoteID"><br>
<!-- variable que desea insertar -->
<label for="variable">Variable que desea ingresar: </label>
<input type="text" name="variable"><br>
<!-- archivo csv -->
<label for="csvfile">Archivo .CSV: </label>
<input type="file" name="csvfile" /><br>
<!-- boton de ingreso -->
<input type="submit" name="enviar"  value="Importar"/>
</form>

<?php
include 'serverlib.php';
//crea un nuevo formulario de llenado
session_start();
// se asegura que exista la clase de navegación, si no existe la crea.
if(isset($_SESSION['form'])) {
	$formulario=$_SESSION['form'];
}
else {
	$formulario=new ServicioAutomatico;
}

//setea la autenticacion del equipo/usuario
$formulario->setUserName($_POST['user']);
$formulario->setPassword($_POST['password']);
$formulario->setCordPlace($_POST['cordPlace']);
if(validar($formulario->getUserName(), $formulario->getPassword())) {
	if(isCordWritable($formulario->getCordPlace(),$formulario->getUserName())) {
		echo "se puede";
	}
	else {
		$formulario->setErrorMessage("El usuario no tiene permitido modificar este cordinador");	
	}
}
else {
	$formulario->setErrorMessage("autenficacion fallida");
}

//$_SESSION['form']=$formulario;
?>
<?php	
	$filename = $_FILES['csvfile']['name'];
	$tempname=$_FILES['csvfile']['tmp_name'];
	$tipo = $_FILES['csvfile']['type'];
	$destino = 'bak_'.$filename;
	copy($tempname,$destino);
	
	if(file_exists($destino)){
		//echo file_get_contents($destino);
	}
	
	/* Rutina que lee el archivo*/
	$table="TemperaturaSuelo";	
	$handle=fopen($destino, 'r+');
		while($fila=fscanf($handle, "%s\n")){
			foreach ($fila as $value){
				$list=strtok($value,TOKEN);
			 	/*put the logic here*/
				$mysql_id = connect_database();	
				if($mysql_id) {
					//getTableColumns($table);		
					$fecha=$list;
					$list=strtok(TOKEN);
					$Hora=$list;
					$list=strtok(TOKEN);
					$valor=floatval($list);
					$list=strtok(TOKEN);
					$unidad=$list;
					$list=strtok(TOKEN);
					$tipo=$list;
					$list=strtok(TOKEN);
					$periodo=$list;
					$remID=1;
					
					//echo $fecha.$Hora.$valor.$unidad.$tipo.$periodo.$remID."<br>";
					//forma el query para insertar los datos a una base de datos en particular.	
					$insertSQL="INSERT INTO ".$table." (TempSueloID, Fecha, Hora, valor, unidad, tipo, periodo, Remoto_Suelos_ID) 
									VALUES (NULL,
									'".$fecha."',
									'".$Hora."',
									'".$valor."',
									'".$unidad."',
									'".$tipo."',
									'".$periodo."',
									'".$remID."')";				
					mysqli_query($mysql_id,$insertSQL);// inserta un dato en la tabla deseada		      			
				}
				mysqli_close($mysql_id); // cierra la conexion con la base de datos					
			}					
		}
	fclose($handle);
	/*Muestra el mensaje de error*/
	echo "<p>".$formulario->getErrorMessage()."</p>";
	$formulario->clearForm();
	$_SESSION['form']=$formulario;
?>
</body>
</html>
