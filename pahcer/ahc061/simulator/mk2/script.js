// --- Constants ---
const N = 10;
const MAX_TURN = 100;
const PLAYER_COLORS = ['#3072ff', '#ff4750', '#26d826', '#f173bd', '#ffa71a', '#24e6cc', '#fcff4e', '#555555'];
const PLAYER_NAMES = ['You (P0)', 'AI (P1)', 'AI (P2)', 'AI (P3)', 'AI (P4)', 'AI (P5)', 'AI (P6)', 'AI (P7)'];

// --- Utility ---
function randInt(min, max) { return Math.floor(Math.random() * (max - min + 1)) + min; }
function randDouble(min, max) { return Math.random() * (max - min) + min; }

// --- Classes ---

class Cell {
    constructor(r, c, value) {
        this.r = r; this.c = c; this.value = value;
        this.owner = -1; this.level = 0; this.piece = -1;
    }
}

class Player {
    constructor(id) {
        this.id = id; this.r = -1; this.c = -1; this.score = 0;
        this.trueParams = {
            wa: randDouble(0.3, 1.0), wb: randDouble(0.3, 1.0),
            wc: randDouble(0.3, 1.0), wd: randDouble(0.3, 1.0),
            epsilon: randDouble(0.1, 0.5)
        };
        this.estParams = { wa: 0.65, wb: 0.65, wc: 0.65, wd: 0.65 };
    }
}

class Game {
    constructor() {
        this.grid = [];
        this.players = [];
        this.turn = 0;
        this.isGameOver = false;
        this.M = 4;
        this.U = 5;
        this.aiRandoms = [];
        this.init();
    }

    init() {
        this.M = parseInt(document.getElementById('input-m').value);
        this.U = parseInt(document.getElementById('input-u').value);
        const mapType = document.getElementById('map-type').value;

        this.resetState();
        this.log(`ゲーム開始 (M=${this.M}, U=${this.U})`);

        if (mapType === 'official') { this.generateOfficialMap(); }
        else { this.generateSimpleMap(); }

        this.placePlayersRandomly();
        this.generateAIRandoms();

        this.updateVizDropdown();
        this.updateScores();
        this.render();
    }

    resetState() {
        this.turn = 1;
        this.isGameOver = false;
        document.getElementById('log').innerHTML = '';
        this.players = [];
        this.grid = [];
        this.aiRandoms = [];
        document.getElementById('use-true-params').checked = false;
        document.getElementById('slider-container').classList.remove('disabled');
        document.getElementById('export-data').value = '';
    }

    generateAIRandoms() {
        this.aiRandoms = [];
        for(let t=0; t<MAX_TURN; t++) {
            const turnRandoms = [];
            for(let i=0; i<this.M-1; i++) {
                turnRandoms.push({ r1: Math.random(), r2: Math.random() });
            }
            this.aiRandoms.push(turnRandoms);
        }
    }

    updateVizDropdown() {
        const sel = document.getElementById('viz-target');
        sel.innerHTML = '<option value="-1">なし (OFF)</option>';
        for(let i=1; i<this.M; i++) {
            const opt = document.createElement('option');
            opt.value = i;
            opt.text = `${PLAYER_NAMES[i]}`;
            sel.appendChild(opt);
        }
        this.updateVizParamsFromInput();
    }

    updateVizParams() {
        ['wa', 'wb', 'wc', 'wd'].forEach(k => {
            document.getElementById(`val-${k}`).innerText = document.getElementById(`p-${k}`).value;
        });
        this.render();
    }

    updateVizParamsFromInput() {
         ['wa', 'wb', 'wc', 'wd'].forEach(k => {
            document.getElementById(`val-${k}`).innerText = document.getElementById(`p-${k}`).value;
        });
    }

    getEstParamsFromUI() {
        return {
            wa: parseFloat(document.getElementById('p-wa').value),
            wb: parseFloat(document.getElementById('p-wb').value),
            wc: parseFloat(document.getElementById('p-wc').value),
            wd: parseFloat(document.getElementById('p-wd').value)
        };
    }

    toggleTrueParams() {
        const isCheat = document.getElementById('use-true-params').checked;
        const container = document.getElementById('slider-container');
        if(isCheat) container.classList.add('disabled');
        else container.classList.remove('disabled');
        this.render();
    }

    // --- Import / Export ---

