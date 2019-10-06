<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta charset="UTF-8">
    <h1>  <center>rhizo-uuardop</center></h1>
    <title>Serviços de Comunicação Digital</title>
    <link rel="stylesheet" href="style.css">
	</head>

<body>

<div class="w3-container w3-teal">
    <h2>rhizo uma gravação</h2>
</div>
<?php
$target_dir = "uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
// Check if image file is a actual image or fake image

// Check if file already exists
if (file_exists($target_file)) {
    echo "Esse arquivo já esta na fila.";
    $uploadOk = 0;
}
// Check file size
if ($_FILES["fileToUpload"]["size"] > 50000000) {
    echo "O arquivo é muito grande.";
    $uploadOk = 0;
}
// Allow certain file formats
//if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
//&& $imageFileType != "gif" )  {
//    echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
//    $uploadOk = 0;
//}
// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded.";
// if everything is ok, try to upload file
} else {
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
        echo "</br>O arquivo  ". basename( $_FILES["fileToUpload"]["name"]). " esta na fila.</br>";
        //$list= scandir($target_dir,1);
        //print_r($list);
        include 'list.php';
    } else {
        echo "Sorry, there was an error uploading your file.";
    }
}
?>
    
    <form action="php3.php" method="post" enctype="multipart/form-data">
        <p>
        Carregar mais arquivos?
        
     </br><input type="file" name="fileToUpload" id="fileToUpload"></br>
      <input type="submit" value="Colocar arquivo na fila" name="submit">
      </br><button class="button" type="submit" value="queue"> Enviar fila</button>
      </p>
</body>
</html>
