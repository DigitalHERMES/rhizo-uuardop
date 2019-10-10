<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
<!--    <link rel='stylesheet' href='styles.css'/> -->
    <script>
      function addbox() {
	  if (document.getElementById('enc').checked) {
              document.getElementById('txt').style.display = 'block';
	  } else {
              document.getElementById('txt').style.display = 'none';
	  }
      }
    </script>
  </head>
  <body>
    <center>

      <h2>Estação: <?php include('get_name.php') ?></h2>
      <h5>Estado do Sistema: <?php include 'running.php'; ?></h5>
      <hr />

  <form action="upload.php" method="post" enctype="multipart/form-data">
    <p>
    <h1>Estação de Destino
    <!-- Colocar rotulos para os sistemas.. -->
    <!-- Enviar arquivo com senha checkbox -->
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
      Proteger com Senha?
      <input type="checkbox" name="encrypt" onclick="addbox();" id="enc" />
      <input type="text" name="password" id="txt" style="display: none;" />
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
