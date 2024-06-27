-- Косая запись нам не страшна, так как мы только вставляем данные
-- и параллельное бронирование двух разных мест не может нарушить 
-- консистентность. Кроме того, нам не страшны фантомная запись и
-- неповторяемое чтение по той же причине, что и во FreeSeats.
-- read uncommitted не подойдет, потому что мы вставляем данные.
-- Итого read committed.

start transaction isolation level read committed;