<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset="UTF-8">
    <title>Serviços de Comunicação Digital</title>
    <link rel="stylesheet" href="style.css">
  </head>

  <body>
    <center>
    <?php include 'header.php' ?>

    <div class="bodywt">
      <h2>Iniciando Transmissão</h2>

<br />
<?php

// fix me - inverted logic...
if (!isset($_POST['sendall']))
{
    $command = "nohup sudo uucico  --master -f > /dev/null &";
    // echo "UUCP Command: " . $command . "<br />";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
} else {
    $source = substr ($_POST['myname'], 0,  6);
    if($source == $_POST['prefix'])
    {
        echo "ERRO: Estação de origem é igual estação de destino! <br />";
        exit;
    }
    else {
        $cmd= "alias.sh ".substr ($_POST['myname'], 0,  6); 
        $source = shell_exec($cmd);
        if ($source == $_POST['prefix'])
        {
            echo "ERRO: Estação de origem é igual estação de destino! <br />";
            exit; 
        }
    }

    $command = "nohup sudo uucico -S " . $_POST['prefix'] . " > /dev/null &";
    // echo "UUCP Command: " . $command . "<br />";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
}

?>
</div>

<div class="body">
      <a href="view_log.php"><h3>Ver Histórico do Sistema</h3></a>
</div>

</body>
</html>
