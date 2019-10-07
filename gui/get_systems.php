<?php

    $command = "get_systems.sh";
    ob_start();
    system($command , $return_var);
    $output = ob_get_contents();
    ob_end_clean();
    $sysnames = explode("\n", $output);
    for ($i = "0" ; $i < count($sysnames); $i++) {
        if(!empty($sysnames[$i])) {
       	       	echo "<option>";
       	       	echo $sysnames[$i];
       	       	echo "</option>";
	}
    }

?>
