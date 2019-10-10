<?php
    exec("pgrep -x uuardopd", $piduu);
    exec("pgrep -x ardop", $pidar);
    if(empty($piduu) || empty($pidar)){ 
        echo "Sistema com Problemas!";
    } else {
        echo "Sistema Funcionando!";
    }
?>
