<?php
// incluir los servicios de la base de datos
include 'ConnectDataBase.php'; 
//definciones
define('ACCIONES',['upload'=>'escribir','download'=>'leer']);
define('USCO_ID',2);
define('FINCA_ID',3);
//declaración de una clase que define los parametros del flujo de la navegacion
class navegacion
{
	public $UserID=NULL;
	public $UserName='';
	public $Logged=false;
	public $ActionList=[];
	public $ActionSel='';
	public $CordList=[];
	public $CordSel='';
	public $RemoteList=[];
	public $RemoteSel='';
	public $RemoteID=NULL;
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

	//setea el nombre de usuario en 
	public function setUserID($id) {
		$this->UserID=$id;
	}
	
	//busca en la base de datos el ID del usuario
	public function getUserID() {
		return $this->UserID;
	}
	
	//configura el nombre de usuario en la clase
	public function setUserName($name) {
		$this->UserName=$name;
	}
	
	//Devuelve el valor del nombre de usuario
	public function getUserName(){
		return $this->UserName;
	}
		
	//busca en la base de datos los permisos a los que tiene un usuario en función de la acción que va a efectuar
	public function getActionList() {
			$this->ActionList=queryActionList($this->UserName);
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
	
	public function setCordList() {
		$this->CordList=querryCordinator($this->UserName, $this->ActionSel);
	}
	
	public function getCordList(){
		return $this->CordList;
	}
	
	public function setCordSel($cordinator){
		$this->CordSel=$cordinator;
	}
	
	public function getCordSel() {
		return $this->CordSel;
	}

	public function setRemList() {	
	}
	
	public function getRemList() {
	}
		
	public function setVarList() {	
	}
	
	public function getVarList() {
	}
}


//Permite hace una validación al formulario de registro
function validar($nombre, $clave) {
	$cmp=false;
	$mysql=connect_database(); //socilita la conexion a la base de datos	
	if ($mysql){
		$query="SELECT UsuarioName, Password FROM Usuarios";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if((strcmp($row[0], $nombre)==0)&&(strcmp($row[1], $clave)==0)) {
				$cmp=true; // si enceuntra la combinacion de usuario y contraseña se pone en "true";
			}
		}
	}
	mysqli_close($mysql);	
	return $cmp;
}


// asocia un ID a un nombre de Usuario Determinado
function querryID($user) {
	$id=NULL; // inicializa la variable ID, la idea es buscarlos en base de datos
	$mysql=connect_database(); //socilita la conexion a la base de datos	
	if ($mysql){
		$query="SELECT UsuarioName, UsuarioID FROM Usuarios";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
			if(strcmp($row[0], $user)==0) {//determina si se encuentra el nombre
				$id=$row[1]; //devuelve el valor que se encuentra en el registro
			}
		}
	}
	mysqli_close($mysql);	
	return $id;
}

/********************************************************************
Obtiene un listado de las acciones a las que tiene permiso un usuario
*********************************************************************/
function queryActionList($UserName){
	$list=[];//Devuelve el valor de la lista de acciones del sujeto
	$mysql=connect_database(); //socilita la conexion a la base de datos	
	if ($mysql){
		$query="SELECT UsuarioName, permiso FROM Permisos";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
				if((strcmp($row[0], $UserName)==0)&&(strcmp($row[1], "escribir")==0)) {
					$list=array_merge($list,['action_1'=>'upload']);
				}
				if((strcmp($row[0], $UserName)==0)&&(strcmp($row[1], "leer")==0)) {
					$list=array_merge($list,['action_2'=>'download']);
				}
			}
		}
	mysqli_close($mysql);			
	return $list;
}

/***********************************************************
Selecciona un listado de cordinadores en los que un usuario 
puede desempeñar determinada función 
***********************************************************/
function querryCordinator($UserName, $action) {
	$opcion=ACCIONES[$action];
	$list=[]; //la lista inicialmente está vacía
	$mysql=connect_database(); //solicita la conexión a la base de datos	
	if ($mysql){
		$query="SELECT UsuarioName, permiso, CordinadorLugar FROM Permisos";
		$result=mysqli_query($mysql, $query);
		while($row=mysqli_fetch_row($result)){//busca en los valores a los que se les ha hecho el fetch
				if((strcmp($row[0], $UserName)==0)&&(strcmp($row[1], $opcion)==0)) {				
					$list=array_merge($list,[$row[2]]);
				}
			}
		}
	mysqli_close($mysql);
	return $list;
}

function queryRemoto($id,$action,$cord){
	$list=[];//variable que lista los remotos que perteneces a cada cordinador.
	switch($action) {
		case "download":
			$list=['suelos','tanque','ambiental'];
			break;
		case "upload":
			$list=['suelos','tanque'];
			break;
	}	
	return $list;
}

function ActionMask($action){
	$string="";
	if(strcmp($action, "download")==0){
		$string="Descargar datos";
	}
	elseif(strcmp($action, "upload")==0) {
		$string="Ingresar datos";
	}
	else {
		$string="";
	}
	return $string;	
}
?>