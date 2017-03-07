<!DOCTYPE html>
<html>
<head>
	<title>proyecto CAFFES</title>
	<meta name="generator" content="Bluefish 2.2.7" >
   <meta charset="utf-8">
   <meta http-equiv="X-UA-Compatible" content="IE=edge">
   <meta name="viewport" content="width=device-width, initial-scale=1">
   <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
</head>

<?php
$usuario=$_POST['user'];
$password=$_POST['password'];	
?>

<?php
function ($nombre, $clave)
<!-- cambia su lógica cuando tenga una base de datos --> 
{	
	$cmp=FALSE;
	if($nombre=='admin' && $clave=='1234') {
		$cmp=true;
	}
	else {
		$cmp=false;
	}
	return $cmp;		
}
?>

<body>
	<!-- Librería jQuery requerida por los plugins de JavaScript -->
   <script src="http://code.jquery.com/jquery.js"></script>
	<div class="container">
		<div class="page-header"><h2>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL<br><small> LA PLATA, HUILA, CENTRO ORIENTE</small></h2></div>
	</div>
	<?php
	if($usuario=='admin' && $password=='1234') {
		echo '<p>Usuario válido</p>';
	}
	else {
		echo 'Usuario inválido';
		echo "<a href=index.html> regresar </a>";
	}
	?>
	
	<script src="js/bootstrap.min.js"></script>
</body>
</html>

