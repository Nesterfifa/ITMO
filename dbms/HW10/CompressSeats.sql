-- Если происходит оптимизация мест, и кто-то паралелльно попытается 
-- купить билет, то возникнет косая запись. Нужен serializable.

start transaction isolation level serializable;