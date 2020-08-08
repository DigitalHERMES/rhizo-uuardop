<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta charset='UTF-8'/>
    <title>Servicios de comunicación digital</title>
    <link rel='stylesheet' href='style.css'/>
  </head>
  <body>
    <center>
    <?php include 'header.php' ?>

    <div class="bodywt">
      <h1>
        <a href="load.php"><i class="material-icons">cloud_upload</i> Subir archivo para la transmisión</a>
      </h1>
    </div>

      <div class="body">
        <h1>
          <a href="tx.php"><i class="material-icons">send</i> Transmitir</a>
        </h1>
      </div>

      <div class="bodywt">
        <h1>
          <a href="receive.php"><i class="material-icons">get_app</i> Archivos recibidos</a>
        </h1>
      </div>

      <div class="body">
        <h1>
          <a href="kill_job.php"><i class="material-icons">cancel</i> Cancelar la transmisión actual
          </a>
        </h1>
      </div>

      <div class="bodywt">
        <h1>
          <a href="list_job.php"><i class="material-icons">list</i> Archivos en la lista cargados para su transmisión
          </a>
      </h1>
      </div>

      <div class="body">
        <h1>
          <a href="erase_queue.php"><i class="material-icons">remove_circle_outline</i> Limpiar los archivos cargados
          </a>
        </h1>
      </div>

      <div class="bodywt">
        <h1>
          <a href="restart_system.php"><i class="material-icons">replay</i> Reinicio del sistema interno
          </a>
        </h1>
      </div>

      <div class="body">
        <h1>
          <a href="view_log.php"><i class="material-icons">info</i> Ver el historial del sistema
          </a>
        </h1>
      </div>

      <div class="bodywt">
        <h1>
          <a href="shutdown.php"><i class="material-icons">flash_off</i> Apagar el sistema
          </a>
        </h1>
      </div>

    </center>
    <br/>
    <br/>
  </body>
</html>
