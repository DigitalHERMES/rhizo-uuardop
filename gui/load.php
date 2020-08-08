<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Servicios de comunicación digital</title>
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
        Estación de destino
        <!-- Colocar rotulos para os sistemas.. -->
        <select id="prefix" name="prefix">
          <?php include('get_systems.php') ?>
        </select>
      </div>
    
      <div class="body">
        <i class="material-icons">open_in_browser</i>
        Arquivo
        <input type="file" name="fileToUpload" id="fileToUpload" value="Seleccionar el archivo"/>
      </div>

      <div class="bodywt">
        <i class="material-icons">enhanced_encryption</i>
        ¿Proteger con contraseña?
        <input type="checkbox" name="encrypt" onclick="addbox();" id="enc" />
	<br />
        <label for="txt" id="label" style="display: none;">Contraseña: </label>
        <input type="text" name="password" id="txt" style="display: none;" />

      </div>
        <div class="body">
<input type="submit" value="colocar el archivo en la cola" name="submit" />
        <input type="hidden" id="myname" name="myname" value="<?php include('get_name.php')?>"/>
    </form>
        
      </div>
      

          <div class="bodywt">
	    <h3>Cola de transmisión</h3>
            <textarea rows=12 cols=100 readonly>
<?php
      $command = "uustat -a| cut -f 2,7,8,9 -d \" \" | sed \"s/\/var\/www\/html\/uploads\///\"";
      ob_start();
      system($command , $return_var);
      $output = ob_get_contents();
      ob_end_clean();
      echo $output; 
?>
	    </textarea>
	  </div>

	  <div class="bodywt">
		Los archivos anteriores están en la cola para ser transmitidos antes que los suyos. ¿Desea cancelar la transmisión de estos archivos?
                <br />
		<form action="erase_queue.php" method="post" enctype="multipart/form-data">
		  <input type="submit" value="Cancelar" name="cancel" />
		</form>
	  </div>

    


    </center>
  </body>
</html>
