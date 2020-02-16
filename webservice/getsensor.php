<?php
header('Content-Type: application/json');
    $response = array();
	include 'db_connect.php';
	include 'functions.php';
 
	//Get the input request parameters
	$inputJSON = file_get_contents('php://input');
	$input = json_decode($inputJSON, TRUE); //convert JSON into array
	if(isset($input['username'])){
		$username = $input['username'];
		if(userExists($username)){
			$query = "SELECT sensor_status FROM sensora WHERE a.user_id = (SELECT user_id FROM samet m WHERE m.username= ?) ORDER BY a.sensor_id DESC LIMIT 1";
			if($stmt = $con->prepare($query)){
				$stmt->bind_param("s",$username); // Binds variables to a prepared statement as parameters
				$stmt->execute();
				$stmt->bind_result($sensor_status); // Binds variables to a prepared statement for result storage
				while($stmt->fetch()){
					 $response['sensor'] = $sensor_status; 
					  
				}
				echo json_encode($response);
			}
		}
	}
?>