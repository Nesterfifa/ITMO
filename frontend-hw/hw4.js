/**
 * Возвращает новый emitter
 * @returns {Object}
 */
function getEmitter() {
    let students = []

    return {

        /**
         * Подписаться на событие
         * @param {String} event
         * @param {Object} context
         * @param {Function} handler
         */
        on: function (event, context, handler) {
            if (students.find(s => s === context) === undefined) {
                students.push(context)
            }
            if (context[event] === undefined) {
                context[event] = []
            }
            context[event].push(handler.bind(context))
            return this
        },

        /**
         * Отписаться от события
         * @param {String} event
         * @param {Object} context
         */
        off: function (event, context) {
            if (students.find(s => s === context) === undefined) {
                students.push(context)
            }
            delete context[event]
            for (let f in context) {
                if (f.startsWith(`${event}.`)) {
                    delete context[f]
                }
            }
            return this
        },

        /**
         * Уведомить о событии
         * @param {String} event
         */
        emit: function (event) {
            for (let student of students) {
                let events = []
                for (let field in student) {
                    if (field === event || event.startsWith(field + ".")) {
                        events.push(field)
                    }
                }
                events.sort((a, b) => a.length > b.length ? -1 : a.length === b.length ? 0 : 1)
                for (let e of events) {
                    for (let ee of student[e]) {
                        ee.call()
                    }
                }
            }
            return this
        },

        /**
         * Подписаться на событие с ограничением по количеству полученных уведомлений
         * @star
         * @param {String} event
         * @param {Object} context
         * @param {Function} handler
         * @param {Number} times – сколько раз получить уведомление
         */
        several: function (event, context, handler, times) {
            console.info(event, context, handler, times);
        },

        /**
         * Подписаться на событие с ограничением по частоте получения уведомлений
         * @star
         * @param {String} event
         * @param {Object} context
         * @param {Function} handler
         * @param {Number} frequency – как часто уведомлять
         */
        through: function (event, context, handler, frequency) {
            console.info(event, context, handler, frequency);
        }
    };
}

module.exports = {
    getEmitter
};

/*
let students = {
    Sam: {
        focus: 100,
        wisdom: 50
    },
    Sally: {
        focus: 100,
        wisdom: 60
    },
    Bill: {
        focus: 90,
        wisdom: 50
    },
    Sharon: {
        focus: 110,
        wisdom: 40
    }
};

let lecturer = getEmitter();

// С началом лекции у всех резко повышаются показатели
lecturer
    .on('begin', students.Sam, function () {
        this.focus += 10;
    })
    .on('begin', students.Sally, function () {
        this.focus += 10;
    })
    .on('begin', students.Bill, function () {
        this.focus += 10;
        this.wisdom += 5;
    })
    .on('begin', students.Sharon, function () {
        this.focus += 20;
    });

// На каждый слайд внимательность падает, но растет мудрость
lecturer
    .on('slide', students.Sam, function () {
        this.wisdom += Math.round(this.focus * 0.1);
        this.focus -= 10;
    })
    .on('slide', students.Sally, function () {
        this.wisdom += Math.round(this.focus * 0.15);
        this.focus -= 5;
    })
    .on('slide', students.Bill, function () {
        this.wisdom += Math.round(this.focus * 0.05);
        this.focus -= 10;
    })
    .on('slide', students.Sharon, function () {
        this.wisdom += Math.round(this.focus * 0.01);
        this.focus -= 5;
    });

// На каждый веселый слайд всё наоборот
lecturer
    .on('slide.funny', students.Sam, function () {
        this.focus += 5;
        this.wisdom -= 10;
    })
    .on('slide.funny', students.Sally, function () {
        this.focus += 5;
        this.wisdom -= 5;
    })
    .on('slide.funny', students.Bill, function () {
        this.focus += 5;
        this.wisdom -= 10;
    })
    .on('slide.funny', students.Sharon, function () {
        this.focus += 10;
        this.wisdom -= 10;
    });

// Начинаем лекцию
lecturer.emit('begin');
// Sam(110,50); Sally(110,60); Bill(100,55); Sharon(130,40)

lecturer
    .emit('slide.text')
    .emit('slide.text')
    .emit('slide.text')
    .emit('slide.funny');
// Sam(75,79); Sally(95,118); Bill(65,63); Sharon(120,34)

lecturer
    .off('slide.funny', students.Sharon)
    .emit('slide.text')
    .emit('slide.text')
    .emit('slide.funny');
// Sam(50,90); Sally(85,155); Bill(40,62); Sharon(105,37)

lecturer
    .off('slide', students.Bill)
    .emit('slide.text')
    .emit('slide.text')
    .emit('slide.text');

lecturer.emit('end');
// Sam(20,102); Sally(70,191); Bill(40,62); Sharon(90,40)
console.log(students)
*/
