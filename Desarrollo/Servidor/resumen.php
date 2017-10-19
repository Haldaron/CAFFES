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
$variables=$_POST['variable']; //lista de las variables que se van a descargar
$nav->setVarSel($variables); //set the variable list

//calcula el ID del remoto que se selecciono
$remote=$nav->getRemSel();
$list=$nav->getRemList();
$remID=$list[$remote][0]; // el indice 0 cambia en caso de instalar mas remotos por finca.

$resultFileName=setFileName($nav);
$resultFile='results.xlsx';

$convert="ssconvert --merge-to=".$resultFile;
foreach ($variables as $fila){
    $archivo=$fila.'.csv';// crea el archivo de la variable seleccionada    
    $file = fopen($archivo,'w'); // dejo abierto un archivo
    $result=getTableData($fila,$remID);
    while($row=mysqli_fetch_row($result)){
        switch($fila){
            case 'suelo_temperatura':
                $row[2]=volt2Temp(lsb2Volt("temp", $row[2]));
            break;                        
            
            case 'metereologico_radiacion_PAR':
                $row[2]=volt2PAR(lsb2Volt("par", $row[2]));
                $row[3]="umol/m2s";
            break;
            
            case 'suelo_humedad':
                $volt=lsb2Volt("hum", $row[2]);
                switch($remID){
                    case 5:
                        $row[2]=volt2Hum($volt,COEFAFINCA5,COEFBFINCA5);
                    break;
                    case 6:
                        $row[2]=volt2Hum($volt,COEFAFINCA6,COEFBFINCA6);
                    break;
                    case 7:
                        $row[2]=volt2Hum($volt,COEFAFINCA7,COEFBFINCA7);
                    break;
                    case 8:
                        $row[2]=volt2Hum($volt,COEFAFINCA8,COEFBFINCA8);
                    break;
                    case 9:
                        $row[2]=volt2Hum($volt,COEFAFINCA9,COEFBFINCA9);
                    break;
                    case 10:
                        $row[2]=volt2Hum($volt,COEFAFINCA10,COEFBFINCA10);
                    break;
                    case 11:
                        $row[2]=volt2Hum($volt,COEFAFINCA11,COEFBFINCA11);
                    break;
                    case 12:
                        $row[2]=volt2Hum($volt,COEFAFINCA12,COEFBFINCA12);
                    break;
                    case 13:
                        $row[2]=volt2Hum($volt,COEFAFINCA13,COEFBFINCA13);
                    break;
                    case 14:
                        $row[2]=volt2Hum($volt,COEFAFINCA14,COEFBFINCA14);
                    break;                   
                }
            break;
            default:
                $row[2]=$row[2];
            break;
        }
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
                <li><a href="remoto.php">remotos</a></li>
                <li><a href="variable.php">variables</a></li>
                <li class="active"><a href="#">resumen</a></li>
                </ul>
            </div>
            </nav>
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
                    <!--<a href="<?php echo $resultFile;?>" class="miboton" download="<?php echo $resultFileName;?>">-->
                        <button class="buttondwn"><b>Descargar</b></button>
                    </a>
		</div>
	</div>
	</div>
	<script src="js/bootstrap.min.js"></script>
</body>
</html>
<?php else: ?>
	<?php header("Location: index.php"); ?>
<?php endif;?>	
