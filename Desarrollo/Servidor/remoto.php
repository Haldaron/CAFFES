
<?php
include "mylibrary.php";
// Start the session
session_start();
?>

<?php
function ShowLog($value) {
	if($value) {
		echo "el usuario se encuentra logueado"."<br>";
	}
	else {
		echo "el usuario no se encuentra logueado"."<br>";
	}
}
?>

<?php
	echo "<h2> prueba de persistencia de las variables de la sesion </h2>";
?>

<?php
$navegador=$_SESSION["nav"];
ShowLog($navegador->getLog());
echo "ID: ".$navegador->getUserID()."<br>";

$lista = $navegador->getActionList();
foreach ($lista as $act){
	echo "acción : ".$act."<br>";
}


?>