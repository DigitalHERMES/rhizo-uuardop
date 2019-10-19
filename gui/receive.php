<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
    <link rel='stylesheet' href='style.css'/>
  </head>

  <body>
    <center>

    <?php include 'header.php' ?>


<?php

$dir = '/var/www/html/arquivos/';
$files = scandir($dir);

foreach($files as $key => $value){
    $path = realpath($dir.DIRECTORY_SEPARATOR.$value);
    if(is_dir($path) && $value != "." && $value != "..") {
        echo "<div class=\"body\">Arquivos de Origem da Estação ".$value."</div><br />";
        $files_st = scandir($dir.DIRECTORY_SEPARATOR.$value);
        $class="bodywt";
        foreach($files_st as $key_st => $value_st){
            $path_st = realpath($dir.DIRECTORY_SEPARATOR.$value.DIRECTORY_SEPARATOR.$value_st);
            if(!is_dir($path_st)) {
                $file_ext = pathinfo($path_st, PATHINFO_EXTENSION);
		if ($class == "bodywt"){
		   echo "<div class=\"bodywt\">";
		   $class="body";
		} else {
		   echo "<div class=\"body\">";
		   $class="bodywt";
		}
                if ($file_ext=="gpg") {
		   echo $value_st;
                   echo "<form action=\"decrypt.php\" method=\"post\" enctype=\"multipart/form-data\" style=\"display: inline;\">";
                   echo "<br />Senha: ";
                   echo "<input type=\"text\" name=\"password\" />";
                   echo "<input type=\"submit\" value=\"Abrir com Senha\" name=\"submit\" />";
                   echo "<input type=\"hidden\" name=\"path\" value=\"".$path_st."\" />";
                   echo "</form>";
                }
		else {
		   echo "<a href=\"arquivos/".$value."/".$value_st."\">".$value_st."</a>";
		}
		/* echo "<br />"; */
		echo "</div>";
            }
        /* $results[] = $path; */
        }
    }
}

if ($class == "bodywt"){
   echo "<div class=\"bodywt\">";
} else {
   echo "<div class=\"body\">";
}

echo "<a href=\"clean_files.php\">Limpar Todos Arquivos</a>";

echo "</div>;
?>



</center>
</body>
</html>
