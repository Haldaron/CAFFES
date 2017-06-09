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
function listCases(){
    $mysqli=connect_database();
    if($mysqli){
        $query='SELECT * FROM casos';
        $result=mysqli_query($mysqli, $query);
        while($row=mysqli_fetch_row($result)){
                    
                echo '<h3>['.$row[0].'] '.$row[1].'</h3>';
                
                echo '<table class="table table table-striped">';
                echo '<tr>';
                    echo '<td><b>Sistema:</b></td>';
                    echo '<td>'.$row[2].'</td>';
                echo '</tr>';

                echo '<tr>';
                    echo '<td><b>variable:</b></td>';
                    echo '<td>'.$row[3].'</td>';
                echo '</tr>';

                echo '<tr>';
                    echo '<td><b>intrumentación:</b></td>';
                    echo '<td>'.$row[4].'</td>';
                echo '</tr>';

                echo '<tr>';
                    echo '<td><b>metodología:</b></td>';
                    echo '<td>'.$row[5].'</td>';
                echo '</tr>';

                echo '<tr>';
                    echo '<td><b>valor:</b></td>';
                    echo '<td>'.$row[6].'</td>';
                echo '</tr>';
                
                echo '<tr>';
                    echo '<td><b>unidad:</b></td>';
                    echo '<td>'.$row[7].'</td>';
                echo '</tr>';

                echo '</table>';
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
    <li><a href="crearCaso.php">Crear caso</a></li>
    <li class="active"><a href="#">Generar Reportes</a></li>
</ul>
<div class="container">
    <div class="row">
        <div class="col-sm-4">
            <h2>Resumen de casos: </h2>
            <div class="form-group">
                <?php listCases();?>
            </div>
        </div>
    </div>
</div>
<script src="../js/bootstrap.min.js"></script>    
</body>
</html>


