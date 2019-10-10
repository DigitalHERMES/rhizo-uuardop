<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
<!--    <link rel='stylesheet' href='styles.css'/> -->
  </head>
  <body>
    <center>
      <h2>Estação: <?php include('get_name.php') ?></h2>
      <h5>Estado do Sistema: <?php include 'running.php'; ?></h5>
      <hr />

      <p>
	<h1>Fila de Transmissão:</h1>
	<br />
	<textarea rows=6 cols=100 readonly>
<?php 
    $command = "uustat -a";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
    echo $output; 
?>
	</textarea>
      </p>
      <br/>
      <br/>
    </center>
  </body>
</html>