    exportInput() {
        if (!this.grid || this.grid.length === 0) return;

        const lines = [];
        lines.push(`${N} ${this.M} ${MAX_TURN} ${this.U}`);

        for(let r=0; r<N; r++) {
            const rowVals = [];
            for(let c=0; c<N; c++) rowVals.push(this.grid[r][c].value);
            lines.push(rowVals.join(' '));
        }

        for(let i=0; i<this.M; i++) {
            lines.push(`${this.players[i].r} ${this.players[i].c}`);
        }

        for(let i=1; i<this.M; i++) {
            const p = this.players[i].trueParams;
            lines.push(`${p.wa.toFixed(10)} ${p.wb.toFixed(10)} ${p.wc.toFixed(10)} ${p.wd.toFixed(10)} ${p.epsilon.toFixed(10)}`);
        }

        for(let t=0; t<MAX_TURN; t++) {
            for(let i=0; i<this.M-1; i++) {
                const rnd = this.aiRandoms[t][i];
                lines.push(`${rnd.r1.toFixed(10)} ${rnd.r2.toFixed(10)}`);
            }
        }

        const outputText = lines.join('\n');
        const outBox = document.getElementById('export-data');
        outBox.value = outputText;

        navigator.clipboard.writeText(outputText).then(() => {
            alert("クリップボードにコピーしました！");
        }).catch(err => {});
    }

    loadInput() {
        const text = document.getElementById('input-data').value.trim();
        if(!text) { alert("入力欄が空です"); return; }

        try {
            const tokens = text.trim().split(/\s+/);
            let idx = 0;
            const readNext = () => tokens[idx++];
            const readInt = () => parseInt(readNext());
            const readFloat = () => parseFloat(readNext());

            const n = readInt();
            const m = readInt();
            const t = readInt();
            const u = readInt();

            if(n !== 10) throw new Error("N must be 10");

            this.M = m; this.U = u;
            this.resetState();

            this.grid = [];
            for(let r=0; r<N; r++) {
                const row = [];
                for(let c=0; c<N; c++) row.push(new Cell(r, c, readInt()));
                this.grid.push(row);
            }

            this.players = [];
            for(let i=0; i<this.M; i++) {
                const p = new Player(i);
                p.r = readInt(); p.c = readInt();
                this.players.push(p);
                const cell = this.grid[p.r][p.c];
                cell.owner = i; cell.level = 1; cell.piece = i;
            }

            // Params
            if(idx < tokens.length) {
                this.log("拡張データ(AIパラメータ)を読み込み中...");
                for(let i=1; i<this.M; i++) {
                    const p = this.players[i];
                    p.trueParams.wa = readFloat();
                    p.trueParams.wb = readFloat();
                    p.trueParams.wc = readFloat();
                    p.trueParams.wd = readFloat();
                    p.trueParams.epsilon = readFloat();
                }
            }

            // Randoms
            if(idx < tokens.length) {
                this.log("拡張データ(乱数)を読み込み中...");
                this.aiRandoms = [];
                for(let turn=0; turn<MAX_TURN; turn++) {
                    const turnRnds = [];
                    for(let i=0; i<this.M-1; i++) {
                        const r1 = readFloat();
                        const r2 = readFloat();
                        turnRnds.push({r1, r2});
                    }
                    this.aiRandoms.push(turnRnds);
                }
            } else {
                this.generateAIRandoms();
            }

            this.log(`入力読込完了`);
            this.updateVizDropdown();
            this.updateScores();
            this.render();

        } catch(e) {
            alert("入力解析エラー: " + e.message);
            console.error(e);
        }
    }

    // --- Map Generators ---

    generateSimpleMap() {
        for(let r=0; r<N; r++) {
            const row = [];
            for(let c=0; c<N; c++) {
                let val = Math.floor(randDouble(1, 10));
                if (Math.random() < 0.1) val += 20;
                row.push(new Cell(r, c, val));
            }
            this.grid.push(row);
        }
    }

