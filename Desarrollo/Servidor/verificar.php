<!DOCTYPE html>
<html>
<head>
	<title>proyecto CAFFES</title>
	<meta name="generator" content="Bluefish 2.2.7" >
   <meta charset="utf-8">
   <meta http-equiv="X-UA-Compatible" content="IE=edge">
   <meta name="viewport" content="width=device-width, initial-scale=1">
   <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
   <link rel="stylesheet" href="./estilos.css" type="text/css" media="all">
</head>

<?php
if(isset($_POST['user'])){
	$usuario=$_POST['user'];
}
	else {
	$usuario=$_GET['user'];
}

if(isset($_POST['password'])){
	$password=$_POST['password'];
}
	else {
	$password=$_GET['password'];
}
?>

<?php
include "mylibrary.php";
?>

<body>
	<!-- Librería jQuery requerida por los plugins de JavaScript -->
   <script src="http://code.jquery.com/jquery.js"></script>
	<div class="container">
	<div class="page-header"><h3>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL<br><small> LA PLATA, HUILA, CENTRO ORIENTE</small></h3></div>
	</div>
	<div class="container"><!-- formulario de ingreso con notificación de error -->
	<div class="row">
	<!-- imagen de referencia -->
	<div class="col-sm-6">
		<img src="./imagenes/finca.jpg" class="img-thumbnail" alt="">
	</div>
	<div class="col-sm-6">
	<!-- decide si reenvia al formulario de registro o muestra las acciones permitidas -->
 	<?php $cmp=validar($usuario,$password);?>
 		<?php if($cmp): ?>
			<form action="cordinador.php" method="POST">			
				<div class="row">
  					<input type="radio" name="action" value="download" checked="checked" id="download">
  					<label for="download" class="DefAccion">Descargar Datos</label>
				</div>
				<div class="row">
  					<input type="radio" name="action" value="upload" id="upload">
  					<label for="upload" class="DefAccion">Ingresar Datos</label>
				</div>
				<button value="Ingresar" type="submit" class="btn btn-default form-control" name="button">Siguiente</button>
			</form>						
	 	<?php else : ?>
			<!-- formulario de registro -->		
			<form action="verificar.php" method="post">
				<div class="form-group">
					<label for="user_text">usuario</label><br>				
					<input type="text" name="user" value="usuario" id="user_text" class="form-control">	
				</div>
				<div class="form-group">
					<label for="password_text">contraseña</label><br>							
					<input type="password" name="password" value="contraseña" id="password_text" class="form-control">	
				</div>	
				<button value="Ingresar" type="submit" class="btn btn-default form-control">Ingresar</button>
			</form>
			<!-- genera un formulario igual al anterior pero con una advertencia acerca del login -->
			<div class="alert alert-warning">
  				<strong>Advertencia:</strong> la combinación usuario/contraseña no es correcta.
			</div>	
	</div>
	</div>
	</div>
 	<?php endif; ?>
	<script src="js/bootstrap.min.js"></script>
</body>
</html>