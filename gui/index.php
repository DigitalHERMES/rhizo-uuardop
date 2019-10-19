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
      <h1>
        <a href="load.php"><i class="material-icons">cloud_upload</i> Carregar Arquivo para Transmissão</a>
      </h1>
    </div>

      <div class="body">
        <h1>
          <a href="tx.php"><i class="material-icons">send</i> Transmitir</a>
        </h1>
      </div>

      <div class="bodywt">
        <h1>
          <a href="receive.php"><i class="material-icons">get_app</i>
        Arquivos Recebidos</a>
        </h1>
      </div>

      <div class="body">
        <h1>
          <a href="kill_job.php"><i class="material-icons">cancel</i> Cancelar
            Transmissão Atual</a>
        </h1>
      </div>

      <div class="bodywt">
        <h1>
          <a href="list_job.php"><i class="material-icons">list</i> Listar
          Arquivos Carregados para Transmissão</a>
      </h1>
      </div>

      <div class="body">
        <h1>
          <a href="erase_queue.php"><i class="material-icons">remove_circle_outline</i> Limpar
            Arquivos Carregados</a>
        </h1>
      </div>

      <div class="bodywt">
        <h1>
          <a href="restart_system.php"><i class="material-icons">replay</i> Re-início
            interno do sistema</a>
        </h1>
      </div>

      <div class="body">
        <h1><a href="view_log.php"><i class="material-icons">info</i> Ver
        Histórico do Sistema</a>
        </h1>
      </div>

    </center>
    <br/>
    <br/>
  </body>
</html>
