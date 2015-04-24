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

<!DOCTYPE html>
<html>
	<head>
		<title>Strategic Warfare: Contact</title>
		<link href="Stiluri/Contact-Style.css" rel="stylesheet" type="text/css" />
	</head>
	<body>

		<header>
			<h1>Strategic Warfare</h1>
			<h3>Nimiceste-ti adversarii!</h3>
		</header>

		<nav>
			<a href="Home.php">Home</a><br>
			<a href="Logare.php">Logare</a><br>
			<a href="FAQ.php">FAQ</a><br>
			<a href="Wiki.php">Wiki</a><br>
		</nav>

		<section>
			<p>
				<ul>
					<li>
						Andronache Costin
					</li>
					Nr telefon:<br>
					Adresa email:<br>
				</ul>
				<ul>
					<li>
						Preisler Raluca
					</li>
					Nr telefon:<br>
					Adresa email:<br>
				</ul>
				<ul>
					<li>
						Mocanu Nicolae
					</li>
					Nr telefon:<br>
					Adresa email:<br>
				</ul>
			</p>
		</section>

		<footer>
			© 2015 TrioGate Studios. Toate drepturile sunt rezervate.
		</footer>

	</body>
</html>
