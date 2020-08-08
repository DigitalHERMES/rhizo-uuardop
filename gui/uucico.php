<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset="UTF-8">
    <title>Servicios de comunicación digital</title>
    <link rel="stylesheet" href="style.css">
  </head>

  <body>
    <center>
    <?php include 'header.php' ?>

    <div class="bodywt">
      <h2>Iniciando la transmisión</h2>

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
        echo "ERROR: ¡La estación de origen es la misma que la estación de destino! <br />";
        exit;
    }
    else {
        $cmd= "alias.sh ".substr ($_POST['myname'], 0,  6); 
        $source = shell_exec($cmd);
        if ($source == $_POST['prefix'])
        {
            echo "ERROR: ¡La estación de origen es la misma que la estación de destino! <br />";
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
      <a href="view_log.php"><h3>Ver el historial del sistema</h3></a>
</div>

</body>
</html>
