<?php
	echo "Para acceder al sistema escriba: floresta.org en la barra de direcciones de su navegador";
        echo "<div class=\"header\">";
        echo "<h2>Estación: ";
	include('get_name.php');
	echo "</h2>";
        echo "<h4>Estado del sistema: ";
	include 'running.php';
	echo "</h4>";
        echo "<center><h2><a href=\"/\">Volver a la página principal</a></h2></center>";
        echo "<hr />";
        echo "</div>";
        
?>
