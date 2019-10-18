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

mkdir($dec_subdir, 0777, TRUE);

$outfile=$dec_subdir.basename($path,".gpg");

$command = "decrypt.sh ".$path." ".$outfile." ".$_POST['password'];
echo $command."<br />";

ob_start();
system($command , $return_var);
$output = ob_get_contents();
ob_end_clean();

echo $output."<br />;

echo "<a href=\"".$outfile."\">".basename($outfile)."</a><br />";

?>


    </center>
  </body>
</html>
