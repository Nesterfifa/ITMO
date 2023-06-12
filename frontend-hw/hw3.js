'use strict';

/**
 * @param {Object} schedule Расписание Банды
 * @param {number} duration Время на ограбление в минутах
 * @param {Object} workingHours Время работы банка
 * @param {string} workingHours.from Время открытия, например, "10:00+5"
 * @param {string} workingHours.to Время закрытия, например, "18:00+5"
 * @returns {Object}
 */
function getAppropriateMoment(schedule, duration, workingHours) {
    const dayToIndex = {
        "ПН": 0,
        "ВТ": 1,
        "СР": 2,
        "ЧТ": 3,
        "ПТ": 4,
        "СБ": 5,
        "ВС": 6
    }
    const indexToDay = {
        0: "ПН",
        1: "ВТ",
        2: "СР",
        3: "ЧТ",
        4: "ПТ",
        5: "СБ",
        6: "ВС"
    }

    let isFound = false;
    let robberyStart = null;
    let robberyDay = null;
    let mergedSchedule = [];
    const timeZone = parseInt(workingHours.from.split("+")[1]);

    for (let i = 0; i < 7; i++) {
        mergedSchedule.push(
            [parseInt(workingHours.from.split(":")[0]) * 60
            + parseInt(workingHours.from.split(":")[1].split("+")[0])
            + 1440 * i, 3],
            [parseInt(workingHours.to.split(":")[0]) * 60
            + parseInt(workingHours.to.split(":")[1].split("+")[0])
            + 1440 * i, 3]);
    }

    let cnt = 0;
    for (let member in schedule) {
        for (let hours of schedule[member]) {
            mergedSchedule.push(
                [(1440 * dayToIndex[hours.from.split(" ")[0]]
                    + parseInt(hours.from.split(" ")[1].split(":")[0] * 60)
                    + parseInt(hours.from.split(":")[1].split("+")[0])
                    + (timeZone - hours.from.split("+")[1]) * 60
                    + 1440 * 7) % (1440 * 7), cnt],
                [(1440 * dayToIndex[hours.to.split(" ")[0]]
                    + parseInt(hours.to.split(" ")[1].split(":")[0] * 60)
                    + parseInt(hours.to.split(":")[1].split("+")[0])
                    + (timeZone - hours.to.split("+")[1]) * 60
                    + 1440 * 7) % (1440 * 7), cnt]);
        }
        cnt++;
    }
    mergedSchedule.sort((a, b) => {
        if (a[0] < b[0]) return -1;
        if (a[0] > b[0]) return 1;
        return 0;
    });
    let free = [1, 1, 1, 0];
    let prevTime = 0;
    let index = 0;
    for (; index < mergedSchedule.length; index++) {
        if (mergedSchedule[index][0] >= 1440 * 3) break;
        if (free.reduce((a, b) => a + b, 0) === 4 && mergedSchedule[index][0] - prevTime >= duration) {
            isFound = true;
            robberyStart = prevTime % 1440;
            robberyDay = indexToDay[Math.floor(prevTime / 1440)];
            break;
        }
        prevTime = mergedSchedule[index][0];
        free[mergedSchedule[index][1]] = 1 - free[mergedSchedule[index][1]];
    }
    return {
        /**
         * Найдено ли время
         * @returns {boolean}
         */
        exists() {
            return isFound;
        },

        /**
         * Возвращает отформатированную строку с часами
         * для ограбления во временной зоне банка
         *
         * @param {string} template
         * @returns {string}
         *
         * @example
         * ```js
         * getAppropriateMoment(...).format('Начинаем в %HH:%MM (%DD)') // => Начинаем в 14:59 (СР)
         * ```
         */
        format(template) {
            if (!isFound) return "";
            return template
                .replace("%HH", ('0' + Math.floor(robberyStart % 1440 / 60)).slice(-2))
                .replace("%MM", ('0' + robberyStart % 1440 % 60).slice(-2))
                .replace("%DD", robberyDay);
        },

        /**
         * Попробовать найти часы для ограбления позже [*]
         * @note Не забудь при реализации выставить флаг `isExtraTaskSolved`
         * @returns {boolean}
         */
        tryLater() {
            if (!isFound) return false;
            prevTime += 30;
            for (; index < mergedSchedule.length; index++) {
                if (mergedSchedule[index][0] >= 1440 * 3) break;
                if (free.reduce((a, b) => a + b, 0) === 4 && mergedSchedule[index][0] - prevTime >= duration) {
                    isFound = true;
                    robberyStart = prevTime % 1440;
                    robberyDay = indexToDay[Math.floor(prevTime / 1440)];
                    break;
                }
                prevTime = mergedSchedule[index][0];
                free[mergedSchedule[index][1]] = 1 - free[mergedSchedule[index][1]];
            }
            return false;
        }
    };
}

module.exports = {
    getAppropriateMoment
};
