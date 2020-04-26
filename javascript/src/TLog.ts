

class TLog {
	log  (msg: string): void {
		console.log(msg);
	}

	error(msg: string): void {
		console.error (msg);
	}
}

declare var gLog : TLog;
