create or replace function FreeSeats(in FlightId int)
returns table(seat_no varchar(4))
language plpgsql
as 
$$
begin
    if not has_flight(FlightId) or not is_booking_available(FlightId)
    then
        return query
            select;
    else
        return query
            select seat_no
            from seats natural join flights
            where flight_id = FlightId
            except
            select seat_no from booked_seats where flight_id = FlightId;
    end if;
end;
$$