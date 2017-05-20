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

function getUserList(){
    $mysqli=connect_database();
    if($mysqli){
        $query='SELECT nombre FROM Usuarios';
        $result=mysqli_query($mysqli, $query);
        while($row=mysqli_fetch_row($result)){
            echo '<option>'.$row[0].' </option>';
        }
    }
    mysqli_close($mysqli);
}

function getCasePlace(){
    $mysqli=connect_database();
    if($mysqli){
        $query='SELECT Lugar FROM Lugares';
        $result=mysqli_query($mysqli, $query);
        while($row=mysqli_fetch_row($result)){
            echo '<option>'.$row[0].' </option>';
        }
    }
    mysqli_close($mysqli);
}

function getSistems(){
    $mysqli=connect_database();
    if($mysqli){
        $query='SELECT Nombre FROM Sistemas';
        $result=mysqli_query($mysqli, $query);
        while($row=mysqli_fetch_row($result)){
            echo '<option>'.$row[0].' </option>';
        }
    }
    mysqli_close($mysqli);
}

?>
<! DOCTYPE html>
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
    <li class="active"><a href="#">Crear reporte</a></li>
    <li><a href="crearCaso.php">Crear caso</a></li>
    <li><a href="generarReporte.php">Generar Reportes</a></li>
</ul>
<div class="container">
    <div class="row">
        <div class="col-sm-6 col-sm-offset-3">
            <h2>Nuevo Reporte: </h2>
            <div class="form-group">
                
                <label for='nombre'>Nombre: </label>
                <select class="form-control" name="nombre">
                    <?php getUserList();?>
                </select>
                
                <label for="Lugar">Lugar: </label>
                <select class="form-control" name="lugar">
                    <?php getCasePlace();?>
                </select>
                
                <label for="sistema">Sistema: </label>
                <select class="form-control" name="sistema">
                    <?php getSistems();?>
                </select>
                
                <label for="caso">Caso: </label>
                <select class="form-control" name="caso">
                    <option>R01-Medición del voltaje de la bateria del subsistema remoto</option>
                </select>

                <label for="fecha">Fecha: </label>
                <input type="date" class="form-control" name="fecha">
                
                <label for="archivo">Evidencia: </label>
                <input type="file" class="form-control" name="archivo">
                
                <label for="valorMedido">Valor medido: </label>
                <input type="number" class="form-control" name="valorMedido">
                
                <label for="observaciones">Observaciones:</label>
                <textarea class="form-control" rows="3" name="observaciones"></textarea>                
            </div>
        </div>
    </div>
</div>
<script src="../js/bootstrap.min.js"></script>    
</body>
</html>


