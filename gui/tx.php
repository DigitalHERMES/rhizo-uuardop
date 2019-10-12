<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
<!--    <link rel='stylesheet' href='styles.css'/> -->
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

      <h2>Estação: <?php include('get_name.php') ?></h2>
      <h5>Estado do Sistema: <?php include 'running.php'; ?></h5>
      <hr />

      <form action="uucico.php" method="post" enctype="multipart/form-data">
        <p>
          <h1>
            Especificar Estação de Envio?
            <input type="checkbox" name="sendall" onclick="addbox();" id="sendall" />
          </h1>
        </p>

        <p>
          <h1>
            <label for="prefix" id="label" style="display: none;">Estação de Destino: </label>
            <select id="prefix" name="prefix" style="display: none;">
              <?php include('get_systems.php') ?>
            </select>
          </h1>
        </p>

        <p>
          <h1>
            <input type="submit" value="Iniciar Transmissão" name="submit" />
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
