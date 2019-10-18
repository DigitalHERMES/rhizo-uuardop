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

$path = $_POST['path'];
$dec_subdir=dirname($path)."/dec/";

echo $dec_subdir."<br />";
echo "password: ".$_POST['password']."<br />";
?>


    </center>
  </body>
</html>
