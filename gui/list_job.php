<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
    <link rel='stylesheet' href='styles.css'/>
  </head>
  <body>
    <center>
    <?php include 'header.php' ?>

    <div class="bodywt">
      <h1>Fila de Transmissão</h1>

      <textarea rows=12 cols=100 readonly>
<?php 
    $command = "uustat -a";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
    echo $output; 
?>
      </textarea>
    </div>
    <br/>
    <br/>
    </center>
  </body>
</html>
