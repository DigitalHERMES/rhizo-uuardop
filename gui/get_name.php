<?php

    $command = "get_nodename.sh";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
    echo $output; 
?>
