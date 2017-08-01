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

<!DOCTYPE html>

<head>
	<title>proyecto CAFFES</title>
	<meta name="generator" content="Bluefish 2.2.7" >
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<html lang="es">
	<link href="../css/bootstrap.min.css" rel="stylesheet" media="screen">
	<link rel="stylesheet" href="../estilos.css" type="text/css" media="all">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
	<script src="../jquery-labelauty/source/jquery-labelauty.js"></script>
	<script src="clockpicker-gh-pages/dist/bootstrap-clockpicker.min.js"></script>
	<link rel="stylesheet" type="text/css" href="../jquery-labelauty/source/jquery-labelauty.css">
	<link rel="stylesheet" type="text/css" href="clockpicker-gh-pages/assets/css/bootstrap.min.css">
        <link rel="stylesheet" type="text/css" href="clockpicker-gh-pages/dist/bootstrap-clockpicker.min.css">
        <link rel="stylesheet" type="text/css" href="clockpicker-gh-pages/assets/css/github.min.css">
</head>

<body>
<!-- Librería jQuery requerida por los plugins de JavaScript -->
<!--<script src="http://code.jquery.com/jquery.js"></script>->
        <!-- Header de la página  -->	
        <div class="container">
            <div class="page-header"><h3>INVESTIGACIÓN DE LAS CONDICIONES DE CONTROL DE LA CALIDAD DE CAFÉ ESPECIAL</div>
        </div>
        
        <div class="container">
            <form  method="GET" action="confirmar.php" enctype="multipart/form-data" onsubmit="confirmar()">
                <div class="col-sm-8">
                    <div class="form-group">
                        <!--division para la selección de sistemas-->
                        <div class="row">
                            <div class="col-sm-6">
                                <label for="sistema">Sistema:</label>
                                <input class='radio-inline' type='radio' name='sistema' value='beneficiadero' data-labelauty='beneficiadero' checked onclick="enableTemp()" required>
                                <input class='radio-inline' type='radio' name='sistema' value='cultivo' data-labelauty='cultivo' onclick="disableTemp()" required>
                            </div>
                            <div class="col-sm-6">
                                <label for="medicion">variable:</label>
                                <input class='radio-inline' type='radio' name='medicion' value='temperatura' data-labelauty='temperatura' id="temp" onclick="setUnitTemp()" required>
                                <input class='radio-inline' type='radio' name='medicion' value='pH' data-labelauty='pH' checked id="pH" onclick="setUnitpH()" required>
                            </div>
                        </div>
                        <!--division para la selección de fecha-->
                        <div class="row">
                            <div class="col-sm-12">
                                <label for="fecha">fecha:</label>
                                <input class="form-control" type="date" name="fecha" lang="es" required /> 
                            </div>
                            <div class="col-sm-12">
                                <label for="hora">hora:</label>
                                <div class="input-group clockpicker" data-autoclose="true">
                                   <input type="text" class="form-control"  value="06:00" required name="hora">
                                        <span class="input-group-addon">
                                            <span class="glyphicon glyphicon-time"></span>
                                        </span>
                                </div>
                            </div>
                        </div>
                </div>
                </div>
                <div class="col-sm-4">
                        <!--division para insertar el valor-->
                        <div class="row">
                            <div class="col-sm-10">
                                <div class="row">
                                <!--<label for="NumberValue">valor:</label>-->
                                <input type="text" class="form-control panel" id="NumberValue" name="variable" required>
                                </div>
                            </div>
                            <div class="col-sm-2">
                                <div class="row">
                                <a class="btn btn-default" id="units">pH</a>
                                </div>
                            </div>
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
			<div class="col-sm-4"><div class="row"><a class="btn btn-default form-control" onclick="cancelar()"><strong>cancelar</strong></a></div></div>
                        <div class="col-sm-8"><div class="row"><button value="ingresar" type="submit" class="btn btn-default form-control" name="button"><strong>Ingresar</strong></button></div></div>
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
                        document.getElementById("units").innerHTML="pH";
                }                
           }
           function enableTemp() {
                document.getElementById("temp").disabled = false;
           }
           function setUnitTemp() {
                document.getElementById("units").innerHTML="°C";
           }
           function setUnitpH() {
                document.getElementById("units").innerHTML="pH";
           }           
           function cancelar() {
		window.location="index.php";
	   }
	   function confirmar() {
		alert("¡Su dato ha sido guardado de forma exitosa!");
	   }	           
           $(document).ready(function(){
                    $(":checkbox").labelauty();
                    $(":radio").labelauty();
            });
            
            $('.clockpicker').clockpicker();
        </script>
</body>
</html>
