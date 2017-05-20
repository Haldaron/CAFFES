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

function getSystemID($system){
    $id=0;
    $mysqli=connect_database();
    if($mysqli){
        $query='SELECT Nombre, sistemaID FROM Sistemas';
        $result=mysqli_query($mysqli, $query);
        while($row=mysqli_fetch_row($result)){
            if (strcmp($row[0], $system)==0){
                $id=$row[1];
            }
        }
    }
    mysqli_close($mysqli);
    return $id;
}

/*lectura de las variables que compoenen el formulario*/
$descripcion=$_POST['Descripcion'];
$sistema=$_POST['sistema'];
$varMedir=$_POST['varMedir'];
$instrumentacion=$_POST['instrumentacion'];
$metodologia=$_POST['metodologia'];
$valorEsperado=$_POST['valorEsperado'];
$unidades=$_POST['unidades'];

$query="INSERT INTO casos (caseID, descripcion, sistema, varMed, intrumentacion, metodogia, valEsperado, Unidades) 
        VALUES (NULL,
        '".$descripcion."',
        ".getSystemID($sistema).",
        '".$varMedir."',
        '".$instrumentacion."',
        '".$metodologia."',
        ".$valorEsperado.",
        '".$unidades."')";
        

        $mysqli=connect_database();
        if($mysqli){
            mysqli_query($mysqli, $query);
            mysqli_close($mysqli);
        }
echo $query;
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
        <div class="col-sm-8 col-sm-offset-2">
            <table class="table table table-striped"">
                <tr> 
                    <td><b>Descripción:</b></td>
                    <td><?php echo $descripcion;?></td>
                </tr>
                <tr> 
                    <td><b>Sistema:</b></td>
                    <td><?php echo $sistema;?></td>
                </tr>
                <tr> 
                    <td><b>Variable:</b></td>
                    <td><?php echo $varMedir;?></td>
                </tr>
                <tr> 
                    <td><b>Instrumentación:</b></td>
                    <td><?php echo $instrumentacion;?></td>
                </tr>
                <tr> 
                    <td><b>Metodología:</b></td>
                    <td><?php echo $metodologia;?></td>
                </tr>
                <tr> 
                    <td><b>Valor esperado:</b></td>
                    <td><?php echo $valorEsperado;?></td>
                </tr>
                <tr> 
                    <td><b>Unidad:</b></td>
                    <td><?php echo $unidades;?></td>
                </tr>
            </table>
            <form action="crearCaso.php">
                <br><button value="continuar" type="submit" class="btn btn-default form-control" name="button">Continuar</button>
            </form>
        </div>
    </div>
</div>
<script src="../js/bootstrap.min.js"></script>    
</body>
</html>
