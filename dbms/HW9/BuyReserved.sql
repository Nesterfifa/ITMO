create or replace function BuyReserved
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
    seat_id = get_seat_id(BuyReserved.SeatNo, BuyReserved.FlightId);
    
    if not has_user(BuyReserved.UserId, BuyReserved.Pass) then
        return false;
    end if;
    if not has_flight(BuyReserved.FlightId) then
        return false;
    end if;
    if not has_booking(
        BuyReserved.UserId, 
        seat_id, 
        BuyReserved.FlightId)
    then
        return false;
    end if;
    if not is_purchase_available(BuyReserved.FlightId) then
        return false;
    end if;
    
    insert into Purchases values
        (
            seat_id,
            BuyReserved.FlightId,
            get_seat_id(BuyReserved.SeatNo, BuyReserved.FlightId)
        );
    return true;
end;
$$