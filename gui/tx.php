<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
    <link rel='stylesheet' href='styles.css'/>
  </head>
  <body>
  <center>
  <p>
    <h2>Estação: <?php include('get_name.php') ?></h2>
  </p>
  <br />

    <form action="upload.php" method="post" enctype="multipart/form-data">
    <p>
    <h1>Estação de Destino</h1> 
    <h1>
      <select id="prefix" name="prefix">
        <?php include('get_systems.php') ?>
      </select>
    </h1>
    </p>
    <p>
      <h1>Arquivo
      <input type="file" name="fileToUpload" id="fileToUpload" value="Escolher Arquivo"/>
      </h1>
    </p>
    <p>
    <h1>
      <input type="submit" value="Transmitir Arquivo" name="submit" />
    </h1>
    </p>
   <!--   <input type="image" src="img_submit.gif" alt="submit" width="48" height="48"/> -->

     <input type="hidden" id="myname" name="myname" value="<?php include('get_name.php')?>"/>
    </form>
    </center>
<br/>
<br/>

</body>
</html>
