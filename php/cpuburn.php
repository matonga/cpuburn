<?php
$cores = 0;
for ($i=1; $i<count($argv); $i++) {
	if ($argv[$i] == '-n') {
		$cores = $argv[$i+1] | 0;
	}
}
if (!$cores) {
	$cores = count (array_slice (explode ("processor\t:", file_get_contents ('/proc/cpuinfo')), 1));
}
printf ("Burning %u cores...\n", $cores);
for ($i=0; $i<$cores; $i++) {
	if (pcntl_fork () == 0) {
		while (1) ;
	}
}
for ($i=0; $i<$cores; $i++) {
	pcntl_wait ($status);
}
