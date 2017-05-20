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
    <li class="active"><a href="#">Crear caso</a></li>
    <li><a href="generarReporte.php">Generar Reportes</a></li>
</ul>
<div class="container">
    <div class="row">
        <div class="col-sm-6 col-sm-offset-3">
            <h2>Nuevo Caso: </h2>
            <form action="casoResumen.php" method="post">
            <div class="form-group">
                <label for="Descripcion">Descripcion: </label>
                <input type="text" class="form-control" name="Descripcion" required>
                
                <label for="sistema">Sistema: </label>
                <select class="form-control" name="sistema">
                    <?php getSistems();?>
                </select>
                
                <label for="varMedir">Variable a medir: </label>
                <input type="text" class="form-control" name="varMedir" required>
                
                <label for="instrumentacion">Intrumentación necesaria: </label>
                <input type="text" class="form-control" name="instrumentacion" required>
                
                <label for="metodologia">Metodología:</label>
                <textarea class="form-control" rows="4" name="metodologia" required></textarea>
                
                <label for="valorEsperado">Valor esperado: </label>
                <input type="number" class="form-control" name="valorEsperado" required>
                
                <label for="unidades">Unidades: </label>
                <input type="text" class="form-control" name="unidades" required>
                
                <br><button value="crear" type="submit" class="btn btn-default form-control" name="button">Crear</button>
            </div>
            </form>
        </div>
    </div>
</div>
<script src="../js/bootstrap.min.js"></script>    
</body>
</html>