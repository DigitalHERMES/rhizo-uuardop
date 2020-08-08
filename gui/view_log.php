<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset="UTF-8"/>
    <title>Servicios de comunicación digital</title>
    <link rel='stylesheet' href='style.css' />
    <meta http-equiv="Refresh" content="100" />
  </head>
  <body>
    <center>
    <?php include 'header.php' ?>

    <div class="bodywt">
      <h1>Historial del sistema</h1>
    </div>

    <div class="body">
      <textarea rows=20 cols=80 readonly>
<?php 
    $command = "uulog|tail";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
    echo $output; 
?>
      </textarea>
    </div>

    </center>
    <br/>
    <br/>

  </body>
</html>
