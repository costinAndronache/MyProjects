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
		<title>Strategic Warfare: FAQ</title>
		<link href="Stiluri/FAQ-Style.css" rel="stylesheet" type="text/css" />
	</head>
	<body>

		<header>
			<h1>Strategic Warfare</h1>
			<h3>Nimiceste-ti adversarii!</h3>
		</header>

		<nav>
			<a href="Home.php">Home</a><br>
			<a href="Logare.php">Logare</a><br>
			<a href="Wiki.php">Wiki</a><br>
			<a href="Contact.php">Contact</a><br>
		</nav>

		<section>
			<p>
				<ul>
					<li>
						Ce reprezinta acest joc?
					</li>
					Strategic Warfare este un proiect realizat de o grupa de studenti in numar trei persoane.
				</ul>
				<ul>
					<li>
						Va trebui sa cumpar acest joc?
					</li>
					Aceasta decizie ramane la hotararea facultatii. Studentii care dezvolta produsele in cadrul universtitatii nu au drepturi de autor la
					aplicatiile lor.
				</ul>
				<ul>
					<li>
						Cand va fi eliberat jocul?
					</li>
					Intentionam sa eliberam jocul pe 31 mai 2015.
				</ul>
				<ul>
					<li>
						De unde fac rost de joc?
					</li>
					Ve-ti putea downloada direct acest joc de pe site-ul nostru.
				</ul>
				<ul>
					<li>
						Ce dezvoltati, mai concret?
					</li>
					Strategic Warfare va fi un RTS minimal.
				</ul>
				<ul>
					<li>
						De ce aveti un gameplay mai dezvoltat? Si de ce grafica lasa de dorit?
					</li>
					Suntem o echipa mica formata din trei persoane iar Strategic Warfare este primul joc online pe care il dezvoltam. Astfel se justifica,
					grafica primitiva si gameplay-ul simplist.
				</ul>
				<ul>
					<li>
						Veti sustine jocul dupa dezvoltare cu patch-uri?
					</li>
					Nu. Acest lucru nu va fi posibil, din moment ce proiectul va fi predat facultatii. Aceasta asumandu-si drepturile de autor ar putea sustine
					jocul cu patch-uri, dar ramane tot la decizia ei.
				</ul>
			</p>
		</section>

		<footer>
			© 2015 TrioGate Studios. Toate drepturile sunt rezervate.
		</footer>

	</body>
</html>
