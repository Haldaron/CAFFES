<!-- inicia una session para poder llevar la clase navegador-->
<?php
//incluye la libreria del proyecto
include 'mylibrary.php';
// Start the session
session_start();
?>



<?php
// se asegura que exista la clase de navegación, si no existe la crea.
if(isset($_SESSION['navigator'])) {
	$nav=$_SESSION['navigator'];
}
else {
	$nav=new navegacion;
}
?>

<!DOCTYPE html>
<html>
<head>
	<title>proyecto CAFFES</title>
	<meta name='generator' content='Bluefish 2.2.7' >
   <meta charset='utf-8'>
   <meta http-equiv='X-UA-Compatible' content='IE=edge'>
   <meta name='viewport' content='width=device-width, initial-scale=1'>
   <link href='css/bootstrap.min.css' rel='stylesheet' media='screen'>
   <link rel='stylesheet' href='./estilos.css' type='text/css' media='all'>
</head>

<body>
	<!-- Librería jQuery requerida por los plugins de JavaScript -->
   <script src='http://code.jquery.com/jquery.js'></script>
	<div class='container'>
	<div class='page-header'><h3>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL<br><small> LA PLATA, HUILA, CENTRO ORIENTE</small></h3></div>
	</div>
	<div class='container'><!-- formulario de ingreso con notificación de error -->
	<div class='row'>
	<!-- imagen de referencia -->
	<div class='col-sm-6'>
		<img src='./imagenes/finca.jpg' class='img-thumbnail' alt=''>
	</div>
		
		<div class='col-sm-6'>
			<form action='cordinador.php' method='POST'>			
				<div class='row'>
  					<input type='radio' name='action' value='download' checked='checked' id='download'>
  					<label for='download' class='DefAccion'>Descargar Datos</label>
				</div>
				<div class='row'>
  					<input type='radio' name='action' value='upload' id='upload'>
  					<label for='upload' class='DefAccion'>Ingresar Datos</label>
				</div>
				<button value='Ingresar' type='submit' class='btn btn-default form-control' name='button'>Siguiente</button>
			</form>		
		</div>		

	</div>
	</div>
	<script src='js/bootstrap.min.js'></script>
</body>
</html>
