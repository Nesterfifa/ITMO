'use strict';

/**
 * Складывает два целых числа
 * @param {Number} a Первое целое
 * @param {Number} b Второе целое
 * @throws {TypeError} Когда в аргументы переданы не числа
 * @returns {Number} Сумма аргументов
 */
function abProblem(a, b) {
    if (typeof a === "number" && typeof b === "number") {
        return a + b;
    } else {
        throw new TypeError("Number arguments expected");
    }
}

/**
 * Определяет век по году
 * @param {Number} year Год, целое положительное число
 * @throws {TypeError} Когда в качестве года передано не число
 * @throws {RangeError} Когда год – отрицательное значение
 * @returns {Number} Век, полученный из года
 */
function centuryByYearProblem(year) {
    if (typeof year !== "number") {
        throw new TypeError("Year should be number");
    } else if (year < 0) {
        throw new RangeError("Year should be non-negative");
    } else {
        return Math.ceil(year / 100);
    }
}

/**
 * Переводит цвет из формата HEX в формат RGB
 * @param {String} hexColor Цвет в формате HEX, например, '#FFFFFF'
 * @throws {TypeError} Когда цвет передан не строкой
 * @throws {RangeError} Когда значения цвета выходят за пределы допустимых
 * @returns {String} Цвет в формате RGB, например, '(255, 255, 255)'
 */
function colorsProblem(hexColor) {
    if (typeof hexColor !== "string") {
        throw new TypeError("Hex color should be string");
    }
    if (!/^#[0-9a-fA-F]{6}$/.test(hexColor)) {
        throw new RangeError("Invalid color");
    }
    let red = parseInt(hexColor[1] + hexColor[2], 16);
    let green = parseInt(hexColor[3] + hexColor[4], 16);
    let blue = parseInt(hexColor[5] + hexColor[6], 16);
    return "(" + red + ", " + green + ", " + blue + ")";
}

/**
 * Находит n-ое число Фибоначчи
 * @param {Number} n Положение числа в ряде Фибоначчи
 * @throws {TypeError} Когда в качестве положения в ряде передано не число
 * @throws {RangeError} Когда положение в ряде не является целым положительным числом
 * @returns {Number} Число Фибоначчи, находящееся на n-ой позиции
 */
function fibonacciProblem(n) {
    if (typeof n !== "number") {
        throw new TypeError("Index should be numerical");
    }
    if (Math.floor(n) !== n || n <= 0) {
        throw new RangeError("Index should be positive integer value");
    }
    let fib = [0, 1];
    while (fib.length <= n) {
        let i = fib.length;
        fib.push(fib[i - 1] + fib[i - 2]);
    }
    return fib[n];
}

/**
 * Транспонирует матрицу
 * @param {(Any[])[]} matrix Матрица размерности MxN
 * @throws {TypeError} Когда в функцию передаётся не двумерный массив
 * @returns {(Any[])[]} Транспонированная матрица размера NxM
 */
function matrixProblem(matrix) {
    if (!(matrix instanceof Array && matrix.every(i => i instanceof Array))) {
        throw new TypeError("2D-array expected");
    }
    let n = matrix.length;
    let m = matrix[0].length;
    let transposed = [];
    for (let i = 0; i < m; i++) {
        transposed.push([]);
        for (let j = 0; j < n; j++) {
            transposed[i].push(matrix[j][i]);
        }
    }
    return transposed;
}

/**
 * Переводит число в другую систему счисления
 * @param {Number} n Число для перевода в другую систему счисления
 * @param {Number} targetNs Система счисления, в которую нужно перевести (Число от 2 до 36)
 * @throws {TypeError} Когда переданы аргументы некорректного типа
 * @throws {RangeError} Когда система счисления выходит за пределы значений [2, 36]
 * @returns {String} Число n в системе счисления targetNs
 */
function numberSystemProblem(n, targetNs) {
    if (typeof n !== "number" || typeof targetNs !== "number") {
        throw new TypeError("Number arguments expected");
    }
    if (targetNs < 2 || targetNs > 36) {
        throw new RangeError("New numerical system should be in interval [2, 36]");
    }
    return n.toString(targetNs);
}

/**
 * Проверяет соответствие телефонного номера формату
 * @param {String} phoneNumber Номер телефона в формате '8–800–xxx–xx–xx'
 * @throws {TypeError} Когда в качестве аргумента передаётся не строка
 * @returns {Boolean} Если соответствует формату, то true, а иначе false
 */
function phoneProblem(phoneNumber) {
    if (typeof phoneNumber !== "string") {
        throw new TypeError("String expected");
    }
    return /^8-800-[0-9]{3}-[0-9]{2}-[0-9]{2}$/.test(phoneNumber);
}

/**
 * Определяет количество улыбающихся смайликов в строке
 * @param {String} text Строка в которой производится поиск
 * @throws {TypeError} Когда в качестве аргумента передаётся не строка
 * @returns {Number} Количество улыбающихся смайликов в строке
 */
function smilesProblem(text) {
    if (typeof text !== "string") {
        throw new TypeError("String expected");
    }
    const regexp = /(:-\))|(\(-:)/g;
    let ans = 0;
    while (regexp.exec(text) !== null) {
        ans++;
    }
    return ans;
}

/**
 * Определяет победителя в игре "Крестики-нолики"
 * Тестами гарантируются корректные аргументы.
 * @param {(('x' | 'o')[])[]} field Игровое поле 3x3 завершённой игры
 * @returns {'x' | 'o' | 'draw'} Результат игры
 */
function ticTacToeProblem(field) {
    const n = 3;
    for (let i = 0; i < n; i++) {
        let rowWin = 0;
        let colWin = 0;
        let diagWin = 0;
        let rDiagWin = 0;
        for (let j = 0; j < n; j++) {
            rowWin += field[i][j] === 'x' ? 1 : -1;
            colWin += field[j][i] === 'x' ? 1 : -1;
            diagWin += field[j][j] === 'x' ? 1 : -1;
            rDiagWin += field[j][n - j - 1] === 'x' ? 1 : -1;
        }
        if (rowWin === 3 || colWin === 3 || diagWin === 3 || rDiagWin === 3) {
            return 'x';
        } else if (rowWin === -3 || colWin === -3 || diagWin === -3 || rDiagWin === -3) {
            return 'o';
        }
    }
    return 'draw';
}

module.exports = {
    abProblem,
    centuryByYearProblem,
    colorsProblem,
    fibonacciProblem,
    matrixProblem,
    numberSystemProblem,
    phoneProblem,
    smilesProblem,
    ticTacToeProblem
};
