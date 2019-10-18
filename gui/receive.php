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
        echo "Arquivos da Estação ".$value."<br />";
        $files_st = scandir($dir.DIRECTORY_SEPARATOR.$value);
        foreach($files_st as $key_st => $value_st){
            $path_st = realpath($dir.DIRECTORY_SEPARATOR.$value.DIRECTORY_SEPARATOR.$value_st);
            if(!is_dir($path_st)) {
                echo "<a href=\"arquivos/".$value."/".$value_st."\">".$value_st."</a>";
                $file_ext = pathinfo($path_st, PATHINFO_EXTENSION);
                if ($file_ext=="gpg") {
                   echo $file." é um arquivo GPG descript??<br/>";
                   echo "<form action=\"decrypt.php\" method=\"post\" enctype=\"multipart/form-data\">";
                   echo "Senha: ";
                   echo "<input type=\"text\" name=\"password\" />";
                   echo "<input type=\"submit\" value=\"Abrir com Senha\" name=\"submit\" />";
                   echo "<input type=\"hidden\" name=\"path\" value=\"".$path_st."\" />";
                   echo "</form>"
                }
                echo "<br />";
            }
        /* $results[] = $path; */
        }
    }
}

?>

    <!--

<?php

  $dir = '/var/www/html/arquivos/';

  // Check if the directory exists
  if (file_exists($dir) && is_dir($dir) ) {
  	
  	  // Get the files of the directory as an array
      $scan_arr = scandir($dir);
      $files_arr = array_diff($scan_arr, array('.','..') );

      // echo "<pre>"; print_r( $files_arr ); echo "</pre>";

      // Get each files of our directory with line break
      foreach ($files_arr as $file) {
      	//Get the file path
      	$file_path = "my_directory/".$file;
      	// Get the file extension
      	$file_ext = pathinfo($file_path, PATHINFO_EXTENSION);
      	if ($file_ext=="jpg" || $file_ext=="png" || $file_ext=="JPG" || $file_ext=="PNG"  ) {
      		echo $file."<br/>";
      	}
        
      	if ($file_ext=="gpg") { echo $file." é um arquivo GPG descript??<br/>"  ;}
        //if ($file_ext=="gpg") {echo "<option value='{$file}'" . ($pageImage == $file ? " selected" : "") . ">{$file}</option>";}
        
      }
  }
  else {
  	echo "Dorectory does not exists";
  }

?>
<select name="level">
<?php
    $dirname = "/var/www/html/arquivos/";
    $dirhandle = opendir($dirname);
    while($file = readdir($dirhandle))
    {
       
    if ($file != "." && $file != "..")
    {
    if (is_file($dirname.$file))
    {
        
        echo "<option value='{$file}'" . ($pageImage == $file ? " selected" : "") . ">{$file}</option>";

    }
    else
    {
    echo "mappe: " . $file . "<br>";
    }
    }
    }
     ?> 
</select>
-->

</center>
</body>
</html>
