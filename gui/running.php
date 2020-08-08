<?php
    exec("pgrep -x uuardopd", $piduu);
    exec("pgrep -x ardop", $pidar);
    if(empty($piduu) || empty($pidar)){ 
        echo "¡El sistema está con problemas!";
    } else {
        echo "¡El sistema funciona!";
    }
?>
