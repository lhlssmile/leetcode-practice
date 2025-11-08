const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

// Token-based input (split by whitespace across lines)
const tokens = []; let idx = 0;
const next = () => tokens[idx++];
const nextInt = () => Number(next());
const nextStr = () => next();

// multiRead: pass parsers (e.g., Number, x=>x) and read multiple values
const multiRead = (...parsers) => parsers.map(p => p(next()));
// readArray: read n tokens with parser (default Number)
const readArray = (n, parser = Number) => Array.from({ length: n }, () => parser(next()));

const INF = 0x3f3f3f3f;
const MOD = 1000000007;

// Fast output helpers
const fastPrintArray = (arr, sep = ' ') => process.stdout.write(arr.join(sep) + '\n');
const fastPrintSlice = (slice, sep = ' ') => process.stdout.write(slice.join(sep) + '\n');

function solve() {
    const t = nextInt();
    const [n, ra, ca, rb, cb] = multiRead(Number, Number, Number, Number, Number);
    const out = [];
    for (let _ = 0; _ < t; _++) {
        let ansRow = rb > ra ? rb : (rb < ra ? (n -rb) : 0);
        let ansCol = cb > ca ? cb : (cb < ca ? (n - cb) : 0);
        const ans = Math.max(ansCol,ansRow);
        out.push(String(ans));
    }

    process.stdout.write(out.join('\n'));
}

rl.on('line', (line) => {
    if (line.length) tokens.push(...line.trim().split(/\s+/));
});
rl.on('close', () => { solve(); });
