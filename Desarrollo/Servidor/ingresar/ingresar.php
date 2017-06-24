<?php
include '../mylibrary.php';
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

<?php
if(isset($_GET["password"])){
    $password=$_GET["password"];
}
if(isset($_GET["usuario"])){
    $usuario=$_GET["usuario"];
    if(!empty($usuario)){
        $nav->setUserName($usuario);
        $_SESSION['navigator']=$nav;
    }
}
if(validar($nav->getUserName(),$password)){
    header('Location: ingresar.php');
}
?>
<!DOCTYPE html>

<head>
	<title>proyecto CAFFES</title>
	<meta name="generator" content="Bluefish 2.2.7" >
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link href="../css/bootstrap.min.css" rel="stylesheet" media="screen">
	<link rel="stylesheet" href="../estilos.css" type="text/css" media="all">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
	<script src="../jquery-labelauty/source/jquery-labelauty.js"></script>
	<link rel="stylesheet" type="text/css" href="../jquery-labelauty/source/jquery-labelauty.css">	
</head>

<body>
<!-- Librería jQuery requerida por los plugins de JavaScript -->
<!--<script src="http://code.jquery.com/jquery.js"></script>->
        <!-- Header de la página  -->	
        <div class="container">
            <div class="page-header"><h3>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL</div>
        </div>
        
        <div class="container">
            <form  method="GET" action="<?php echo $_SERVER['PHP_SELF']?>" enctype="multipart/form-data">
                <div class="col-sm-8">
                    <div class="form-group">
                        <!--division para la selección de sistemas-->
                        <div class="row">
                            <div class="col-sm-6">
                                <label for="sistema">Sistema:</label>
                                <input class='radio-inline' type='radio' name='sistema' value='sistema' data-labelauty='beneficiadero' checked onclick="enableTemp()">
                                <input class='radio-inline' type='radio' name='sistema' value='sistema' data-labelauty='cultivo' onclick="disableTemp()">
                            </div>
                            <div class="col-sm-6">
                                <label for="variable">variable:</label>
                                <input class='radio-inline' type='radio' name='variable' value='variable' data-labelauty='temperatura' id="temp">
                                <input class='radio-inline' type='radio' name='variable' value='variable' data-labelauty='pH' checked id="pH">
                            </div>
                        </div>
                        <!--division para la selección de fecha-->
                        <div class="row">
                            <div class="col-sm-12">
                                <label for="fecha">fecha:</label>
                                <input class="form-control" type="date" name="fecha"/> 
                            </div>
                            <div class="col-sm-12">
                                <label for="hora">hora:</label>
                                <input class="form-control" type="time" name="hora">
                            </div>
                        </div>
                </div>
                </div>
                <div class="col-sm-4">
                        <!--division para insertar el valor-->
                        <div class="row">
                            <label for="NumberValue">valor:</label>
                            <input type="text" class="form-control panel" id="NumberValue" name="variable">
                        </div>
                        
                    <div class="row">
                        <div class="btn-group btn-group-justified">
                            <a class="btn btn-default" onclick="appendNumber('1')"><strong>1</strong></a>
                            <a class="btn btn-default" onclick="appendNumber('2')"><strong>2</strong></a>
                            <a class="btn btn-default" onclick="appendNumber('3')"><strong>3</strong></a>
                        </div>
                    </div>
                    <div class="row">
                        <div class="btn-group btn-group-justified">
                            <a class="btn btn-default" onclick="appendNumber('4')"><strong>4</strong></a>
                            <a class="btn btn-default" onclick="appendNumber('5')"><strong>5</strong></a>
                            <a class="btn btn-default" onclick="appendNumber('6')"><strong>6</strong></a>
                        </div>
                    </div>
                    <div class="row">
                        <div class="btn-group btn-group-justified">
                            <a class="btn btn-default" onclick="appendNumber('7')"><strong>7</strong></a>
                            <a class="btn btn-default" onclick="appendNumber('8')"><strong>8</strong></a>
                            <a class="btn btn-default" onclick="appendNumber('9')"><strong>9</strong></a>
                        </div>
                    </div>
                    <div class="row">
                        <div class="btn-group btn-group-justified">
                            <a class="btn btn-default" onclick="setPoint()"><strong>.</strong></a>
                            <a class="btn btn-default" onclick="appendNumber('0')"><strong>0</strong></a>
                            <a class="btn btn-default" onclick="backspace()"><img src="../imagenes/backspace.svg"/></a>
                        </div>
                    </div>
                    <div class="row">
                        <button value="ingresar" type="submit" class="btn btn-default form-control" name="button"><strong>Ingresar</strong></button>
                    </div>                    
                </div>
            </form>
        </div>
        <script type="text/javascript">
           function appendNumber(N){
                document.getElementById('NumberValue').value+=N;
           }
           
           function backspace(){
                var value=document.getElementById('NumberValue').value;
                var bs_value= value.slice(0,value.length-1);
                document.getElementById('NumberValue').value=bs_value;
           }
           
           function setPoint(){
                var value=document.getElementById('NumberValue').value.match(/./g);
                if (value.length<=2){
                    document.getElementById('NumberValue').value+=".";
                }
           }
           function disableTemp() {
                document.getElementById("temp").disabled = true;
                if(document.getElementById("temp").checked){
                        document.getElementById("pH").checked=true;
                        document.getElementById("temp").checked=false;
                }                
           }
           function enableTemp() {
                document.getElementById("temp").disabled = false;
           }           
           $(document).ready(function(){
                    $(":checkbox").labelauty();
                    $(":radio").labelauty();
            });
        </script>
</body>
</html>