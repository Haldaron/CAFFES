<!-- inicia una session para poder llevar la clase navegador-->
<?php
include 'mylibrary.php';
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

<?php if($nav->getLog()): ?>
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
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
	<script src="jquery-labelauty/source/jquery-labelauty.js"></script>
	<link rel="stylesheet" type="text/css" href="jquery-labelauty/source/jquery-labelauty.css">
</head>

<body>
<!-- Librería jQuery requerida por los plugins de JavaScript -->
<!-- descomentar para agregar estilos<script src="http://code.jquery.com/jquery.js"></script>-->
			<!-- Header de la página  -->	
			<div class="container">
				<div class="page-header"><h3>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL<br><small> LA PLATA, HUILA, CENTRO ORIENTE</small></h3></div>
			</div>
			<div class="container">
				<div class="col-sm-6">
					<img src="./imagenes/finca.jpg" class="img-thumbnail" alt="">
				</div>
				<div class="col-sm-6">
					<h3><i>Lista de acciones:</i></h3><br>
					<form action="cordinador.php" method="POST">					
					<?php
						$list=$nav->getActionList();
						foreach ($list as $item){
							echo "<div class='row block'>\n";
  							echo "<input  type='radio' name='action' value='".$item."' data-labelauty='".ActionMask($item)."' checked>\n";
							echo "</div>\n";
						}
					?>
					<br>
					<button value='Ingresar' type='submit' class='btn btn-default form-control' name='button'>Siguiente</button>
					</form>
				</div>
			</div>	
			<script>
				$(document).ready(function(){
					$(":radio").labelauty();
				});
			</script>			
			<script src="js/bootstrap.min.js"></script>	
</body>
</html>
<?php else: ?>
	<?php header("Location: index.php"); ?>
<?php endif;?>	