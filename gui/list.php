<?php
$dir = "uploads/";
// Open a directory, and read its contents
if (is_dir($dir)){
  if ($dh = opendir($dir)){
    while (($file = readdir($dh)) !== false){
        if ($file == '.' || $file == '..') {
        continue;}
      echo "Arquivo:" . $file . "<br />";
    }
    closedir($dh);
  }
}
?>
