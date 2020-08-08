<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Servicios de comunicación digital</title>
<link rel='stylesheet' href='style.css'/>
    <script>
      function addbox() {
      if (document.getElementById('sendall').checked) {
          document.getElementById('prefix').style.display = 'inline';
          document.getElementById('label').style.display = 'inline';
      } else {
          document.getElementById('prefix').style.display = 'none';
          document.getElementById('label').style.display = 'none';
      }
      }
    </script>
  </head>
  <body>
    <center>
    <?php include 'header.php' ?>


      <form action="uucico.php" method="post" enctype="multipart/form-data">
        <div class="bodywt">
          <h1>
            ¿Especificar la estación de destino?
            <input type="checkbox" name="sendall" onclick="addbox();" id="sendall" />
          </h1>

          <h1>
            <label for="prefix" id="label" style="display: none;"><i class="material-icons">radio</i> Estación de destino: </label>
            <select id="prefix" name="prefix" style="display: none;">
              <?php include('get_systems.php') ?>
            </select>
          </h1>
        </div>

        <div class="body">
          <h1>
            <input type="submit" value="Iniciar la transmisión" name="submit" />
          </h1>
        </div>
        <!--   <input type="image" src="img_submit.gif" alt="submit" width="48" height="48"/> -->

        <input type="hidden" id="myname" name="myname" value="<?php include('get_name.php')?>"/>
      </form>

<div class="bodywt">
      <h1>Cola de transmisión</h1>

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


    </center>
    <br/>
    <br/>

  </body>
</html>
