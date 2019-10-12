<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="UTF-8"</meta>
    <h1>  <center>rhizo-uuardop</center></h1>
    <title>Serviços de Comunicação Digital</title>
    <link rel="stylesheet" href="style.css">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">    
</head>

<body>
    
   
    
    <div class='header'>
        <h2>Estação: AA2AAA</h2>
    <h6>Estado do Sistema: 
        <?php include 'running.php'; ?>
        
    </h6></div>


    <h2>Envio de arquivo</h2>
    <form action="php3.php" method="post" enctype="multipart/form-data">
      Escolha o arquivo:<i class="material-icons">
folder_open
</i> 
      <input type="file" name="fileToUpload" id="fileToUpload">
      <input type="submit" value="Colocar arquivo na fila" name="submit"><i class="material-icons">
cloud_upload
</i><br/>
    </form>
            
    
    

   
<br/>

<div class='results'>
<br/>
Arquivos na fila para serem enviados.
</br>
</br>

    <?php include 'list.php'; ?>
</div>
     <div class="body">
    Escolher destinatario
    <select class="form" id="prefix" name="prefix">
    <option>Selecionar </option>
    <option>111111</option>
    <option>111111</option>
    <option>111111</option>
    <option>111111</option>
    <option>111111</option>
    <option>111111</option>
    <option>111111</option>
    <option>111111</option>
    </select>
    <form action="sendQueue.php" method="post" enctype="multipart/form-data">
     Enviar todos os arquivos que estão na fila  <input type="submit" value="Enviar todos os arquivos da fila" name="submit"><br/>
    </form></div>
<form action="index.html" method="post" enctype="multipart/form-data">
  <input type="submit" value="Voltar a pagina inicial" name="index"><br/>
    </form>

    
            

</body>
</html>
