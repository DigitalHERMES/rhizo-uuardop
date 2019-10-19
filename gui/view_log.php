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

    <div class="bodywt">
      <h1>Histórico do Sistema</h1>
    </div>

    <div class="body">
      <textarea rows=25 cols=80 readonly>
<?php 
    $command = "uulog";
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
