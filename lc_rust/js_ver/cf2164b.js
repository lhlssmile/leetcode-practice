const fs = require('fs');
const tokens = fs.readFileSync(0, 'utf-8').trim().split(/\s+/);
let idx = 0
const next = () => tokens[idx++];

const findOddPairs = (odds) => {
  if (odds.length < 2) return null;
    const adj = odds
        .slice(0, -1)
        .map((x, i) => [x, odds[i + 1]])
        .find(([x, y]) => y < 2 * x);
    if (adj) return adj;

    const any = odds
        .flatMap((x, i) => odds.slice(i + 1).map((y) => [x, y]))
        .find(([x, y]) => ((y % x) % 2) === 0);
    return any || null;
};


const t = Number(next());
const out = [];

for (let _ = 0; _ < t; _++) {
    const n = Number(next());
    const a = Array.from({length: n}, () => Number(next()));
    const part = a.reduce(
        (acc, x) => ((x % 2 === 0 ? acc.evens : acc.odds).push(x), acc),
        {evens: [], odds: []}
    );
    const evens = part.evens;
    const odds = part.odds;

    const ans = (() => {
        if (evens.length >= 2) return `${evens[0]} ${evens[1]}`;
        const p = findOddPairs(odds);
        if (p) return `${p[0]} ${p[1]}`;
        if (evens.length === 0) return `-1`;
        const e = evens[0];
        const x = odds.filter((o) => o < e).find((x) => ( (e % x) % 2) === 0 );
        return x !== undefined ? `${x} ${e}` : `-1`;
    });
    out.push(ans)
}

process.stdout.write(out.join('\n'))