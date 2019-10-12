<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta charset="UTF-8">
<title>Serviços de Comunicação Digital</title>
<link rel="stylesheet" href="style.css">
</head>

<body>

<h2>Iniciando Transmissão:</h2>

<br />
<?php

// fix me - inverted logic...
if (!isset($_POST['sendall']))
{
    $command = "sudo uucico  --master -f";
    echo "UUCP Command: " . $command . "<br />";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
} else {

    $source = substr ($_POST['myname'], 0,  6);
    if($source == $_POST['prefix'])
    {
        echo "ERRO: Estação de origem é igual estação de destino! <br />";
    } else 
    {
        $command = "sudo uucico -S " . $_POST['prefix'] . "";
        echo "UUCP Command: " . $command . "<br />";
        ob_start();
        system($command , $return_var);
        $output = ob_get_contents();
        ob_end_clean();
    }
}

?>

</body>
</html>
