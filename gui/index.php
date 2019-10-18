<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Serviços de Comunicação Digital</title>
    <link rel='stylesheet' href='style.css'/>
  </head>
  <body>
    <center>
    <?php include 'header.php' ?>

      <div class="bodywt">
            <h1><i class="material-icons">cloud_upload
</i>	<a href="load.php">Carregar Arquivo para Transmissão</a>
              </i></h1></div>
              
      
      <div class="body">
      
          <h1><i class="material-icons">send</i><a href="tx.php">Transmitir</a></h1>
      
      </div>

      
        <div class="bodywt">    
            <h1><i class="material-icons">list</i><a href="list_job.php">Listar Arquivos Carregados para Transmissão</a></h1></div>
      

      <div class="body">
      
          <h1><i class="material-icons">get_app</i><a href="receive.php">Recebimento de arquivos</a></h1>
      
      </div>

        <div class="bodywt">
            <h1><i class="material-icons">cancel</i><a href="kill_job.php">Cancelar transmissão</a></h1></div>

        <div class="body">
	<h1><i class="material-icons">info</i><a href="view_log.php">Ver log</a></h1>
        </div>
    </center>
    <br/>
    <br/>
  </body>
</html>
