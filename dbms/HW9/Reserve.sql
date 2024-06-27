create or replace function Reserve
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
begin
    if not has_user(Reserve.UserId, Reserve.Pass) then
        return false;
    end if;
    if not has_flight(Reserve.FlightId) then
        return false;
    end if;
    if Reserve.SeatNo not in (select seat_no as SeatNo from FreeSeats(Reserve.FlightId)) then
        return false;
    end if;
    insert into bookings values
        (
            generate_booking_id(), 
            Reserve.UserId, 
            Reserve.FlightId, 
            get_seat_no(Reserve.SeatNo, Reserve.FlightId), 
            now(), 
            now() + interval '3 days'
        );
    return true;
end;
$$