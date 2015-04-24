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
		<title>Strategic Warfare: Home</title>
		<link href="Stiluri/Home-Style.css" rel="stylesheet" type="text/css" />
	</head>
	<body>


		<header>
			<h1>Strategic Warfare</h1>
			<h3>Nimiceste-ti adversarii!</h3>
		</header>

		<nav>
			<a href="Logare.php">Logare</a><br>
			<a href="FAQ.php">FAQ</a><br>
			<a href="Wiki.php">Wiki</a><br>
			<a href="Contact.php">Contact</a><br>
		</nav>

		<section>
			<p>
				<div id="buton" class="centru">
					<p><a href="Logare.php">JOACA ACUM!</a></p>
				</div>
			</p>
			<p>
				<div id="introducere-paragraf" class="centru">
					Te afli pe un teren inospitalier concurentei. Te gasesti printre fortele care doresc sa-ti nege dominanta militara si strategica. Trebuie sa
					aduni resurse, creezi aliante si sa-ti demonstrezi capacitatea de a detine monopolul in lupta strategica. Noi iti oferim toate constructiile,
					unitatile si tehnologiile militare. Esti in stare sa-ti afirmi competivitatea?
				</div>
			</p>
			
			<div class="centru">
				<h2>Galerie Media</h2>

				<ul style="list-style-type: none">
					<li>
						<img src="Imagini/imagine-home-1.jpg" alt="" width="100">
					</li>
					<li>
						<img src="Imagini/imagine-home-2.jpg" alt="" width="100">
					</li>
					<li>
						<img src="Imagini/imagine-home-3.jpg" alt="" width="100">
					</li>
					<li>
						<img src="Imagini/imagine-home-4.jpg" alt="" width="100">
					</li>
				</ul>
			</div>
		</section>

		<footer>
			© 2015 TrioGate Studios. Toate drepturile sunt rezervate.
		</footer>

	</body>
</html>
