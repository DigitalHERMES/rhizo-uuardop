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
	<h1>Transmissão Cancelada e Fila de Envio Limpa.</h1>
	<br />
<?php 
    $command = "kill_job.sh";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
//    echo $output; 
?>
      </p>
      <br/>
      <br/>
      </center>
  </body>
</html>