    generateOfficialMap() {
        const a = randDouble(0.0, 3.0);
        let rawV = [];
        for(let r=0; r<N; r++) {
            rawV[r] = [];
            for(let c=0; c<N; c++) rawV[r][c] = Math.pow(randDouble(0.5, 1.0), a);
        }
        const K = randInt(0, 2);
        for(let k=0; k<K; k++) {
            const x = randInt(0, N-1), y = randInt(0, N-1);
            const b = randDouble(1.0, 4.0), m = randInt(0, 4), R = randDouble(1.0, 5.0);
            for(let i=0; i<N; i++) {
                for(let j=0; j<N; j++) {
                    const d2 = (i-x)**2 + (j-y)**2;
                    const dE = Math.sqrt(d2);
                    const dM = Math.abs(i-x) + Math.abs(j-y);
                    if(m===0) rawV[i][j] += b * Math.exp(-d2 / (2*R*R));
                    else if(m===1) rawV[i][j] += b / (1 + dE/R);
                    else if(m===2 && d2<=R*R) rawV[i][j] += b/4;
                    else if(m===3) rawV[i][j] += b / (1 + dM/R);
                    else if(m===4 && dM<=R) rawV[i][j] += b/4;
                }
            }
        }
        let curSum = 0;
        for(let r=0; r<N; r++) for(let c=0; c<N; c++) curSum += rawV[r][c];
        let intV = [];
        let finSum = 0;
        const TARGET = 1000 * N * N;
        for(let r=0; r<N; r++) {
            intV[r] = [];
            for(let c=0; c<N; c++) {
                const val = Math.ceil(rawV[r][c] * TARGET / curSum);
                intV[r][c] = val;
                finSum += val;
            }
        }
        while(finSum > TARGET) {
            let cands = [];
            for(let r=0; r<N; r++) for(let c=0; c<N; c++) if(intV[r][c] >= 2) cands.push({r,c});
            if(cands.length===0) break;
            const t = cands[randInt(0, cands.length-1)];
            intV[t.r][t.c]--;
            finSum--;
        }
        for(let r=0; r<N; r++) {
            const row = [];
            for(let c=0; c<N; c++) row.push(new Cell(r, c, intV[r][c]));
            this.grid.push(row);
        }
    }

    placePlayersRandomly() {
        const startPositions = new Set();
        for(let i=0; i<this.M; i++) {
            let p = new Player(i);
            let r, c;
            do { r = randInt(0, N-1); c = randInt(0, N-1); } while(startPositions.has(`${r},${c}`));
            startPositions.add(`${r},${c}`);
            p.r = r; p.c = c;
            this.players.push(p);
            const cell = this.grid[r][c];
            cell.owner = i; cell.level = 1; cell.piece = i;
        }
    }

    // --- Game Logic Matching lib.rs ---

    // BFS with fixed order to match Rust get_candidates
    getReachableTerritory(pid) {
        if(!this.players[pid]) return [];
        const p = this.players[pid];

        let reachable = [];
        let visited = new Set();
        let queue = [{r: p.r, c: p.c}];
        visited.add(`${p.r},${p.c}`);

        // Note: Rust code adds start position to reachable if it's not occupied by *others*.
        // Since we handle player collision check later in decideAIMove/getBestMove,
        // here we just return the full connectivity set based on ownership.
        // However, lib.rs `get_candidates` filters occupied cells inside BFS.
        // We will return ALL connected own/adjacent cells here, and filter occupancy later.

        // Wait, lib.rs `get_candidates` checks `ok` (occupied by other?) then adds to reachable.
        // And it only continues BFS if `owner == player`.
        // Order of neighbors in Rust: (0,1), (1,0), (0,-1), (-1,0) [Right, Down, Left, Up]

        let head = 0;
        while(head < queue.length){
            const curr = queue[head++];

            // Check occupancy for "reachable" list addition
            let occupiedByOther = false;
            for(let i=0; i<this.M; i++) {
                if(i !== pid && this.players[i].r === curr.r && this.players[i].c === curr.c) {
                    occupiedByOther = true; break;
                }
            }
            if(!occupiedByOther) {
                reachable.push(curr);
            }

            // Continue BFS only if own territory
            if(this.grid[curr.r][curr.c].owner === pid) {
                const dirs = [[0,1], [1,0], [0,-1], [-1,0]]; // Fixed Order: R, D, L, U
                for(let d of dirs) {
                    const nr = curr.r + d[0];
                    const nc = curr.c + d[1];
                    if(nr>=0 && nr<N && nc>=0 && nc<N) {
                        const key = `${nr},${nc}`;
                        if(!visited.has(key)) {
                            visited.add(key);
                            queue.push({r: nr, c: nc});
                        }
                    }
                }
            }
        }
        return reachable;
    }

    // Since we baked logic into getReachableTerritory, getValidMoves is just alias
    getValidMoves(pid) {
        return this.getReachableTerritory(pid);
    }

    decideAIMove(pid) {
        const p = this.players[pid];
        const moves = this.getValidMoves(pid); // Returns candidates in BFS order
        if(moves.length === 0) return {r: p.r, c: p.c};

        const rndIdx = this.turn - 1;
        const aiIdx = pid - 1; // P1->0

        let r1 = Math.random();
        let r2 = Math.random();

        if(this.aiRandoms[rndIdx] && this.aiRandoms[rndIdx][aiIdx]) {
            r1 = this.aiRandoms[rndIdx][aiIdx].r1;
            r2 = this.aiRandoms[rndIdx][aiIdx].r2;
        }

        if(r1 < p.trueParams.epsilon) {
            // Random move: index = floor(r2 * len)
            const idx = Math.min(moves.length - 1, Math.floor(r2 * moves.length));
            return moves[idx];
        }
        return this.getBestMove(pid, moves, p.trueParams, r2);
    }

