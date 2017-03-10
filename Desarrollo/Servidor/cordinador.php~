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

$navegador->SetLog(false);
ShowLog($navegador->Logged);
$navegador->SetLog(true);
ShowLog($navegador->Logged);

$action = $_POST["action"];
echo $action;
?>