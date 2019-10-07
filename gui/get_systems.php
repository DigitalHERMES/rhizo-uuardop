<?php

    $command = "get_systems.sh";
    ob_start();
    system($command , $return_var);
    $output = "<option>" . ob_get_contents() . "</option>";
    ob_end_clean();
    echo $output; 
?>
