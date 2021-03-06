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

<?php if($nav->getLog()):?>
	<?php
	if(!empty($_POST['action'])){
		$action=$_POST['action'];
		$nav->setActionSel($action);
		$nav->setCordList();
        }
	?>

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
<!--  <script src="http://code.jquery.com/jquery.js"></script>-->
			<!-- Header de la página  -->	
			<div class="container">
				<div class="page-header"><h3>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL<br><small> LA PLATA, HUILA, CENTRO ORIENTE</small></h3></div>
			</div>
			
			<!--cabecera que contiene la barra de navegacion-->
			<div class="container">
                            <nav class="navbar navbar-default">			
                            <div class="container-fluid">
                                <div class="navbar-header">
                                <a class="navbar-brand" href="index.html">ProyectoOccicafe</a>
                                </div>
                                <ul class="nav navbar-nav">
                                <li><a href="actions.php">acciones</a></li>
                                <li class="active"><a href="#">cordinadores</a></li>
                                </ul>
                            </div>
                            </nav>
                        </div>

			<div class="container">
				<div class="col-sm-6">
					<img src="./imagenes/finca.jpg" class="img-thumbnail img-responsive" alt="Imagen responsive">
				</div>
				<div class="col-sm-6">
					<h3><i>Lista de cordinadores:</i></h3><br>
					<div class="row">					
					<form action="remoto.php" method="POST">										
					<?php
						$list=$nav->getCordList();
						foreach ($list as $item){
							echo "<div class='col-sm-4'>\n";
  							echo "<input class='radio-inline' type='radio' name='cord' value='".$item."' data-labelauty='".$item."' checked>\n";
							echo "</div>\n";
						}
					?>
					</div>
					<button value='Ingresar' type='submit' class='btn btn-default form-control' name='button'>Siguiente</button>
					</form>

				</div>
			</div>	
			<script>
				$(document).ready(function(){
					$(":checkbox").labelauty();
					$(":radio").labelauty();
				});
			</script>
			<script src="js/bootstrap.min.js"></script>	
</body>
</html>
<?php else: ?>
	<?php header("Location: index.php"); ?>
<?php endif;?>