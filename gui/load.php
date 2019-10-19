<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
  <link rel='stylesheet' href='style.css'/> 
    <script>
      function addbox() {
	  if (document.getElementById('enc').checked) {
              document.getElementById('txt').style.display = 'inline';
	      document.getElementById('label').style.display = 'inline';
	  } else {
              document.getElementById('txt').style.display = 'none';
	      document.getElementById('label').style.display = 'none';
	  }
      }
    </script>
  </head>
  <body>
    <center>
    <?php include 'header.php' ?>

    <form action="upload.php" method="post" enctype="multipart/form-data">
      <div class="bodywt">
        <i class="material-icons">radio</i>
        Estação de Destino
        <!-- Colocar rotulos para os sistemas.. -->
        <select id="prefix" name="prefix">
          <?php include('get_systems.php') ?>
        </select>
      </div>

      <div class="body">
        <i class="material-icons">open_in_browser</i>
        Arquivo
        <input type="file" name="fileToUpload" id="fileToUpload" value="Escolher Arquivo"/>
      </div>

      <div class="bodywt">
        <i class="material-icons">enhanced_encryption</i>
        Proteger com Senha?
        <input type="checkbox" name="encrypt" onclick="addbox();" id="enc" />

        <label for="txt" id="label" style="display: none;">Senha: </label>
        <input type="text" name="password" id="txt" style="display: none;" />

      </div>

      <div class="body">
        <i class="material-icons">rss_feed</i>
        Enviar agora?
        <input type="checkbox" name="sendnow" id="sendnow" />
      </div>

      <div class="bodywt">
        <input type="submit" value="Transmitir Arquivo" name="submit" />
      </div>
   <!--   <input type="image" src="img_submit.gif" alt="submit" width="48" height="48"/> -->

      <input type="hidden" id="myname" name="myname" value="<?php include('get_name.php')?>"/>
    </form>
    </center>

    <br/>

  </body>
</html>
