<?php 
	session_start();
	include_once("config.php");
	if(!isset($_SESSION['email']))
	{
        $_SESSION['email'] = "vizitator";
        echo "Utilizator nelogat.";
    }
    
    else echo "Utilizator: ". $_SESSION['email'];
?>
<!-- <br><input type="submit" name="delogare" value="DELOGARE" title="Apasati pentru a va deloga" onclick="location.href='Home.php'">
<?php
    	if(isset($_POST['delogare'])){
    		//unset($_SESSION);
    		$_SESSION['login']=false;
    		unset($_SESSION['delogare']);
    		}
 ?> -->

<?php if( !(isset( $_POST['login'] ) ) ) { ?>
<!DOCTYPE html>
<html>
    <head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<title>Login to TrioGate Studios</title>
		<link href="Stiluri/Logare-Style.css" rel="stylesheet" type="text/css" />
	</head>
    <body>
   
		<header>
			<h2>TrioGate Studios: Logare</h2>
		</header>
		
		<nav>
			<a href="Home.php">Home</a><br>
			<a href="FAQ.php">FAQ</a><br>
			<a href="Wiki.php">Wiki</a><br>
			<a href="Contact.php">Contact</a><br>
		</nav>
		
		<section>
			<form method="post" action="">

				<p>Email: <input type="text" maxlength="30" required autofocus name="email" /> </p>

				<p>Parolă: <input type="password" maxlength="30" required name="password" /> <p>
			
				<p><a href="#">V-ați uitat parola?</a></p>
		
				<p>
					<input type="submit" name="login" value="LOGIN" title="Apasati pentru a expedia datele spre server"/>
					<input type="button" name="register" value="Înregistrare" onclick="location.href='Inregistrare.php'" title="Mergeti pe pagina de inregistrare"/>
				</p>

			</form>
		</section>
		
		<footer>
			<p>© 2015 TrioGate Studios. Toate drepturile sunt rezervate.</p>
		</footer>
    
    </body>
</html>

<?php 
} else {
	$user=new User;
	$user->storeFormValues($_POST);
	$email=$_POST["email"];

	
	if($user->userLogin()){
		echo "Logare realizata cu succes!";	
		?>
		<br><a href="Home.php">Click pentru a merge pe pagina principala</a>
		<?php 

	$_SESSION['login'] = true;
	$_SESSION['email']=$email;

	}else{
		echo "Combinație greșită Email&Parolă";	
	}
}
?>