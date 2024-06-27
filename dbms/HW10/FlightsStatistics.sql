-- В моей реализации мы один раз читаем Flights, кроме вызова FreeSeats.
-- Справедливо все, что справедливо для FreeSeats.

start transaction read only isolation level read committed;