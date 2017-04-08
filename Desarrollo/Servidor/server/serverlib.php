<?php define("TOKEN_FILE",","); ?>
<?php define("TOKEN_BEGIN",'dummy,'); ?>
<?php define("TOKEN_REMOTE_TYPE","_"); ?>
<?php
//clase que permite hacer la carga automatica de los datos
class ServicioAutomatico {
	public $usuario=NULL;
	public $clave=NULL;
	public $cordID=NULL;
	public $remID=NULL;
	public $varName="";
	public $remoteTable="";
	public $remoteID=NULL;
	public $filename="";
	public $errorMessage="";
	public $estructura=[];	
	
	public function setUserName($name) {
		$this->usuario=$name;
	}
	public function getUserName() {
		return $this->usuario;
	}
	public function setPassword($password) {
		$this->clave=$password;
	}
	public function getPassword() {
		return $this->clave;
	}
	public function setCordID($cord) {
		$this->cordID=$cord;
	}
	public function getCordID() {
		return $this->cordID;
	}
	public function setVariable($var){
		$this->varName=$var;	
	}	
	public function getVariable() {
		return $this->varName;	
	}
	public function setRemoteTable() {
		$remote=strtok($this->varName,TOKEN_REMOTE_TYPE);//saca la parte del string que indica el remoto
		$tableName='';		
		switch($remote) {
			case 'suelo':
				$tableName='RemotoSuelos';
				break;
			case 'tanque':
				$tableName='RemotoTanques';
				break;
			case 'metereologico':
				$tableName='RemotoMetereologico';
				break;			
		}
		$this->remoteTable= $tableName;
	}
	public function getRemoteTable() {
		return $this->remoteTable;
	}
	public function setRemoteID($remID){		
		$this->remoteID=$remID;	
	}	
	public function getRemoteID() {
		return $this->remoteID;	
	}
	public function setFilename($fm) {
		$this->filename=$fm;
	}
	public function getFilename() {
		return $this->filename;
	}		
	public function getErrorMessage() {
		return $this->errorMessage;
	}
	public function setErrorMessage($msg) {
		$this->errorMessage=$msg;
	}
	public function clearForm() {
		$this->usuario=NULL;
		$this->clave=NULL;
		$this->cordID=NULL;
		$this->remID=NULL;
		$this->varName="";
		$this->filename="";
		$this->errorMessage="";
		$this->estructura=[];
	}
	public function getStructure(){
		$this->estructura['tanque'][]='pH';
		$this->estructura['tanque'][]='temperatura';
		$this->estructura['suelo'][]='pH';
		$this->estructura['suelo'][]='temperatura';
		$this->estructura['suelo'][]='humedad';
		$this->estructura['metereologico'][]='precipitacion';
		$this->estructura['metereologico'][]='radiacion_PAR';
		$this->estructura['metereologico'][]='temperatura';
		$this->estructura['metereologico'][]='humedad';
		$this->estructura['metereologico'][]='brillo_solar';
		$this->estructura['metereologico'][]='direccion_viento';
		$this->estructura['metereologico'][]='velocidad_viento';	
		return $this->estructura;
	}
	public function setQuery($fila){
		$query="INSERT INTO ";//directiva que pide insertar valores a la tabla
		$tableFields=getTableColumns($this->varName);
		$query.=$this->varName." ("; //señala la tabla en la que se van a insertar los datos
		/*Concatena los campos de la tabla*/		
		foreach($tableFields as $index=>$field){
			$query.=" ".$field;
			if($index<sizeof($tableFields)-1) {
				$query.=",";
			}
			else {
				$query.=")";
			}	
		}
		/*inserta los valores de la tabla*/
		$query.= " VALUES (";
		$query.= " NULL,"; //el primer dato es nulo para que autoidente en la tabla
		$value=strtok($fila,TOKEN_FILE);		
		while($value=strtok(TOKEN_FILE)){//lee todos los campos separados por el TOKEN ","
			$query.=	" '".$value."',";	
		}
		$query.="'".$this->remoteID."')";
		return $query;
	}
}
?>