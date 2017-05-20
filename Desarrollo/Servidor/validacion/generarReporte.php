<! DOCTYPE html>
<?php
define(SERVERNAME,'localhost');
define(MYPHPUSER,'root');
define(MYPHPPASSWORD,'GEST2017');
define(DATABASENAME,'validacion');

function connect_database(){
	$identifier=mysqli_connect(SERVERNAME, MYPHPUSER, MYPHPPASSWORD);
	if(isset($identifier)){
		mysqli_select_db($identifier,DATABASENAME);	
	}
	return $identifier;
}
?>

<html>
<head>
    <title>Formato de validacion de la infraestructura instalada</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta charset="ISO-8859-1">
    <link href="../css/bootstrap.min.css" rel="stylesheet" media="screen">
</head>
<body>
<script src="http://code.jquery.com/jquery.js"></script>
<ul class="nav nav-tabs">
    <li><a href="index.php">Crear reporte</a></li>
    <li><a href="crearCaso.php">Crear caso</a></li>
    <li class="active"><a href="#">Generar Reportes</a></li>
</ul>
<div class="container">
    <div class="row">
        <div class="col-sm-6 col-sm-offset-3">
            <h2>Resumen de reportes: </h2>
            <div class="form-group">
                <!--put your form here-->
            </div>
        </div>
    </div>
</div>
<script src="../js/bootstrap.min.js"></script>    
</body>
</html>


