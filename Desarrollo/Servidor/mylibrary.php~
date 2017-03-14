<?php 
//definciones
define('USCO_ID',0001);
define('FINCA_ID',0002);
//declaración de una clase que define los parametros del flujo de la navegacion
class navegacion
{
	public $UserID=0;
	public $Logged=false;
	public $ActionList=[];
	public $ActionSel='';
	public $CordList=[];
	public $CordSel='';
	public $RemoteList=[];
	public $RemoteVar='';
	public $VariableList=[];
	public $VariableSel='';
	
	//muestra si estado de validación de registro del usuario
	public function getLog() {
		return $this->Logged;
	}
	//pone el valor de log /activado/desactivado dentro del objeto
	public function setLog($value) {
		$this->Logged=$value;
	}

	//busca en la base de datos el ID del usuario
	public function setUserID($id) {
		$this->UserID=$id;
	}
	
	//busca en la base de datos el ID del usuario
	public function getUserID() {
		return $this->UserID;
	}
	
	//busca en la base de datos los permisos a los que tiene un usuario en función de la acción que va a efectuar
	public function getActionList() {
		if(($this->UserID)==USCO_ID) {
			$this->ActionList=['download','upload'];
		}
		elseif(($this->UserID)==FINCA_ID) {
			$this->ActionList=['upload'];	
		}
		return $this->ActionList;
	}
	
	// pone en el campo de ActionSel la variable que seleccióno el usuario en el formulario
	public function setActionSel($action) {
		$this->ActionSel=$action;
	}
	
	// devuelve el valor de la accion que selecciono de la lista anterior
	public function getActionSel() {
		return $this->ActionSel;
	}	
}


//Permite hace una validación al formulario de registro
function validar($nombre, $clave) {	
	$cmp = false;
	if((strcmp($nombre, 'usco')==0 && strcmp($clave, 'usco123')==0) ||
		(strcmp($nombre, 'finca')==0 && strcmp($clave, 'finca123')==0)){
		$cmp=true;
	}
	else {
		$cmp=false;
	}
	
	return $cmp;		
}


// asocia un ID a un nombre de Usuario Determinado
function querryID($user) {
		$id=0; // inicializa la variable ID, la idea es buscarlos en base de datos
		if (strcmp($user, 'usco')==0){
			$id=USCO_ID;	
		}
		elseif(strcmp($user, 'finca')==0) {
			$id=FINCA_ID;		
		}
		return $id;
	}
?>