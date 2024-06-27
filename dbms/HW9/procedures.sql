-- Проверяет, что бронирование мест на рейс возможно
create or replace function is_booking_available(in flight_id int)
returns boolean
as
$$
begin
    return not exists
        (
            select flight_id
            from blocked
            where blocked.flight_id = is_booking_available.flight_id
            union all
            select flight_id 
            from flights
            where 
                flights.flight_time < now() + interval '3 days'
                and flights.flight_id = is_booking_available.flight_id
        );
end;
$$ language plpgsql;

-- Проверяет существование рейса
create or replace function has_flight(in flight_id int)
returns boolean
as
$$
begin
    return exists
        (
            select
                *
            from
                flights
            where
                flights.flight_id = has_flight.flight_id
        );
end;
$$ language plpgsql;

create extension pgcrypto;

-- Валидация пользователя
create or replace function has_user(in user_id int, in pass varchar(255))
returns boolean
as
$$
begin
    return exists
        (
            select
                *
            from
                users
            where
                users.user_id = has_user.user_id
                and users.pass = crypt(has_user.pass, users.salt)
        );
end;
$$ language plpgsql;

-- Находит seat_id по seat_no и flight_id
create or replace function get_seat_id(in seat_no varchar(4), in flight_id int)
returns int
as
$$
begin
    return
        (
            select
                seat_id
            from
                seats
                natural join fligths
            where
                flights.flight_id = get_seat_id.flight_id
                and seats.seat_no = get_seat_id.seat_no
        );
end;
$$ language plpgsql;

-- Проверяет, есть ли у юзера действующая бронь на место
create or replace function has_booking
    (
        in user_id int,
        in seat_id int,
        in flight_id int
    )
returns boolean
as
$$
begin
    return 
        exists
            (
                select
                    *
                from
                    bookings
                where
                    bookings.user_id = has_booking.user_id
                    and bookings.seat_id = has_booking.seat_id
                    and bookings.flight_id = has_booking.flight_id
                    and bookings.expiration_time > now()
            )
        and not exists
            (
                select
                    *
                from
                    purchases
                where
                    purchases.seat_id = has_booking.seat_id
                    and purchases.flight_id = has_booking.flight_id
            );
end;
$$ language plpgsql;

-- Генерация booking_id
create or replace function generate_booking_id()
returns int
as
$$
begin
    return coalesce((select max(booking_id) from bookings), 0) + 1;
end;
$$ language plpgsql;

-- Генерация purchase_id
create or replace function generate_purchase_id()
returns int
as
$$
begin
    return coalesce((select max(purchase_id) from purchases), 0) + 1;
end;
$$ language plpgsql;

-- Проверяет, что места на рейс еще можно покупать
create or replace function is_purchase_available(in flight_id int)
returns boolean
as
$$
begin
    return not exists
        (
            select flight_id
            from blocked
            where blocked.flight_id = is_purchase_available.flight_id
            union all
            select flight_id
            from flights
            where
                flights.flight_id = is_purchase_available.flight_id
                and flights.flight_time > now() + interval '3 hours'
        );
end;
$$ language plpgsql;

-- Количество забронированных мест на рейс
create or replace function count_booked(in flight_id int)
returns int
as
$$
begin
    return
        (
            select count(bookings.seat_id) from bookings where
                bookings.flight_id = count_booked.flight_id
                and bookings.expiration_time > now()
        );
end;
$$ language plpgsql;

-- Количество купленных мест на рейс
create or replace function count_purchased(in flight_id int)
returns int
as
$$
begin
    return
        (
            select count(seat_id) from purchases where
                purchases.flight_id = count_purchased.flight_id
        );
end;
$$ language plpgsql;

-- Приведение номера места в формат ddd[A-Z]
create or replace function normalize_seat_no(in seat_no varchar(4))
returns varchar(4)
as
$$
declare
    result varchar(4);
begin
    result = normalize_seat_no.seat_no;
    while length(result) < 4 loop
        result = concat('0', result);
    end loop;
    return result;
end;
$$ language plpgsql;
