<?php
        echo "<div class=\"header\">";
        echo "<h2>Estação: ";
	include('get_name.php');
	echo "</h2>";
        echo "<h4>Estado do Sistema: ";
	include 'running.php';
	echo "</h4>";
        echo "<center><h2><a href=\"/\">Voltar para Página Principal</a></h2></center>";
        echo "<hr />";
        echo "</div>";
?>
