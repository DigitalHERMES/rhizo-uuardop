<?php
$dir = "/var/www/html/arquivos/";
// Open a directory, and read its contents
if (is_dir($dir)){
  if ($dh = opendir($dir)){
    while (($file = readdir($dh)) !== false){
        if ($file == '.' || $file == '..') {
        continue;}
      echo "Archivo: " . $file . "<br />";
    }
    closedir($dh);
  }
}
?>
