<?php 
session_start(); 
require_once('db_conn.php');

if (isset($_POST['uname']) && isset($_POST['password'])) {
    function validate($data){ //function validates input when receiving it from post
       $data = trim($data);
       $data = stripslashes($data);
       $data = htmlspecialchars($data);
       return $data;
    }

    $uname = validate($_POST['uname']);
    $pass = validate($_POST['password']);

    //Validates user information and attempt to log in
    if (empty($uname)) {
        header("Location: index.php?error=Username is required");
        exit();
    } else if(empty($pass)){
        header("Location: index.php?error=Password is required");
        exit();
    } else {
        //select the row in database with the usernmae the user entered
        $sql = "SELECT * FROM UserCredentials WHERE username='$uname'";
        $result = mysqli_query($conn, $sql);
        if (mysqli_num_rows($result) === 1) { //if only one username is associated with the row fetched, continue with login 
            $row = mysqli_fetch_assoc($result);
            if (!password_verify($pass, $row['pass'])) { //verify password matches encrypted password stored in database
                header("Location: index.php?error=Incorect User name or password");
                exit();
            } else if (!($row['username'] === $uname)) {
                header("Location: index.php?error=Incorect User name or password");
                exit();
            } else {
                //set session variables to information stored in database
                $_SESSION['user_name'] = $row['username'];
                $_SESSION['id'] = $row['id']; 

                //$id = intval($_SESSION['id']);
                //$sql = "SELECT * FROM ClientInformation WHERE id=$id";
                $sql = "SELECT * FROM ClientInformation WHERE id={$_SESSION['id']}";
                $result2 = mysqli_query($conn, $sql);

                if (mysqli_num_rows($result2) === 1) { //if only one row is associated with the session id, we can continue and set the session name and address
                    $row2 = mysqli_fetch_assoc($result2);
                    $_SESSION['name'] = $row2['full_name'];
                    
                    if (empty($row2['address2']) || is_null($row2['address2'])) {
                        $fullAddress = $row2['address1'] . ', ' . $row2['city'] . ', ' . $row2['state'] . ' ' . $row2['zipcode'];
                        $_SESSION['full_address'] = $fullAddress;
                    } else {
                        $fullAddress = $row2['address1'] . ' ' . $row2['address2'] . ', ' . $row2['city'] . ', ' . $row2['state'] . ' ' . $row2['zipcode'];
                        $_SESSION['full_address'] = $fullAddress;
                    }

                    header("Location: fuelQuoteForm.php");
                    exit();
                } else if (mysqli_num_rows($result2) === 0) { //if no usernames are associated with the session id, the account needs to finish filling out profile information
                    header("Location: profileManagement.php?error=You must finish entering your information before you can order fuel.");
                    exit();
                } else {
                    header("Location: index.php?error=Incorect User name or password 2");
                    exit();
                }
                /*header("Location: fuelQuoteForm.php");
                exit();*/
            }
        } else {
            header("Location: index.php?error=Incorect User name or password");
            exit();
        }
    }
}else{
    header("Location: index.php");
    exit();
}

mysqli_close($conn);