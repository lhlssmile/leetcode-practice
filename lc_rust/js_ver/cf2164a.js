const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

let lines = [];
let currentLine = 0;

function input() { return lines[currentLine++]; }
function nextInt() { return parseInt(input()); }
function nextIntArray() { return input().split(' ').map(Number); }

const INF = 0x3f3f3f3f;
const MOD = 1000000007;

function solve() {
    const n = nextInt();
    const a = nextIntArray();

    const [minVal, maxVal] = a.reduce(
        ([currMin, currMax], x) => [
            Math.min(currMin, x),
            Math.max(currMax, x)
        ],
        [Infinity, -Infinity]
    );
    const x = nextInt();
    if (x >= minVal && x <= maxVal) {
        console.log("YES");
    } else {
        console.log("NO");
    }

}

rl.on('line', (line) => { lines.push(line); });
rl.on('close', () => { solve(); });