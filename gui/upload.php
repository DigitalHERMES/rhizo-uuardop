<?php
$target_dir = "uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
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
    echo "Sorry, file already exists.";
    $uploadOk = 0;
}


if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
&& $imageFileType != "gif" && $uploadPic == 1) {
    echo "We have a common JPG, JPEG, PNG or GIF!";
}

// Check file size and if it is picture, reduce the size...
// limit not to reduce size is 50k!
if (($_FILES["fileToUpload"]["size"] > 50*1024) && $uploadPic == 1 ) { // 10MB max
    echo "Sua imagem é muito grande - convertendo para um tamanho menor.<br />";
    $command = "ffmpeg -i " . ;
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
    echo "Output: " . $output . " Return value: " . $return_var; 
    $uploadOk = 1;
}


// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded.";
// if everything is ok, try to upload file
} else {
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) { //  should I run UUCP from here?
    // uucp -C buffer.c central\!\~/
        echo "O arquivo ". basename( $_FILES["fileToUpload"]["name"]). " foi adicionado com sucesso.";
    } else {
        echo "Erro na cópia do arquivo....";
    }
}
?>
