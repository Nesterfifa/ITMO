-- Рейсы
create table flights(
    flight_id int not null, 
    flight_time timestamp not null, 
    plane_id integer not null,
    primary key(flight_id)
);

-- Номера мест в самолете
create table seats(
    plane_id int not null,
    seat_no varchar(4) not null,
    seat_id int,
    primary key(seat_id)
);

-- Пользователи
create table users(
    user_id int,
    pass varchar(255) not null,
    salt varchar(100) not null,
    primary key(user_id)
);

-- Бронирования
create table bookings(
    booking_id int not null,
    user_id int not null,
    flight_id int not null,
    seat_id int not null,
    booking_time timestamp not null,
    expiration_time timestamp not null,
    
    primary key(booking_id),
    constraint fk_booking_user_id
        foreign key(user_id)
            references users(user_id),
    constraint fk_booking_flight_id
        foreign key(flight_id)
            references flights(flight_id),
    constraint fk_booking_seat_id
        foreign key(seat_id)
            references seats(seat_id)
);

-- Выкупленные места
create table purchases(
    purchase_id int not null,
    flight_id int not null,
    seat_id int not null,
    
    primary key(purchase_id),
    constraint fk_purchases_flight_id
        foreign key(flight_id)
            references flights(flight_id),
    constraint fk_purchases_seat_id
        foreign key(seat_id)
            references seats(seat_id)
);

-- Рейсы, бронирование для которых отключено вручную
create table blocked(
    flight_id int not null,
    constraint fk_blocked_flight_id
        foreign key(flight_id)
            references flights(flight_id)
);

-- Занятые места (забронированные или выкупленные)
create view booked_seats as
select
    flights.flight_id as flight_id,
    seats.plane_id as plane_id,
    seats.seat_id as seat_id,
    seats.seat_no as seat_no
from
    seats
    natural join flights
where
    exists 
        (
            select
                *
            from
                bookings
            where
                bookings.flight_id = flights.flight_id
                and bookings.seat_id = seats.seat_id
                and bookings.expiration_time > now()
        )
    or exists
        (
            select
                *
            from
                purchases
            where
                purchases.flight_id = flights.flight_id
                and purchases.seat_id = seats.seat_id
        );






