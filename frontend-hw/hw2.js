'use strict';

/**
 * Телефонная книга
 */
const phoneBook = new Map();

/**
 * Вызывайте эту функцию, если есть синтаксическая ошибка в запросе
 * @param {number} lineNumber – номер строки с ошибкой
 * @param {number} charNumber – номер символа, с которого запрос стал ошибочным
 */
function syntaxError(lineNumber, charNumber) {
    throw new Error(`SyntaxError: Unexpected token at ${lineNumber}:${charNumber}`);
}

/**
 * Выполнение запроса на языке pbQL
 * @param {string} query
 * @returns {string[]} - строки с результатами запроса
 */
function run(query) {
    let requests = query.split(";");
    if (requests.slice(-1)[0].match(new RegExp("[a-z,0-9A-Z]")) !== null) {
        syntaxError(requests.length, requests.join(";").length + 1)
    }
    let ans = [];
    for (let t = 0; t < requests.length - 1; t++) {
        let request = requests[t].split(" ");
        let pos = 1;
        switch (request[0]) {
            case "Создай":
                pos += request[0].length + 1;
                if (request[1] !== "контакт") {
                    syntaxError(t + 1, pos);
                }
                pos += request[1].length + 1;
                let name = request.slice(2).join(" ");
                if (!phoneBook.has(name)) {
                    phoneBook.set(name, { phones: [], mails: [] });
                }
                pos += name.length + request.length > 2 ? 1 : 0;
                break;
            case "Удали":
                switch (request[1]) {
                    case "контакт":
                        pos += "Удали контакт ".length;
                        if (request.length < 3) {
                            pos--
                        }
                        let name = request.slice(2).join(" ");
                        phoneBook.delete(name);
                        pos += name.length + 1;
                        break;
                    case "контакты,":
                        pos += "Удали контакты, ".length;
                        if (request[2] !== "где") {
                            syntaxError(t + 1, pos);
                        }
                        pos += request[2].length + 1;
                        if (request[3] !== "есть") {
                            syntaxError(t + 1, pos);
                        }
                        pos += request[3].length + 1;
                        if (request.length < 5) {
                            syntaxError(t + 1, pos)
                        }
                        const arg = request.slice(4).join(" ");
                        if (arg !== "") {
                            let toDel = [];
                            phoneBook.forEach((value, key, _) => {
                                if (key.includes(arg)
                                    || value.phones.some(x => x.includes(arg))
                                    || value.mails.some(x => x.includes(arg))) {
                                    toDel.push(key);
                                }
                            })
                            for (let del of toDel) {
                                phoneBook.delete(del);
                            }
                        }
                        break;
                    default:
                        let mailsToDelete = []
                        let phonesToDelete = []
                        pos += "Удали ".length
                        if (request[1] !== "почту" && request[1] !== "телефон") {
                            syntaxError(t + 1, pos)
                        }

                        let i = 1;
                        for (i = 1; i < request.length && (request[i] === "почту" || request[i] === "телефон");) {
                            if (request[i] === "почту") {
                                i++;
                                pos += 6
                                if (request[i] === undefined) {
                                    syntaxError(t + 1, pos - 1)
                                }
                                mailsToDelete.push(request[i])
                                pos += request[i].length + 1
                                i++
                            } else if (request[i] === "телефон") {
                                i++
                                pos += 8
                                if (request[i] === undefined) {
                                    syntaxError(t + 1, pos - 1)
                                }
                                if (!request[i].match("^[0-9]{10}$")) {
                                    syntaxError(t + 1, pos)
                                }
                                phonesToDelete.push(request[i])
                                pos += request[i].length + 1
                                i++
                            } else {
                                syntaxError(t + 1, pos)
                            }
                            if (request[i] === "и") {
                                i++
                                pos += 2
                            } else break
                        }

                        if (request[i] !== "для") {
                            syntaxError(t + 1, pos)
                        }
                        pos += 4
                        i++
                        if (request[i] !== "контакта") {
                            syntaxError(t + 1, pos)
                        }
                        pos += 9
                        i++
                        if (request[i] === undefined) {
                            break
                        }
                        const r = request.slice(i).join(" ")
                        let flag = true
                        for (let char of r) {
                            if (char !== " ") {
                                flag = false
                            }
                        }
                        pos += r.length + 1
                        if (flag) break
                        if (phoneBook.has(r)) {
                            for (let phone of phonesToDelete) {
                                phoneBook.get(r).phones.splice(phoneBook.get(r).phones.indexOf(phone), 1)
                            }
                            for (let mail of mailsToDelete) {
                                phoneBook.get(r).mails.splice(phoneBook.get(r).mails.indexOf(mail), 1)
                            }
                        }
                }
                break;
            case "Добавь":
                let phonesToAdd = []
                let mailsToAdd = []
                pos += 7
                if (request[1] !== "почту" && request[1] !== "телефон") {
                    syntaxError(t + 1, pos)
                }

                let i = 1;
                for (i = 1; i < request.length && (request[i] === "почту" || request[i] === "телефон");) {
                    if (request[i] === "почту") {
                        i++;
                        pos += 6
                        if (request[i] === undefined) {
                            syntaxError(t + 1, pos - 1)
                        }
                        mailsToAdd.push(request[i])
                        pos += request[i].length + 1
                        i++
                    } else if (request[i] === "телефон") {
                        i++
                        pos += 8
                        if (request[i] === undefined) {
                            syntaxError(t + 1, pos - 1)
                        }
                        if (!request[i].match("^[0-9]{10}$")) {
                            syntaxError(t + 1, pos)
                        }
                        phonesToAdd.push(request[i])
                        pos += request[i].length + 1
                        i++
                    } else {
                        syntaxError(t + 1, pos)
                    }
                    if (request[i] === "и") {
                        i++
                        pos += 2
                    } else break
                }

                if (request[i] !== "для") {
                    syntaxError(t + 1, pos)
                }
                pos += 4
                i++
                if (request[i] !== "контакта") {
                    syntaxError(t + 1, pos)
                }
                pos += 9
                i++
                if (request[i] === undefined) {
                    break
                }
                const r = request.slice(i).join(" ")
                let flag = true
                for (let char of r) {
                    if (char !== " ") {
                        flag = false
                    }
                }
                pos += r.length + 1
                if (flag) break
                if (phoneBook.has(r)) {
                    for (let phone of phonesToAdd) {
                        if (phoneBook.get(r).phones.includes(phone)) {
                            continue
                        }
                        phoneBook.get(r).phones.push(phone)
                    }
                    for (let mail of mailsToAdd) {
                        if (phoneBook.get(r).mails.includes(mail)) {
                            continue
                        }
                        phoneBook.get(r).mails.push(mail)
                    }
                }
                break;
            case "Покажи":
                let show = []
                pos += 7
                if (request[1] !== "почты" && request[1] !== "телефоны" && request[1] !== "имя") {
                    syntaxError(t + 1, pos)
                }

                let j = 1;
                for (j = 1; j < request.length && (request[j] === "почты" || request[j] === "телефоны" || request[j] === "имя");) {
                    if (request[j] === "почты") {
                        pos += 6
                        show.push(request[j])
                        j++
                    } else if (request[j] === "телефоны") {
                        pos += 9
                        show.push(request[j])
                        j++
                    } else if (request[j] === "имя") {
                        pos += 4
                        show.push(request[j])
                        j++
                    } else {
                        syntaxError(t + 1, pos)
                    }
                    if (request[j] === "и") {
                        j++
                        pos += 2
                    } else break
                }

                if (request[j] !== "для") {
                    syntaxError(t + 1, pos)
                }
                pos += 4
                j++
                if (request[j] !== "контактов,") {
                    syntaxError(t + 1, pos)
                }
                pos += 11
                j++
                if (request[j] !== "где") {
                    syntaxError(t + 1, pos)
                }
                j++
                pos += 4
                if (request[j] !== "есть") {
                    syntaxError(t + 1, pos)
                }
                j++
                pos += 5
                if (request[j] === undefined) {
                    break
                }
                const q = request.slice(j).join(" ")
                let f = true
                for (let char of q) {
                    if (char !== " ") {
                        f = false
                    }
                }
                pos += q.length + 1
                if (f) break

                phoneBook.forEach((value, key, _) => {
                    if (key.includes(q)
                        || value.mails.some(mail => mail.includes(q))
                        || value.phones.some(phone => phone.includes(q))) {
                        let res = ""
                        for (let i in show) {
                            if (show[i] === "имя") {
                                res += `${key}`
                            } else if (show[i] === "почты") {
                                res += value.mails.join(',')
                            } else if (show[i] === "телефоны") {
                                res += value.phones.map(phone => `+7 (${phone.slice(0, 3)}) ${phone.slice(3, 6)}-${phone.slice(6, 8)}-${phone.slice(8, 10)}`).join(',')
                            }
                            if (i < show.length - 1) {
                                res += ";"
                            }
                        }
                        ans.push(res)
                    }
                })

                break;
            default:
                syntaxError(t + 1, pos);
        }
    }
    return ans;
}

module.exports = { phoneBook, run };