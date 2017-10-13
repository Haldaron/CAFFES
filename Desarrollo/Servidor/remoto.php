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
	if(!empty($_POST['cord'])){
		$cord=$_POST['cord'];
		$nav->setCordSel($cord);
		$nav->setRemList();
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
                                <li><a href="cordinador.php">cordinadores</a></li>
                                <li class="active"><a href="#">remotos</a></li>
                                </ul>
                            </div>
                            </nav>
                        </div>
                        
			<div class="container">
				<div class="col-sm-6">
					<img src="./imagenes/finca.jpg" class="img-thumbnail img-responsive" alt="Imagen responsive">
				</div>
				<div class="col-sm-6">
					<?php
						$nav->setCordList();
					?>
					<h3><i>Lista de Remotos:</i></h3><br>
					<div class="row">					
					<form action="variable.php" method="POST">										
					<?php
						$list=$nav->getRemList();
						foreach ($list as $clave=>$item){
							$label=$item?$clave:NULL;// Si está vacio el listado de remotos no muestra la clave
							if($label) {
								echo "<div class='col-sm-6'>\n";
	  							echo "<input class='radio-inline' type='radio' name='remoto' value='".$label."' data-labelauty='".$label."' checked>\n";
								echo "</div>\n";							
							}
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