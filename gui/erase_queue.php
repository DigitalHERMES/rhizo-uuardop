<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Servicios de comunicación digital</title>
    <link rel='stylesheet' href='style.css'/>
  </head>
  <body>
    <center>
    <?php include 'header.php' ?>

      <div class="body">
        <h1>Archivos eliminados de la cola de transmisión
        </h1>
      </div>

      <br />
<?php
    $command = "sudo uustat -u www-data -K";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();

    $command = "sudo uustat -u uucp -K";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();

    $command = "sudo uustat -u root -K";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();


?>
      <div class="body">
          <a href="load.php"> Subir archivos</a>
          
      </div>
      
    </center>
  </body>
</html>
