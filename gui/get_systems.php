<?php

    $command = "get_systems.sh";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    $keywords = preg_split("/[\s,]+/", $output);
    foreach($keywords as $word){
        echo "<option>" . $word . "</option>";
    }
    ob_end_clean();
    echo $output; 
?>
