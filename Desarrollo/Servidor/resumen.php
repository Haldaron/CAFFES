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

/*leer las variables que el usuario selecciono*/
//$variables=['pH,'suelo_temperatura']:
//$nav->setVarSel($variable);

$variables=$_POST['variable']; //lista de las variables que se van a descargar
$nav->setVarSel($variables); //set the variable list


$resultFileName=setFileName($nav);

$resultFile="~/Desktop/results.xlsx";

$convert="ssconvert --merge-to=".$resultFile;
foreach ($variables as $fila){
    $archivo=$fila.'.csv';// crea el archivo de la variable seleccionada    
    $file = fopen($archivo,'w'); // dejo abierto un archivo
    $result=getTableData($fila);
    while($row=mysqli_fetch_row($result)){
        fputcsv($file,$row);
    }
    fclose($file); //cierra el archivo
    //revisa si hay uno o mas variables seleccionadas
    if(count($variables)==1){
        $convert='ssconvert'.' '.$archivo.' '.$resultFile;
    }
    else{
        $convert.=' '.$archivo;
    }
}
system('rm '.$resultFile);//borra el archivo anteriores
system($convert);   //crea un nuevo archivo con la solicitud
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
    <link rel="stylesheet" href="estilos.css" type="text/css" media="all">
</head>
<body>
	<!-- Librería jQuery requerida por los plugins de JavaScript -->
   <script src="http://code.jquery.com/jquery.js"></script>

	<!-- Header de la página  -->	
	<div class="container">
	<div class="page-header"><h3>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL<br><small> LA PLATA, HUILA, CENTRO ORIENTE</small></h3></div>
	</div>
	<!-- Primera fila del diseño -->
	<div class="container">
	<div class="row">
		<!-- Formulario de registro de usuarios -->
		<!-- imagen de referencia -->
		<div class="col-sm-6">
			<img src="./imagenes/finca.jpg" class="img-thumbnail img-responsive" alt="Imagen responsive">
		</div>
		<!-- formulario de registro -->	
		<div class="col-sm-6">
                    <a href="<?php echo $resultFile;?>" class="miboton" download="<?php echo $resultFileName;?>">
                        <button class="buttondwn"><b>Descargar</b></button>
                    </a>
		</div>
	</div>
	</div>
	<script src="js/bootstrap.min.js"></script>
</body>
</html>