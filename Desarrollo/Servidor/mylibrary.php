<?php 
//declaración de una clase que define los parametros del flujo de la navegacion
class navegacion
{
	public $UserID=0;
	public $Logged=false;
	public $ActionList=array();
	public $ActionSel="";
	public $CordList=array();
	public $CordSel="";
	public $RemoteList=array();
	public $RemoteVar="";
	public $VariableList=array();
	public $VariableSel="";
}

?>

<?php
//Permite hace una validación al formulario de registro
function validar($nombre, $clave) 
{	
	$cmp = false;
	if((strcmp($nombre, "usco")==0 && strcmp($clave, "usco123")==0) ||
		(strcmp($nombre, "finca")==0 && strcmp($clave, "finca123")==0))  {
		$cmp=true;
	}
	else {
		$cmp=false;
	}
	
	return $cmp;		
}
?>