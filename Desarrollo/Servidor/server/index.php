<?php include "../ConnectDataBase.php";?>
<?php include "serverlib.php";?>

<?php
//crea un nuevo formulario de llenado
session_start();
// se asegura que exista la clase de navegación, si no existe la crea.
if(isset($_SESSION['form'])) {
	$formulario=$_SESSION['form'];
}
else {
	$formulario=new ServicioAutomatico;
}
?>
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
<label for="cordID">CordinadorID</label>
<input type="number" name="cordID"><br>
<!-- variable que desea insertar -->
<label for="variable">Variable que desea ingresar: </label>
<select name="variable">
	<?php
		$struct=$formulario->getStructure();
		/*Imprime todas las opciones de variables que hay en la arquitectura del sistema*/
		foreach($struct as $sistema=>$valor){
			foreach($valor as $index=>$var){
				echo "<option value=".$sistema."_".$var.">".$var."(".$sistema.")"."</option>\n";
			}			
		}		
	?>
</select> <br>
<?php echo array_search("suelo_pH",$struct);?>
<!-- Remoto ID al cual quiere escribir -->
<label for="remoteID">ID del remoto: </label>
<input type="number" name="remoteID"><br>
<!-- archivo csv -->
<label for="csvfile">Archivo .csv: </label>
<input type="file" name="datafile" /><br>
<!-- boton de ingreso -->
<input type="submit" name="enviar"  value="Importar"/>
</form>

<?php
//Recolecta la información del usuario
$formulario->setUserName($_POST['user']);
$formulario->setPassword($_POST['password']);
$formulario->setCordID($_POST['cordID']);
$formulario->setVariable($_POST['variable']);
$formulario->setRemoteTable();
$formulario->setRemoteID($_POST['remoteID']);
$formulario->setFilename($_FILES['datafile']['tmp_name']);

if(validar($formulario->getUserName(), $formulario->getPassword())) {
	if(isCordWritable(retrieveCordPlace($formulario->getCordID()),$formulario->getUserName())) {
		if(isRemoteAttached(	$formulario->getRemoteTable(),
									$formulario->getRemoteID(),
									$formulario->getCordID())){
			/****************************************************************
			Inicia el proceso de inserción del archivo CSV a la base de datos
			--Se toma como referencia todos los datos de la solicitud.
			*****************************************************************/
			$mysql=connect_database();			
			$handle=fopen($formulario->getFilename(),'r+');
			while($content=fscanf($handle, "%s\n")){//escanea todas las filas del archivo		
				foreach($content as $fila){
					$fila=TOKEN_BEGIN.$fila;//garantiza que la funcion lea todos los datos de la cadena			
					$query=$formulario->setQuery($fila);
					echo $query.'<br>';				
					mysqli_query($mysql,$query);
				}
			}
			mysqli_close($mysql);		
		}
		else {
			$formulario->setErrorMessage("El remoto no está asociado al cordinador");
		}
	}
	else {
		$formulario->setErrorMessage("El usuario no tiene permitido modificar este cordinador");	
	}
}
else {
	$formulario->setErrorMessage("autenficacion fallida");
}
/*Muestra el mensaje de error*/
echo "<p>".$formulario->getErrorMessage()."</p>";
$formulario->clearForm();
$_SESSION['form']=$formulario;
?>
</body>
</html>