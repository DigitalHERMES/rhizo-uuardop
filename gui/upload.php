<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta charset="UTF-8">
<title>Serviços de Comunicação Digital</title>
<link rel="stylesheet" href="style.css">
</head>

<body>

<h2>Resultado da submissão do arquivo:</h2>

<br />
<?php
$target_dir = "/var/www/html/uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$remote_dir = "/var/www/html/arquivos/";
$uploadPic = 0;
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

// Check if image file is a actual image or fake image
if(isset($_POST["submit"])) {
    $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
    if($check !== false) {
        echo "File is an image - " . $check["mime"] . ".";
        $uploadPic = 1;
        $uploadOk = 1;
    } else {
//        echo "File is not an image. Proceding normally";
        $uploadOk = 1;
        $uploadPic = 0;
    }
}
// Check if file already exists
if (file_exists($target_file)) {
//    echo "Sorry, file already exists, cotinuing...";
    $uploadOk = 1;
}

if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
&& $imageFileType != "gif" && $uploadPic == 1) {
    echo "We have a common JPG, JPEG, PNG or GIF!";
}

// Check file size and if it is picture, reduce the size...
// limit not to reduce size is 50k!
if (($_FILES["fileToUpload"]["size"] > 50*1024) && $uploadPic == 1 ) { // 10MB max
    echo "Sua imagem é muito grande - convertendo para um tamanho menor.<br />";
    $command = "compress_image.sh" .  $_FILES["fileToUpload"]["name"] . "";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
    echo "Output: " . $output . " Return value: " . $return_var; 
    $uploadOk = 1;
}

// Check file size of a file...
// limit is 50k!
if (($_FILES["fileToUpload"]["size"] > 50*1024) && $uploadPic == 0 ) { // 10MB max
    echo "Arquivo muito grande. Máximo permitido: 51200 byte, tamanho do arquivo: " . $_FILES["fileToUpload"]["size"] . "<br />";
    $uploadOk = 0;
}

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "Erro no pré-processamento do arquivo.<br />";
// if everything is ok, try to upload file
} else {
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) { //  should I run UUCP from here?
        echo "</br>O arquivo  ". $_FILES["fileToUpload"]["name"] . " foi adicionado à fila.</br>";
        $source = substr ($_POST['myname'], 0,  6);
        $command = "uucp -C -d " .  $target_file . " " . $_POST['prefix'] . "\!" . $remote_dir . $source . "/";
        echo "UUCP Command: " . $command . "<br />";
        ob_start();
        system($command , $return_var);
        $output = ob_get_contents();
        ob_end_clean();
        unlink($target_file);
    } else {
        echo "Erro ao mover o arquivo para pasta temporária. <br />";
    }
}
?>

</body>
</html>
