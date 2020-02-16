<?php
header('Content-Type: application/json');
    $response = array();
	include 'db_connect.php';
	include 'functions.php';
 
	//Get the input request parameters
	$inputJSON = file_get_contents('php://input');
	$input = json_decode($inputJSON, TRUE); //convert JSON into array
	if(isset($input['username'])&& isset($input['sensor'])){
			$username = $input['username'];
			$waterPump_status = $input['sensor'];
			if(userExists($username)){
					$query = "UPDATE garden f SET sensor_status = ?, created_date = CURRENT_TIMESTAMP WHERE f.user_id = (SELECT user_id FROM samet m WHERE m.username= ?)";
					if($stmt = $con->prepare($query)){
						$stmt->bind_param("is",$sensor_status ,$username);
						$stmt->execute();
						$response['sensor'] = 1; 
						$stmt->close();
						
						echo json_encode($response);
					}
				
			}
			else{
				$response['sensor'] = 0;
				echo json_encode($response);
			}
	}
?>
