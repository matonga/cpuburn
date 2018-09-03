const os = require ('os');
const child_process = require ('child_process');
var cores = os.cpus().length;
for (var i=2; i<process.argv.length; i++) {
	if (process.argv[i] == '-n') {
		cores = process.argv[i+1] | 0;
	}
	if (process.argv[i] == '--cpuburn') {
		while (1) ;
	}
}
process.stdout.write ('Burning ' + cores + ' cores...\n');
for (var i=0; i<cores; i++) {
	child_process.fork (process.argv[1], [ '--cpuburn' ]);
}
