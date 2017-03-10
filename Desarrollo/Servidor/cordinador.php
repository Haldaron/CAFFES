<?php
include "mylibrary.php";

$navegador= new navegacion;

function ShowLog($value) {
	if($value) {
		echo "el usuario se encuentra logueado"."<br>";
	}
	else {
		echo "el usuario no se encuentra logueado"."<br>";
	}
}

echo "<h2>Pruebas de la funcion SetLog/getLog</h2>"."<br>";
$navegador->setLog(false);
ShowLog($navegador->getLog());
$navegador->setLog(true);
ShowLog($navegador->getLog());

echo "<h2>Pruebas de la funcion Action List </h2>"."<br>";

$user="usco";
$id=querryID($user);
echo "la identificación del usuario ".$user." es: ".$id."<br>";
$navegador->setUserID($id);
echo "ID: ".$navegador->getUserID()."<br>";

$lista = $navegador->getActionList();
foreach ($lista as $act){
	echo "acción : ".$act."<br>";
}

$action = $_POST["action"];

$navegador->setActionSel($action);
echo "la opción seleccionada es: ". $navegador->ActionSel."<br>";
?>