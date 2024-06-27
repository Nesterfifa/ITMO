create or replace procedure CompressSeats(in FlightId int)
language plpgsql
as
$$
declare
    cursor_seats cursor for
        select
            seats.seat_id as seat_id
        from
            seats
            natural join flights
        where 
            flights.flight_id = CompressSeats.FlightId
        order by normalized_set_no(seats.seat_no);
    cursor_bookings cursor for
        select
            booking_id,
            user_id,
            seat_id,
            flight_id,
            booking_time,
            expiration_time
        from
            bookings
        where
            bookings.flight_id = CompressSeats.FlightId
            and bookings.seat_id not in
                (
                    select
                        purchases.seat_id
                    from
                        purchases
                    where
                        purchases.flight_id = CompressSeats.FlightId
                        
                );
    cursor_purchases cursor for
        select
            purchase_id,
            seat_id,
            flight_id
        from
            purchases
        where
            purchases.flight_id = CompressSeats.FlightId;
    seat int;
    purchase int;
    booking int;
begin
    if not has_flight(BuyFree.FlightId) then
        return;
    end if;
    
    open cursor_seats;
    open cursor_purchases;
    
    loop
        fetch cursor_seats into seat;
        fetch cursor_purchases into purchase;
        exit when not found;
        update bookings set seat_id = seat where seat_id in 
            (
                select seat_id 
                from purchases 
                where purchases.flight_id = CompressSeats.FlightId
            );
        update purchases set seat_id = seat where purchases.purchase_id = purchase;
    end loop;
    
    close cursor_purchases;
    open cursor_bookings;
    
    loop
        fetch cursor_seats into seat;
        fetch cursor_bookings into booking;
        exit when not found;
        update bookings set seat_id = seat where bookings.booking_id = booking;
    end loop;
    
    close cursor_bookings;
end;
$$