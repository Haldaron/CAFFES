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
	<meta name="generator" content="Bluefish 2.2.7">
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<html lang="es">
	<link href="../css/bootstrap.min.css" rel="stylesheet" media="screen">
	<link rel="stylesheet" href="../estilos.css" type="text/css" media="all">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
</head>

<?php
$fecha=$_GET["fecha"];
$hora=$_GET["hora"].":00";
$valor=$_GET["variable"];

$tipo="puntual";

$sistema=$_GET["sistema"];
$medicion=$_GET["medicion"];

if((strcmp($sistema,"beneficiadero")==0)&&(strcmp($medicion,"temperatura")==0))
{
    $periodo="N/A";
    $unidad="Celsius";
    $filename="/home/pi/USCO/remoto_tanque/Temperatura.csv";
}
elseif((strcmp($sistema,"beneficiadero")==0)&&(strcmp($medicion,"pH")==0))
{
    $periodo="N/A";
    $unidad="pH";
    $filename="/home/pi/USCO/remoto_tanque/ph.csv";  
}
elseif((strcmp($sistema,"cultivo")==0)&&(strcmp($medicion,"pH")==0))
{
    $periodo="trimensual";
    $unidad="pH";
    $filename="/home/pi/USCO/remoto_suelo/remoto1/ph.csv";
}
else{
    header("Location: index.php"); //no deberia ingresar a este condicional
}
	/*configura la cadena que sera alamacenado en el archivo*/
	$entry=$fecha.','.$hora.','.$valor.','.$unidad.','.$tipo.','.$periodo."\n";
	echo $entry;
	echo $filename;
	$fd=fopen($filename,"a");
	  if(fwrite($fd,$entry))
	  {
	    header("Location: index.php");
	  }
	  else
	  {
	    header("Location: ingresar.php");
	  }
	fclose($fd);
?>
</html>