    getBestMove(pid, moves, params, r2 = 0.5) {
        let scores = [];
        let maxScore = -Infinity;

        for(let m of moves) {
            const score = this.calcScore(pid, m.r, m.c, params);
            scores.push(score);
            if(score > maxScore) maxScore = score;
        }

        // Collect best indices with tolerance
        const tolerance = 1e-9 * Math.max(1.0, Math.abs(maxScore));
        let bestIndices = [];
        for(let i=0; i<scores.length; i++) {
            if(scores[i] >= maxScore - tolerance) {
                bestIndices.push(i);
            }
        }

        const bestIdx = Math.min(bestIndices.length - 1, Math.floor(r2 * bestIndices.length));
        return moves[bestIndices[bestIdx]];
    }

    calcScore(pid, r, c, params) {
        const cell = this.grid[r][c];
        let coef = 0;
        if(cell.owner === -1) coef = params.wa;
        else if(cell.owner === pid) {
            if(cell.level < this.U) coef = params.wb;
            else coef = 0;
        } else {
            if(cell.level === 1) coef = params.wc;
            else coef = params.wd;
        }
        return cell.value * coef;
    }

    handlePlayerClick(r, c) {
        if(this.isGameOver) return;
        const validMoves = this.getValidMoves(0);
        if(!validMoves.some(m => m.r === r && m.c === c)) {
            this.log("移動不可"); return;
        }
        const moves = new Map();
        moves.set(0, {r, c});
        for(let i=1; i<this.M; i++) moves.set(i, this.decideAIMove(i));
        this.processTurn(moves);
    }

    processTurn(moves) {
        const destMap = new Map();
        for(let i=0; i<this.M; i++) {
            const m = moves.get(i);
            const key = `${m.r},${m.c}`;
            if(!destMap.has(key)) destMap.set(key, []);
            destMap.get(key).push(i);
        }

        const repelled = new Set();
        destMap.forEach((pids, key) => {
            const [r, c] = key.split(',').map(Number);
            if(pids.length > 1) {
                const owner = this.grid[r][c].owner;
                if(pids.includes(owner)) {
                    pids.forEach(pid => { if(pid !== owner) repelled.add(pid); });
                } else {
                    pids.forEach(pid => repelled.add(pid));
                }
            }
        });

        for(let i=0; i<this.M; i++) {
            if(repelled.has(i)) continue;
            const m = moves.get(i);
            const cell = this.grid[m.r][m.c];

            if(cell.owner === -1) {
                cell.owner = i; cell.level = 1;
            } else if(cell.owner === i) {
                if(cell.level < this.U) cell.level++;
            } else {
                cell.level--;
                if(cell.level === 0) {
                    cell.owner = i; cell.level = 1;
                    this.log(`P${i}が(${m.r},${m.c})を奪取`);
                } else {
                    repelled.add(i);
                }
            }
        }

        for(let i=0; i<this.M; i++) {
            if(!repelled.has(i)) {
                const m = moves.get(i);
                this.grid[this.players[i].r][this.players[i].c].piece = -1;
                this.players[i].r = m.r;
                this.players[i].c = m.c;
            }
        }
        for(let i=0; i<this.M; i++) {
            const p = this.players[i];
            this.grid[p.r][p.c].piece = i;
        }

        this.turn++;
        this.updateScores();
        this.render();
        if(this.turn > MAX_TURN) {
            this.isGameOver = true;
            this.log("ゲーム終了");
        }
    }

    updateScores() {
        for(let p of this.players) p.score = 0;
        for(let r=0; r<N; r++) for(let c=0; c<N; c++) {
            const cell = this.grid[r][c];
            if(cell.owner !== -1) this.players[cell.owner].score += cell.value * cell.level;
        }
        const S0 = this.players[0].score;
        let SA = 0;
        for(let i=1; i<this.M; i++) if(this.players[i].score > SA) SA = this.players[i].score;
        const ratio = (SA === 0) ? (S0 > 0 ? 100 : 0) : (S0 / SA);
        const absScore = Math.round(100000 * Math.log2(1 + ratio));
        document.getElementById('abs-score').innerText = absScore.toLocaleString();
    }

    log(msg) {
        const div = document.getElementById('log');
        div.innerHTML = `<div>[T${this.turn}] ${msg}</div>` + div.innerHTML;
    }

    reset() { this.init(); }

