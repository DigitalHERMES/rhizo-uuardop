<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
    <link rel='stylesheet' href='styles.css'/>
  </head>
  <body>


  <div>
￼    <h2>Estação: <?php include('get_name.php') ?></h2>
  </div>
  <div>
￼    <h6>Estado do Sistema: 
￼        <?php include 'running.php'; ?>
     </h6>
  </div>
  <br />
  <p>
    <h2>Log do Sistema:</h2>
<br />
<textarea rows=8 cols=100 readonly>
<?php 
    $command = "uulog";
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

</body>
</html>
