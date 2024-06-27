create or replace function BuyFree(in FlightId int, in SeatNo varchar(4))
returns boolean
language plpgsql
as
$$
begin
    if not has_flight(BuyFree.FlightId) then
        return false;
    end if;
    if BuyFree.SeatNo not in (select seat_no as SeatNo from FreeSeats(Reserve.FlightId))
    or not is_purchase_available(BuyFree.FlightId)
    then
        return false;
    end if;
    insert into Purchases values
        (
            generate_purchase_id(),
            BuyFree.FlightId,
            get_seat_id(BuyFree.SeatNo, BuyFree.FlightId)
        );
    return true;
end;
$$