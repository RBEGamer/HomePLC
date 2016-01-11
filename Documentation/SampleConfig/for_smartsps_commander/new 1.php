<?php


$fp = fopen('schematic.xml', 'w');
fwrite($fp, $_POST['data']);
fclose($fp);


<?php