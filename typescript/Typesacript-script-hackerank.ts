'use strict';

import { WriteStream, createWriteStream } from "fs";
process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString: string = '';
let inputLines: string[] = [];
let currentLine: number = 0;

process.stdin.on('data', function(inputStdin: string): void {
    inputString += inputStdin;
});

process.stdin.on('end', function(): void {
    inputLines = inputString.split('\n');
    inputString = '';

    main();
});

function readLine(): string {
    return inputLines[currentLine++];
}

/**
 * Busca los numeros que comparten relacion segun ua lista dada 1D y una lista 2D
 * con para buscar la relacion.
 * 
 * @param group Grupo de numeros dados que ya comparten relacion y que se buscaran en la lista.
 * @param astronaut Lista de grupos en desorden  que comparten relacion para buscar.
 * @returns 
 */
function lookForCompatriot(group: number[], astronaut: number[][]): number[] {
  let cleanGorup: number[] = [];
  // Se buscara cada numero dado en el grupo de entrada.
  for(let i: number = 0; i < group.length; i++) {
      if (!astronaut.find((subArr) => subArr.includes(group[i]))) continue; // Validar si existe al menos un grupo con el numero igual al buscado.
    // Busca cada numero del grupo dado en la lista en desorden.
    const wantedCompatriots: number[][] = astronaut.filter((subArr, index) => {
      if (subArr.includes(group[i])) {
        astronaut.splice(index, 1); // Se elimina el grupo encontrado de la lista en desorden (Permite poder usar la funcion de forma recursiva sin que se vuelva un llamado infinito)
        return true;
      }
      return false;
    });
    let dirtyGroup: number[] = cleanGorup.concat(wantedCompatriots.flat()); // Concatenar los pares encontrados.
    // Si se encontraron numeros que comparten relacion.
    if(dirtyGroup.length) {
      dirtyGroup = [...new Set(dirtyGroup)]; // Se limpia el array de posibles numeros repetidos
      // Como se ha encontrado un nuevo grupo de numeros que comparten relacion y estos a su vez
      // pueden contener numeros que NO llegaron en el grupo de entrada, pero que aun asi ahora
      // comparten relacion, se llama de manera recursiva nuevamente a la funcion para que busque
      // nuevamente en la lista desordenada.
      dirtyGroup = dirtyGroup.concat(lookForCompatriot(dirtyGroup, astronaut)); // Se concatenan todos los numeros enconrados que comparten relacion.
    }
    cleanGorup = cleanGorup.concat(dirtyGroup);
  }
  cleanGorup = [...new Set(cleanGorup)]; // Se limpia el arary de posibles numeros repetidos.
  return cleanGorup; // Se retorna el grupo limpio de todos los numeros que comparten relacion.
}

/**
 * Calcula la cantidad de combinaciones posibles segun una lista 2D de numeros no repetidos,
 * agrupando en parejas de dos sin repetoir numeros del mismo grupo.
 * Los grupos de numeros no repetidos pueden tener diferente longitud.
 * 
 * @param groups Lista con los grupos de numeros, ejemplo: [[2,4], [1,0,7], [6]]
 * @returns Cantidad de combinaciones posibles.
 */
function getCombinations(n: number, groups: number[][]): number {
  let combinations = 0;
  let optionsWithGroup = 0;
  // Recorre la cantidad de grupos totales en la lista.
  for (let i = 0; i < groups.length; i++) {
    // Recorre los grupos siguientes al grupo dado segun el ciclo anterior.
    optionsWithGroup += groups[i].length;
    for (let j: number = i + 1; j < groups.length; j++) {
      // Se multiplica la longitud en el grupo segun el ciclo mas externo por
      // la longitud en el grupo siguiente, ejemplo:
      // Para  la lista [[2,4], [1,0,7], [6]] se multiplica 2 x 3 que es la longitud de los primeros dos grupos
      const mult: number = groups[i].length * groups[j].length;
      combinations += mult; // Se Suma la cantidad de combinaciones calculadas para cada multiplicacion.
    }
  }

  // contar combinaciones para la opciones que quedaron fuera del grupo.
  // Se sigue el siguiente planteamiento, si los numeros posibles eran del 7 (n) y se
  // encontraron grupos para 2 de ellos, Eso quiere decir que faltaron 5 (f) numeros.
  // Las combinaciones posibles de estos numeros s puede hallar sumando la sequencia incremental
  // desde 1 hasta (f-1), para el ejemplo seria 1 hasta (5-1) -> 1 + 2 + 3 + 4 = 10 combinaciones posibles
  const optionsWithoutGroup = n - optionsWithGroup;
  let combWithoutGroup = 0;
  if (optionsWithoutGroup > 0) {
    const ivec: number[] = Array.from( // Se crea la secuencia de numeros de 1 hasta (f-1)
      { length: optionsWithoutGroup - 1 },
      (_, i) => i + 1,
    );
    combWithoutGroup = ivec.reduce((partialSum, a) => partialSum + a, 0); // Se suman todos los numeros de la sequencia.
  }

  // contar combinaciones posibles entre opciones en grupo y fuera del grupo
  const combMixed: number = optionsWithGroup * optionsWithoutGroup;
  return combinations + combMixed + combWithoutGroup;
}

/**
 * Calcula la cantidad posible de combinaciones de parejas de astronautas 
 * de diferentes nacionalidades segun una lista data de astronautas que comparten 
 * nacionalidad y un valor n de la cantidad de astronautas.
 * 
 * @param n Numero maximo de astronautas que iran a la luna, comienzan en cero.
 * @param astronaut Lista 2D de parejas de astronautas que comparten nacionalidad
 * @returns La cantidad de combinaciones posibles.
 */
function journeyToMoon(n: number, astronaut: number[][]): number {
  const groups: number[][] = [];

  // Buscar los compatriotas de cada astronauta.
  for (let i = 0; i < n; i++) {
    if (astronaut.length == 0) break; // Evitar seguir buscando cuando la lista de entrada este vacia.
    if (groups.find((subArr) => subArr.includes(i))) continue; // Evita buscar numeros que ya esta en un grupo.
    const group: number[] = lookForCompatriot([i], astronaut); // Funcion que busca los grupos de compatriotas.
    if (group.length) groups.push(group); // Agregar grupo en el caso de encontrar en la lista dada de compatriotas.
    // if (!groups.find((subArr) => subArr.includes(i))) groups.push([i]); // Agregar en el caso de no encontrar en la lista de compatriotas y que no se encuentre en ningun grupo ya agregado.
  }
  const combinations = getCombinations(n, groups); // Funcion que calcula la cantidad de combinaciones posibles
  return combinations;
}

function main() {
    const ws: WriteStream = createWriteStream(process.env['OUTPUT_PATH']);

    const firstMultipleInput: string[] = readLine().replace(/\s+$/g, '').split(' ');

    const n: number = parseInt(firstMultipleInput[0], 10);

    const p: number = parseInt(firstMultipleInput[1], 10);

    let astronaut: number[][] = Array(p);

    for (let i: number = 0; i < p; i++) {
        astronaut[i] = readLine().replace(/\s+$/g, '').split(' ').map(astronautTemp => parseInt(astronautTemp, 10));
    }
    const ats2 = astronaut;
    const result: number = journeyToMoon(n, astronaut);

    ws.write(result + '\n');

    ws.end();
}
