<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
    <link rel='stylesheet' href='style.css'/>
    <!-- <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">   -->
    <!-- <script src="https://kit.fontawesome.com/3e1432211a.js" crossorigin="anonymous"></script>-->
  </head>
  <body>
    <center>
      <div class="header">
      <h2>Estação: <?php include('get_name.php') ?></h2>
      <h5>Estado do Sistema: <?php include 'running.php'; ?></h5>
      <hr />
      </div>

        <div class="bodywt">
            <h1><i class="material-icons">cloud_upload
</i>	<a href="load.php">Carregar Arquivo para Transmissão</a>
              </i></h1></div>
      
        
      
      <div class="body">
      
          <h1><i class="material-icons">send</i><a href="tx.php">Transmitir</a></h1>
      
      </div>

      
        <div class="bodywt">    
            <h2><i class="material-icons">list</i><a href="list_job.php">Listar Arquivos Carregados para Transmissão</a></h2></div>
      

      <div class="body">
      
          <h1><i class="material-icons">get_app</i><a href="../uploads/">Recebimento de arquivos</a></h1>
      
      </div>

        <div class="bodywt">
            <h1><i class="material-icons">cancel</i><a href="kill_job.php">Cancelar transmissão</a></h1></div>
      

      <div class="body">
      <p>
	<h1><a href="list_job.php">Fila de transmissão</a></h1>
      </p>
      </div>

        <div class="bodywt">
	<h1><i class="material-icons">info</i><a href="view_log.php">Ver log</a></h1>
        </div>
    </center>
    <br/>
    <br/>
  </body>
</html>
