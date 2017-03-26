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

<body>
<!-- Librería jQuery requerida por los plugins de JavaScript -->
<script src="http://code.jquery.com/jquery.js"></script>
			<!-- Header de la página  -->	
			<div class="container">
				<div class="page-header"><h3>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL<br><small> LA PLATA, HUILA, CENTRO ORIENTE</small></h3></div>
			</div>
<?php if(isset($_POST['user']) && isset($_POST['password'])): ?>
	<?php
	$usuario=$_POST['user'];
	$password=$_POST['password'];
	?>
	<?php if(validar($usuario,$password)): ?>
		<?php
		//actualiza los valores de la estructura
		$nav->setLog(true);
		$nav->setUserID(querryID($usuario));
		$nav->setUserName($usuario);
		$_SESSION['navigator']=$nav;
		header("Location: actions.php");
		?>
	<?php else: ?>
		<?php
		//actualiza los valores de la estructura
		$nav->setLog(false);
		$nav->setUserID(NULL);
		$nav->setUserName(NULL);
		$_SESSION['navigator']=$nav;
		?>
			<div class="container">
				<div class="row">
					<!-- imagen de referencia -->
					<div class="col-sm-6">
						<img src="./imagenes/finca.jpg" class="img-thumbnail" alt="">
					</div>
					<!-- formulario de registro -->		
					<div class="col-sm-6">
							<form action="index.php" method="POST">
								<div class="form-group">
									<label for="user_text">usuario</label><br>				
									<input type="text" name="user" value="usuario" id="user_text" class="form-control">
								</div>		
								<div class="form-group">
									<label for="password_text">contraseña</label><br>							
									<input type="password" name="password" value="contraseña" id="password_text" class="form-control">	
								</div>
								<br>	
								<button value="Ingresar" type="submit" class="btn btn-default form-control" name="button">Ingresar</button>
							</form>
							<div class="alert alert-warning">
					  				<strong>Advertencia:</strong> la combinación usuario/contraseña no es correcta.
							</div>							
					</div>
				</div>
			</div> 
	<?php endif; ?>

<?php elseif(isset($_GET['user']) && isset($_GET['password'])): ?>
	<?php
	$usuario=$_GET['user'];
	$password=$_GET['password'];
	?>
	<?php if(validar($usuario,$password)): ?>
		<?php
		//actualiza los valores de la estructura
		$nav->setLog(true);
		$nav->setUserID(querryID($usuario));
		$nav->setUserName($usuario);
		$_SESSION['navigator']=$nav;
		header("Location: actions.php");
		?>
	<?php else: ?>
		<?php
		//actualiza los valores de la estructura
		$nav->setLog(false);
		$nav->setUserID(NULL);
		$nav->setUserName(NULL);
		$_SESSION['navigator']=$nav;
		?>
			<div class="container">
				<div class="row">
					<!-- imagen de referencia -->
					<div class="col-sm-6">
						<img src="./imagenes/finca.jpg" class="img-thumbnail" alt="">
					</div>
					<!-- formulario de registro -->		
					<div class="col-sm-6">
							<form action="index.php" method="POST">
								<div class="form-group">
									<label for="user_text">usuario</label><br>				
									<input type="text" name="user" value="usuario" id="user_text" class="form-control">
								</div>		
								<div class="form-group">
									<label for="password_text">contraseña</label><br>							
									<input type="password" name="password" value="contraseña" id="password_text" class="form-control">	
								</div>
								<br>	
								<button value="Ingresar" type="submit" class="btn btn-default form-control" name="button">Ingresar</button>
							</form>
							<div class="alert alert-warning">
					  				<strong>Advertencia:</strong> la combinación usuario/contraseña no es correcta.
							</div>							
					</div>
				</div>
			</div> 
	<?php endif; ?>
<?php else: ?>
	<?php if($nav->getLog()): ?>
		<?php header("Location: actions.php");?>
	<?php else: ?>
			<div class="container">
				<div class="row">
					<!-- imagen de referencia -->
					<div class="col-sm-6">
						<img src="./imagenes/finca.jpg" class="img-thumbnail" alt="">
					</div>
					<!-- formulario de registro -->		
					<div class="col-sm-6">
							<form action="index.php" method="POST">
								<div class="form-group">
									<label for="user_text">usuario</label><br>				
									<input type="text" name="user" value="usuario" id="user_text" class="form-control">
								</div>		
								<div class="form-group">
									<label for="password_text">contraseña</label><br>							
									<input type="password" name="password" value="contraseña" id="password_text" class="form-control">	
								</div>
								<br>	
								<button value="Ingresar" type="submit" class="btn btn-default form-control" name="button">Ingresar</button>
							</form>
							<div class="alert alert-warning">
					  				<strong>Advertencia:</strong> Debe registrarse para ingresar al sistema.
							</div>							
					</div>
				</div>
			</div> 		
	<?php endif; ?>
<?php endif; ?>		
			<script src="js/bootstrap.min.js"></script>	
</body>
</html>