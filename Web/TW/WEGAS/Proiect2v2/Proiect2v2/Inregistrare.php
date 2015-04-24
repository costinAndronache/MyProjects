<?php
	session_start();
	include_once("config.php");
	if(!isset($_SESSION['email']))
	{
        $_SESSION['email'] = "vizitator";
        echo "Utilizator nelogat.";
    }
     echo "Utilizator: ". $_SESSION['email'];
?>


<?php if( !(isset( $_POST['register'] ) ) ) { ?>

<!DOCTYPE html>
<html>
    <head lang="ro">
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<title>Join to TrioGate Studios</title>
		<link href="Stiluri/Logare-Style.css" rel="stylesheet" type="text/css" />
	</head>
    
    <body>
	
		<header>
			<h2>TrioGate Studios: Înregistrare</h2>
		</header>
		
		<nav>
			<a href="Home.php">Home</a><br>
			<a href="FAQ.php">FAQ</a><br>
			<a href="Wiki.php">Wiki</a><br>
			<a href="Contact.php">Contact</a><br>
		</nav>

		<section>
			<form method="post">
			
				<p>Username: <input type="text" id="usn" maxlength="30" required autofocus name="username" /></p>

				<p>Email: <input type="text" id="email" maxlength="30" required name="email" /></p>

				<p>Parola: <input type="password" id="passwd" maxlength="30" required name="password" /></p>

				<p>Confirmați parola: <input type="password" id="conpasswd" maxlength="30" required name="conpassword" /></p>

				<p>
					<input type="submit" name="register" value="Înregistrare" />
					<input type="button" name="cancel" value="Anulați" onclick="location.href='Logare.php'" />
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
	
	if( $_POST['password'] == $_POST['conpassword'] ) {
		echo $user->register($_POST);	
	} else {
		echo "Cele doua parole nu corespund.";	
	}
}
?>