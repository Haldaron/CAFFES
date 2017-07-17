<?php
include '../mylibrary.php';
// Start the session
session_start();
// se asegura que exista la clase de navegación, si no existe la crea.
if(isset($_SESSION['navigator'])) {
	$nav=$_SESSION['navigator'];
}
else {
	$nav=new navegacion;
}
?>

<!DOCTYPE html>

<head>
	<title>proyecto CAFFES</title>
	<meta name="generator" content="Bluefish 2.2.7" >
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<html lang="es">
	<link href="../css/bootstrap.min.css" rel="stylesheet" media="screen">
	<link rel="stylesheet" href="../estilos.css" type="text/css" media="all">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
</head>

<?php
	header("Location: index.php");
?>
<script>
	function confirmar(){
		alert("¡Su dato ha sido almacenado de forma exitosa");
	}
</script>
