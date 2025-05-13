const fs = require("fs");
const path = require("path");

if (process.argv.length !== 4) {
  console.error("Usage: node sat.js <input.sa> <output.o>");
  process.exit(1);
}

const inputFile = process.argv[2];
const outputFile = process.argv[3];

const MEMORY_SIZE = 128;

const COMMANDS = {
  NOP: 0x00,
  CPUINFO: 0x01,
  READ: 0x0a,
  WRITE: 0x0b,
  LOAD: 0x14,
  STORE: 0x15,
  ADD: 0x1e,
  SUB: 0x1f,
  DIVIDE: 0x20,
  MUL: 0x21,
  JUMP: 0x28,
  JNEG: 0x29,
  JZ: 0x2a,
  HALT: 0x2b,
  NOT: 0x33,
  AND: 0x34,
  OR: 0x35,
  XOR: 0x36,
  JNS: 0x37,
  JC: 0x38,
  JNC: 0x39,
  JP: 0x3a,
  JNP: 0x3b,
  CHL: 0x3c,
  SHR: 0x3d,
  RCL: 0x3e,
  RCR: 0x3f,
  NEG: 0x40,
  ADDC: 0x41,
  SUBC: 0x42,
  LOGLC: 0x43,
  LOGRC: 0x44,
  RCCL: 0x45,
  RCCR: 0x46,
  MOVA: 0x47,
  MOVR: 0x48,
  MOVCA: 0x49,
  MOVCR: 0x4a,
};

const memory = new Int32Array(MEMORY_SIZE).fill(0);

function parseLine(line) {
  const commentIndex = line.indexOf(";");
  if (commentIndex !== -1) {
    line = line.slice(0, commentIndex);
  }
  line = line.trim();
  if (!line) return null;

  const parts = line.split(/\s+/);
  if (parts.length < 3) return null;

  const address = parseInt(parts[0], 10);
  if (isNaN(address) || address < 0 || address >= MEMORY_SIZE) {
    throw new Error(`Invalid memory address: ${parts[0]}`);
  }

  const command = parts[1];
  const operandStr = parts[2];

  if (command === "=") {
    const val = parseInt(operandStr, 10);
    if (isNaN(val)) {
      throw new Error(`Invalid value at address ${address}: ${operandStr}`);
    }
    return { address, value: val };
  } else {
    const cmdCode = COMMANDS[command.toUpperCase()];
    if (cmdCode === undefined) {
      throw new Error(`Unknown command at address ${address}: ${command}`);
    }
    const operand = parseInt(operandStr, 10);
    if (isNaN(operand) || operand < 0 || operand >= MEMORY_SIZE) {
      throw new Error(`Invalid operand at address ${address}: ${operandStr}`);
    }
    return { address, cmdCode, operand };
  }
}

function encodeCommand(cmdCode, operand) {
  return (cmdCode << 7) | operand;
}

try {
  const lines = fs.readFileSync(inputFile, "utf8").split(/\r?\n/);

  for (const line of lines) {
    const parsed = parseLine(line);
    if (!parsed) continue;

    if ("value" in parsed) {
      memory[parsed.address] = parsed.value;
    } else {
      memory[parsed.address] = encodeCommand(parsed.cmdCode, parsed.operand);
    }
  }

  const buffer = Buffer.alloc(MEMORY_SIZE * 4);
  for (let i = 0; i < MEMORY_SIZE; i++) {
    buffer.writeInt32LE(memory[i], i * 4);
  }
  fs.writeFileSync(outputFile, buffer);

  console.log(`Translation completed. Output saved to ${outputFile}`);
} catch (err) {
  console.error("Error:", err.message);
  process.exit(1);
}
