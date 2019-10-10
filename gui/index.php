<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="UTF-8"</meta>
    <h1>  <center>rhizo-uuardop</center></h1>
    <title>Serviços de Comunicação Digital</title>
    <link rel="stylesheet" href="style.css">
</head>

<body>
    
   
    
    <div class='header'>
        <h2>Estação: AA2AAA</h2>
    <h6>Estado do Sistema: 
        <?php include 'running.php'; ?>
        
    </h6></div>


    <h2>Envio de arquivo</h2>
    <form action="upload.php" method="post" enctype="multipart/form-data">
      Escolha o arquivo: 
      <input type="file" name="fileToUpload" id="fileToUpload">
      <input type="submit" value="Colocar arquivo na fila" name="submit"><br/>
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
 <form action="sendQueue.php" method="post" enctype="multipart/form-data">
     Adicionar mais arquivos a fila <input type="file" name="queue" id="queue"></br>
      Enviar todos os arquivos que estão na fila<input type="submit" value="Enviar todos os arquivos da fila" name="submit"><br/>
    </form>
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
                </div>
            

</body>
</html>
