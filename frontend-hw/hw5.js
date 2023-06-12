'use strict';

/**
 * Итератор по друзьям
 * @constructor
 * @param {Object[]} friends
 * @param {Filter} filter
 */
function Iterator(friends, filter) {
    this.filter = filter
    let queue = {
        content: [],
        l: 0,
        r: 0,

        push: function(elem) {
            this.content[this.r++] = elem
        },

        pop: function() {
            if (this.l === this.r) {
                throw new RangeError("queue is empty")
            }
            return this.content[this.l++];
        },

        isEmpty: function() {
            return this.r - this.l === 0
        }
    }

    this.dist = new Map()
    for (let friend of friends) {
        this.dist[friend.name] = friend.best ? 1 : 100000000000
        if (friend.best) {
            queue.push(friend)
        }
    }

    while (!queue.isEmpty()) {
        let v = queue.pop()
        for (let friend of v.friends) {
            if (this.dist[friend] > this.dist[v.name] + 1) {
                let person = friends.find(x => x.name === friend)
                queue.push(person)
                this.dist[friend] = this.dist[v.name] + 1
            }
        }
    }

    this.data = (() => {
        let friendsCopy = friends.slice(0).filter(this.filter.check)
        friendsCopy.sort((a, b) =>
            this.dist[a.name] < this.dist[b.name] ? -1
                : this.dist[a.name] > this.dist[b.name] ? 1
                : a.name.localeCompare(b.name))
        return friendsCopy.filter(x => this.dist[x.name] < 10000000)
    })()
}

Iterator.prototype.done = function() {
    return !this.data.length
}

Iterator.prototype.next = function() {
    return !this.done() ? this.data.shift() : null
}

/**
 * Итератор по друзям с ограничением по кругу
 * @extends Iterator
 * @constructor
 * @param {Object[]} friends
 * @param {Filter} filter
 * @param {Number} maxLevel – максимальный круг друзей
 */
function LimitedIterator(friends, filter, maxLevel) {
    Iterator.call(this, friends, filter)
    this.data = this.data.filter(x => this.dist[x.name] <= maxLevel)
}

Object.setPrototypeOf(LimitedIterator.prototype, Iterator.prototype)

/**
 * Фильтр друзей
 * @constructor
 */
function Filter() {
    this.check = () => true
}

/**
 * Фильтр друзей
 * @extends Filter
 * @constructor
 */
function MaleFilter() {
    Filter.call(this)
    this.check = x => x.hasOwnProperty("gender") && x.gender === "male"
}

Object.setPrototypeOf(MaleFilter.prototype, Filter.prototype)

/**
 * Фильтр друзей-девушек
 * @extends Filter
 * @constructor
 */
function FemaleFilter() {
    Filter.call(this)
    this.check = x => x.hasOwnProperty("gender") && x.gender === "female"
}

Object.setPrototypeOf(FemaleFilter.prototype, Filter.prototype)

exports.Iterator = Iterator;
exports.LimitedIterator = LimitedIterator;

exports.Filter = Filter;
exports.MaleFilter = MaleFilter;
exports.FemaleFilter = FemaleFilter;