    render() {
        if (!this.grid || this.grid.length === 0 || this.players.length === 0) return;

        const boardDiv = document.getElementById('board');
        boardDiv.innerHTML = '';
        const validMoves = (!this.isGameOver) ? this.getValidMoves(0) : [];
        const validMoveSet = new Set(validMoves.map(m => `${m.r},${m.c}`));

        // Prediction
        const showTargets = document.getElementById('show-ai-targets').checked;
        const aiTargets = new Map();
        if (showTargets && !this.isGameOver) {
            for(let i=1; i<this.M; i++) {
                // For prediction, use r2=0.5 (average tie break) or try to use future r?
                // lib.rs uses a specific r2 for tie breaking.
                // We can use the ACTUAL r2 for accurate prediction if available
                const rndIdx = this.turn - 1;
                const aiIdx = i - 1;
                let predR2 = 0.5;
                if(this.aiRandoms[rndIdx] && this.aiRandoms[rndIdx][aiIdx]) {
                    predR2 = this.aiRandoms[rndIdx][aiIdx].r2;
                }

                const moves = this.getValidMoves(i);
                if(moves.length > 0) {
                    const best = this.getBestMove(i, moves, this.players[i].trueParams, predR2);
                    const key = `${best.r},${best.c}`;
                    if(!aiTargets.has(key)) aiTargets.set(key, []);
                    aiTargets.get(key).push(i);
                }
            }
        }

        // Viz
        const vizTargetId = parseInt(document.getElementById('viz-target').value);
        const isVizMode = (vizTargetId !== -1);
        let vizParams = null;
        let maxVizScore = 1;

        if(isVizMode && this.players[vizTargetId]) {
            const isCheat = document.getElementById('use-true-params').checked;
            if(isCheat) vizParams = this.players[vizTargetId].trueParams;
            else vizParams = this.getEstParamsFromUI();

            for(let r=0; r<N; r++) for(let c=0; c<N; c++) {
                const s = this.calcScore(vizTargetId, r, c, vizParams);
                if(s > maxVizScore) maxVizScore = s;
            }
        }

        for(let r=0; r<N; r++) {
            for(let c=0; c<N; c++) {
                const cell = this.grid[r][c];
                const div = document.createElement('div');
                div.className = 'cell';

                if(cell.owner !== -1) {
                    div.style.backgroundColor = PLAYER_COLORS[cell.owner] + '40';
                    div.style.border = `2px solid ${PLAYER_COLORS[cell.owner]}`;
                } else {
                    div.style.border = '1px solid #ced4da';
                }

                let innerHTML = `
                    <div class="cell-info">
                        <span class="val">${cell.value}</span>
                        <span class="lvl">Lv.${cell.level}</span>
                    </div>
                `;

                if(isVizMode) {
                    const score = this.calcScore(vizTargetId, r, c, vizParams);
                    const percent = Math.min(100, (score / maxVizScore) * 100);
                    innerHTML += `
                        <div class="cell-viz" style="display:block;">
                            <div class="viz-bar" style="width:${percent}%"></div>
                            <div class="viz-text">${Math.floor(score)}</div>
                        </div>
                    `;
                }

                if(aiTargets.has(`${r},${c}`)) {
                    const pids = aiTargets.get(`${r},${c}`);
                    let markersHtml = `<div class="target-container">`;
                    pids.forEach(pid => {
                        markersHtml += `<div class="target-marker" style="color:${PLAYER_COLORS[pid]}"></div>`;
                    });
                    markersHtml += `</div>`;
                    innerHTML += markersHtml;
                }

                div.innerHTML = innerHTML;

                if(validMoveSet.has(`${r},${c}`)) {
                    div.classList.add('reachable');
                    div.onclick = () => this.handlePlayerClick(r, c);
                }

                if(cell.piece !== -1) {
                    const p = document.createElement('div');
                    p.className = 'piece';
                    p.style.backgroundColor = PLAYER_COLORS[cell.piece];
                    p.style.boxShadow = '1px 1px 4px rgba(0,0,0,0.5)';
                    div.appendChild(p);
                }
                boardDiv.appendChild(div);
            }
        }

        document.getElementById('turn-display').innerText = `${Math.min(this.turn, MAX_TURN)} / ${MAX_TURN}`;
        const scoresDiv = document.getElementById('scores');
        scoresDiv.innerHTML = this.players.map(p => `
            <div class="stat-row">
                <span style="color:${PLAYER_COLORS[p.id]}"><b>${PLAYER_NAMES[p.id]}</b></span>
                <b>${p.score}</b>
            </div>
        `).join('');
    }
}

const game = new Game();