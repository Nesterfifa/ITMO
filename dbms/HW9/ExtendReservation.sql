create or replace function ExtendReservation
    (
        in UserId int, 
        in Pass varchar(255), 
        in FlightId int, 
        in SeatNo varchar(4)
    )
returns boolean
language plpgsql
as
$$
declare
    seat_id int;
begin
    seat_id = get_seat_id(ExtendReservation.SeatNo, ExtendReservation.FlightId);
    
    if not has_user(ExtendReservation.UserId, ExtendReservation.Pass) then
        return false;
    end if;
    if not has_flight(ExtendReservation.FlightId) then
        return false;
    end if;
    if not is_booking_available(ExtendReservation.FlightId) then
        return false;
    end if;
    if not has_booking(
        ExtendReservation.UserId, 
        seat_id, 
        ExtendReservation.FlightId)
    then
        return false;
    end if;
    
    update bookings 
    set expiration_date = expiration_date + interval '3 days'
    where
        bookings.user_id = ExtendReservation.UserId
        and bookings.flight_id = ExtendReservation.FlightId
        and bookings.seat_id = seat_id;
    return true;
end;
$$