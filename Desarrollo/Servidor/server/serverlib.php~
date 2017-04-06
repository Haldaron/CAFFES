<?php
//clase que permite hacer la carga automatica de los datos
class ServicioAutomatico {
	public $usuario=NULL;
	public $clave=NULL;
	public $cordID=NULL;
	public $remID=NULL;
	public $varName="";
	public $filename="";
	public $errorMessage="";
	
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
	public function setCordPlace($cord) {
		$this->cordID=$cord;
	}
	public function getCordPlace() {
		return $this->cordID;
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
	}
}

?>