<?php
        exec("pgrep -x uuardopd", $pids);
            if(empty($pids)) { echo 'UUARDOPD NÃO ESTA FUNCIONANDO';}
            else {echo "UUARDOPD FUNCIONANDO NORMALMENTE";}
            ?>
